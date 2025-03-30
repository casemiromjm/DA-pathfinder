#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include <algorithm>
#include <InputData.h>
#include <OutputData.h>
#include <set>
#include "dijkstra.h"

using namespace std;

bool relax_drive(Edge *edge) { // d[u] + w(u,v) < d[v]

    if (edge->getOrig()->getDist() + edge->getDrive() < edge->getDest()->getDist()) {

        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getDrive());
        edge->getDest()->setPath(edge);

        return true;
    }

    return false;
}

void dijkstra_driving(Graph * g, const int &origin) {

    if (g->getVertexSet().empty()) {
        return;
    }

    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }

    //source node
    Vertex* s = g->findVertex(origin);
    s->setDist(0);

    MutablePriorityQueue<Vertex> pq;
    pq.insert(s);

    while (!pq.empty()) {
        auto v = pq.extractMin();

        for (auto e : v->getAdj()) { //for all edges of the node being processed
            if (e->getDest()->isVisited()) {
              //if the node was visited in the first time, ignore it in the second time
              continue;
            }

            double oldDist = e->getDest()->getDist();

            if (relax_drive(e)) {
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

void dijkstra_restricted_driving(Graph * g, const int &origin,
    const set<int> &avoidNodes, const set<pair<int, int>> &avoidSegments) {

    if (g->getVertexSet().empty()) {
        return;
    }

    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }

    Vertex *s = g->findVertex(origin);
    s->setDist(0);

    MutablePriorityQueue<Vertex> pq;
    pq.insert(s);

    while (!pq.empty()) {
        auto v = pq.extractMin();

        //Checks if the node is in the ignore list, if yes continues (skip the node)
        if (avoidNodes.contains(v->getInfo())) {
            continue;
        }

        for (auto e : v->getAdj()) {

            //checks if the edge (node pair) is in the list of edges to be ignored, if yes then ignore it
            if (avoidSegments.contains({v->getInfo(), e->getDest()->getInfo()})) {
                continue;
            }

            double oldDist = e->getDest()->getDist();

            if (relax_drive(e)) {
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

std::vector<int> getPath(Graph * g, const int &origin, const int &dest) {
    std::vector<int> res;
    auto d = g->findVertex(dest);

    if (d == nullptr || d->getDist() == INF) {
        return res;     //destination unreachable
    }

    while (d->getInfo() != origin) {
        res.push_back(d->getInfo());

        //nodes that aren't the destination or origin are marked as visited after the first Dijkstra call
        //to ensure no repeated nodes in each route
        if (d->getInfo() != origin && d->getInfo() != dest) {
            d->setVisited(true);
        }

        d = d->getPath()->getOrig();
    }

    res.push_back(d->getInfo());
    reverse(res.begin(), res.end());

    return res;
}

void dijkstra_driving_wrapper(const InputData* input_data, OutputData* output_data, Graph* g, bool& isRestricted) {
    output_data->source = input_data->source;
    output_data->destination = input_data->destination;

    //check if the route will be restricted
    if (input_data->includeNode != -1 || !input_data->avoidNodes.empty() || !input_data->avoidSegments.empty()) {
        isRestricted = true;

        //check if there's an node to be included
        if (input_data->includeNode != -1) {
            //if the route must pass through a specific node, perform 2 Dijkstra searches, one from the origin to the required node
            //and other from the required node to destination

            dijkstra_restricted_driving(g, input_data->source, input_data->avoidNodes, input_data->avoidSegments);

            //after running Dijkstra, we'll find the shortest path to the include node
            std::vector<int> path_to_include = getPath(g,input_data->source, input_data->includeNode);
            int path_size1 = g->findVertex(input_data->includeNode)->getDist();

            dijkstra_restricted_driving(g, input_data->includeNode, input_data->avoidNodes, input_data->avoidSegments);

            //we execute another Dijkstra to find the shortest path from the include node to the final destination node
            std::vector<int> path_include_to_dest = getPath(g,input_data->includeNode, input_data->destination);
            int path_size2 = g->findVertex(input_data->destination)->getDist();

            path_to_include.pop_back(); //remove the 'include node' from the first path to simplify route combination

            //then we combine path 1 with path 2 to obtain the final complete route
            path_to_include.insert(path_to_include.end(), path_include_to_dest.begin(), path_include_to_dest.end());

            output_data->bestDrivingRoute = path_to_include;
            output_data->min_time_1 = path_size1 + path_size2;
        }

        //no "includeNode", but there are nodes and/or edge restrictions
        else {
            dijkstra_restricted_driving(g, input_data->source, input_data->avoidNodes, input_data->avoidSegments);
            output_data->bestDrivingRoute = getPath(g, input_data->source, input_data->destination);
            output_data->min_time_1 = g->findVertex(input_data->destination)->getDist();
        }
    }

    //no restrictions
    else {
        dijkstra_driving(g, input_data->source);
        output_data->bestDrivingRoute = getPath(g, input_data->source, input_data->destination);
        output_data->min_time_1 = g->findVertex(input_data->destination)->getDist();

        dijkstra_driving(g, input_data->source);
        output_data->alternativeDrivingRoute1 = getPath(g, input_data->source, input_data->destination);
        output_data->min_time_2 = g->findVertex(input_data->destination)->getDist();
    }
}

