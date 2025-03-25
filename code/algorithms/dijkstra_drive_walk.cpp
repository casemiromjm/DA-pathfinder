//
// Created by sebas on 20-03-2025.
//

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include <InputData.h>
#include <OutputData.h>
#include <string>
#include "../algorithms/dijkstra_.h"

using namespace std;


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

    //inicializar variáveis auxiliares

    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setWalkPath(nullptr);
    }

    //nó de origem
    Vertex *s = g->findVertex(origin);
    s->setDist(0);

    MutablePriorityQueue<Vertex> pq;
    pq.insert(s);

    while (!pq.empty()) {
        auto v = pq.extractMin();

        //verifica se o vertex está na lista a ser ignorado, se sim continua (ignora)
        if (avoidNodes.contains(v->getInfo())) {
            continue;
        }

        for (auto e : v->getAdj()) { // para todos os edges do nó a ser processado


            //verifica se a aresta (par de vertex) está na lista de arestas a serem ignoradas
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

//Associar a cada nó de parking uma distância
map<int, int> parking_nodes_dist(const Graph* g) {
    map<int,int> parking_nodes {};

    if (g->getVertexSet().empty()) {
        return {};
    }
    for (auto v : g->getVertexSet()) {
        if (v->getParking() == 1) {
            parking_nodes.insert({v->getInfo(), v->getDist()});
        }
    }
    return parking_nodes;
}

vector<int> getWalkPath(Graph * g, const int &origin, const int &dest) {
    vector<int> res;
    auto d = g->findVertex(origin);

    if (d == nullptr || d->getDist() == INF) {
        return res;     // dest não alcançável
    }

    while (d->getInfo() != origin) {
        res.push_back(d->getInfo());
        if (d->getWalkPath() == nullptr) return {};

        d = d->getWalkPath()->getOrig();
    }

    res.push_back(origin);
    reverse(res.begin(), res.end());
    return res;
}

//Devolve o nó de parking e distancia total do melhor trajeto
pair<int,int> getBestPath(const map<int, int> &dist_map, const Graph* g) {
    pair<int, int> best_path;
    for (const auto &d : dist_map) {
        int best_sum = 0, best_parking = 0;

        if (d.second > best_sum) {
            best_sum = d.second;
            best_parking = d.first;
        }

        //Maior distancia walk desempata
        else if (d.second == best_sum) {

            //Como o dijkstra_walk foi chamado mais recentemente, getDist retorna a distância walk
            if (g->findVertex(d.first)->getDist() > g->findVertex(best_parking)->getDist()) {
                best_path.first = d.first;
                best_path.second = d.second;
            }
        }
    }

    return best_path;
}

void dijkstra_drive_walk_wrapper(const InputData* input_data, OutputData* output_data, Graph* g) {
    map<int, int> dist_map; //Vão se guardar o nó de parking usado por caminho e as somas das distâncias drive + walk
    pair<int, int> best_path;
    output_data->source = input_data->source;
    output_data->destination = input_data->destination;

    //Computar distâncias driving da source aos nós com parking e guardá-las
    dijkstra_restricted_driving(g, input_data->source, input_data->avoidNodes, input_data->avoidSegments);
    map<int,int> parking_nodes_drive = parking_nodes_dist(g);

    //Computar distâncias walking da dest aos nós com parking e guardá-las
    dijkstra_walk(g, input_data->destination, input_data->avoidNodes, input_data->avoidSegments);
    map<int,int> parking_nodes_walk = parking_nodes_dist(g);

    for (const auto &p : parking_nodes_walk) {
        //Se a distância walk do caminho excede o MaxWalkTime, não se adiciona ao dist_map
        if (p.second <= input_data->maxWalkTime) {
            dist_map[p.first] = p.second;
        }
    }

    for (const auto &p : parking_nodes_drive) {
        //Só se vai inserir as distâncias driving se já estiver lá a distância walk (válida)
        if (dist_map.contains(p.first)) {
            dist_map[p.first] += p.second;
        }
    }

    if (parking_nodes_drive.empty()) {
        output_data->message = "No parking nodes found.";
    }
    else if (dist_map.empty()) {
        output_data->message = "No path with max. walk time of " + to_string(input_data->maxWalkTime) + " minutes was found.";
    }
    else {
        best_path  = getBestPath(dist_map, g);

        output_data->parkingNode = best_path.first;
        output_data->total_time = best_path.second;

        output_data->min_time_1 = parking_nodes_drive[best_path.first];
        output_data->min_time_2 = parking_nodes_walk[best_path.first];

        //output_data->drivingRoute = getDrivePath(g, input_data->source, best_path.first);
        //output_data->walkingRoute = getWalkPath(g, best_path.first, input_data->destination);
    }

}
