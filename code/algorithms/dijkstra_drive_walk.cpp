#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include <InputData.h>
#include <OutputData.h>
#include <string>
#include "dijkstra.h"

// useful macros for creating alternative routes
#define MAX_WALK_RANGE 100
#define WALK_INCREMENT 10

using namespace std;

//some global variables
map<int, double> dist_map; //store the parking node used per route and the sums of driving + walking distances
map<int,double> parking_nodes_drive;//stores the driving distances from source to parking nodes
map<int,double> parking_nodes_walk;//store the walking distances from destination to parking nodes

bool relax_walk(Edge *edge) { // d[u] + w(u,v) < d[v]

    if (edge->getOrig()->getDist() + edge->getWalk() < edge->getDest()->getDist()) {

        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWalk());
        edge->getDest()->setWalkPath(edge);

        return true;
    }

    return false;
}

void dijkstra_walk(Graph * g, const int &origin,
    const  set<int> &avoidNodes, const set<pair<int, int>> &avoidSegments) {

    if (g->getVertexSet().empty()) {
        return;
    }

    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setWalkPath(nullptr);
    }

    //source node
    Vertex *s = g->findVertex(origin);
    s->setDist(0);

    MutablePriorityQueue<Vertex> pq;
    pq.insert(s);

    while (!pq.empty()) {
        auto v = pq.extractMin();

        //checks if the node is in the "ignore list"(avoidNodes) if yes, it continues (skips the node).
        if (avoidNodes.contains(v->getInfo())) {
            continue;
        }

        for (auto e : v->getAdj()) { //for all edges of the node being processed

            //checks if the edge (node pair) is in the list of edges to be ignored (avoidSegments)
            if (avoidSegments.contains({v->getInfo(), e->getDest()->getInfo()})) {
                continue;
            }

            double oldDist = e->getDest()->getDist();

            if (relax_walk(e)) {
                if (oldDist == INF) {
                    pq.insert(e->getDest());
                }
                else {
                    pq.decreaseKey(e->getDest());
                }
            }
        }
    }

}

//associate a distance to each parking node
map<int, double> parking_nodes_dist(const Graph* g) {
    map<int,double> parking_nodes {};

    if (g->getVertexSet().empty()) {
        return parking_nodes;       //empty
    }

    for (auto v : g->getVertexSet()) {
        if (v->getParking()) {
            parking_nodes[v->getInfo()] = v->getDist();
        }
    }

    return parking_nodes;
}

vector<int> getWalkPath(Graph* g, const int &origin, const int &dest) {
    vector<int> res;
    auto d = g->findVertex(origin);

    if (d == nullptr || d->getDist() == INF) {
        return res;     //destination unreachable
    }

    while (d->getInfo() != dest) {
        res.push_back(d->getInfo());
        d = d->getWalkPath()->getOrig();
    }

    res.push_back(dest);
    return res;
}

pair<int, double> getBestPath(const map<int, double> &dist_map, const Graph* g) {

    double best_sum = INF;  //use double to handle INF without issues
    int best_parking = 0;

    for (const auto &d : dist_map) {

        //d.first = node ID
        //d.second = computed distance for this node

        //if a shorter distance exists than the current one, update the parking node
        if (d.second < best_sum) {
            best_sum = d.second;
            best_parking = d.first;
        }

        //tiebreaker: longest walking distance
        else if (d.second == best_sum) {

            //since dijkstra_walk was called most recently, getDist() returns the walking distance
            if (g->findVertex(d.first)->getDist() > g->findVertex(best_parking)->getDist()) {
                best_parking = d.first;
                best_sum = d.second;
            }
        }
    }

    return {best_parking, best_sum};
}

//find alternative routes (if they exist)
void findAlternativeRoutes(const InputData* input_data, OutputData* output_data, bool& isRestricted, Graph* g) {

    int helperWalkTime = input_data->maxWalkTime + WALK_INCREMENT;
    map <int, double>  alternative_routes;

    //while there are fewer than 2 alternative routes (or until exceeding maximum walkTime range) the loop continues
    while (alternative_routes.size() < 2 && helperWalkTime < MAX_WALK_RANGE) {

        //update dist_map with the new walkTime
        for (const auto &p : parking_nodes_walk) {
            if (p.second <= helperWalkTime) {
                    dist_map[p.first] = p.second;
            }
        }

        for (const auto &p : parking_nodes_drive) {
            if (dist_map.contains(p.first)) {
                dist_map[p.first] += p.second;
            }
        }

        //after computing combinations with the new walkTime, we progressively store the best routes in the 'alternative_routes' vector
        //until either the dist_map is exhausted, or the vector contains 2 alternative routes the loop continues
        while (!dist_map.empty()) {
            auto best = getBestPath(dist_map, g);

            if (!alternative_routes.contains(best.first)) {
                alternative_routes.insert(best);
            }

            dist_map.erase(best.first); //remove the current 'best' entry

            if (alternative_routes.size() >= 2) break;
        }

        helperWalkTime += WALK_INCREMENT;
    }

    // found alternatives routes
    if (!alternative_routes.empty()) {
        isRestricted = true;
        auto first_elem = alternative_routes.begin(); //1 element
        auto second_elem = first_elem++; //2 element

        //checks if a second alternative route exists, if yes organizes the output structure and assigns the 2 route's values
        if (second_elem != alternative_routes.end()) {

            //logic to ensure output is ordered correctly, i.e., with the lowest totalTime first
            if (first_elem->second > second_elem->second) {
                auto aux = first_elem;
                first_elem = second_elem;
                second_elem = aux;
            }

            output_data->parkingNode2 = second_elem->first;
            output_data->total_time2 = second_elem->second;

            output_data->min_time_3 = parking_nodes_drive[second_elem->first];
            output_data->min_time_4 = parking_nodes_walk[second_elem->first];

            output_data->alternativeDrivingRoute2 = getPath(g, input_data->source, second_elem->first);
            output_data->alternativeWalkingRoute2 = getWalkPath(g, second_elem->first, input_data->destination);
        }

        output_data->parkingNode1 = first_elem->first;
        output_data->total_time1 = first_elem->second;

        output_data->min_time_1 = parking_nodes_drive[first_elem->first];
        output_data->min_time_2 = parking_nodes_walk[first_elem->first];

        output_data->alternativeDrivingRoute1 = getPath(g, input_data->source, first_elem->first);
        output_data->alternativeWalkingRoute1 = getWalkPath(g, first_elem->first, input_data->destination);
    }
}

void dijkstra_drive_walk_wrapper(const InputData* input_data, OutputData* output_data, Graph* g, bool& isRestricted) {

    // ensure good use of global variables, since only the wrapper is called from outside and only the wrapper calls other functions from this file
    dist_map.clear();
    parking_nodes_walk.clear();
    parking_nodes_drive.clear();

    output_data->source = input_data->source;
    output_data->destination = input_data->destination;

    //compute driving distances from source to parking nodes and store them
    dijkstra_restricted_driving(g, input_data->source, input_data->avoidNodes, input_data->avoidSegments);
    parking_nodes_drive = parking_nodes_dist(g);

    //compute walking distances from destination to parking nodes and store them
    dijkstra_walk(g, input_data->destination, input_data->avoidNodes, input_data->avoidSegments);
    parking_nodes_walk = parking_nodes_dist(g);

    for (const auto &p : parking_nodes_walk) {
        //if the walking distance of the path exceeds MaxWalkTime, it's not added to dist_map
        if (p.second <= input_data->maxWalkTime) {
            dist_map[p.first] = p.second;
        }
    }

    for (const auto &p : parking_nodes_drive) {
        //driving distances are only inserted if a valid walking distance already exists
        if (dist_map.contains(p.first)) {
            dist_map[p.first] += p.second;
        }
    }

    if (parking_nodes_drive.empty()) {
        output_data->message = "No parking nodes found.";
    }

    else if (dist_map.empty()) {  //if no path is found with the normal maxWalkTime:

        //search for alternative routes by increasing maxWalkTime and output to a separate file
        findAlternativeRoutes(input_data, output_data, isRestricted, g);

        //store error message because we decided to output alternative routes in a separate file (not 100% correct)
        output_data->message = "No path with max. walk time of " + to_string(input_data->maxWalkTime) + " minutes was found.";
    }

    // found path with original maxwalktime
    else {
        pair<int, double> best_path = getBestPath(dist_map, g);

        output_data->parkingNode1 = best_path.first;
        output_data->total_time1 = best_path.second;

        output_data->min_time_1 = parking_nodes_drive[best_path.first];
        output_data->min_time_2 = parking_nodes_walk[best_path.first];

        output_data->bestDrivingRoute = getPath(g, input_data->source, best_path.first);
        output_data->bestWalkingRoute = getWalkPath(g, best_path.first, input_data->destination);
    }
}
