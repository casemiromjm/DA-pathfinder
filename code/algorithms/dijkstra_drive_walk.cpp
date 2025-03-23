//
// Created by sebas on 20-03-2025.
//

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "dijsktra_driving.cpp"
#include <InputData.h>
#include <OutputData.h>
#include <unordered_set>


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
        v->setPath(nullptr);
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
set<pair<int, int>> parking_nodes_dist(const Graph* g) {
    set<pair<int,int>> parking_nodes;

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

    while (d->getInfo() != dest) {
        res.push_back(d->getInfo());
        d = d->getWalkPath()->getOrig();
    }

    res.push_back(d->getInfo());
    return res;
}

void dijkstra_drive_walk_wrapper(const InputData* input_data, OutputData* output_data, Graph* g) {
    set<pair<int, int>> path_dist;
    output_data->source = input_data->source;
    output_data->destination = input_data->destination;

    //Computar distâncias driving da source aos nós com parking e guardá-las
    dijkstra_restricted_driving(g, input_data->source, input_data->avoidNodes, input_data->avoidSegments);
    set<pair<int,int>> parking_nodes_drive = parking_nodes_dist(g);

    //Computar distâncias walking da dest aos nós com parking e guardá-las
    dijkstra_walk(g, input_data->source, input_data->avoidNodes, input_data->avoidSegments);
    set<pair<int,int>> parking_nodes_walk = parking_nodes_dist(g);


}
