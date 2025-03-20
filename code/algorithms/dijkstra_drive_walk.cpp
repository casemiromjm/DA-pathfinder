//
// Created by sebas on 20-03-2025.
//

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "dijsktra_driving.cpp"
#include <algorithm>
#include <InputData.h>
#include <OutputData.h>
#include <unordered_set>
#include <set>

using namespace std;


bool relax_walk(Edge *edge) { // d[u] + w(u,v) < d[v]

    if (edge->getOrig()->getDist() + edge->getWalk() < edge->getDest()->getDist()) {

        edge->getDest()->setDist(edge->getOrig()->getDist() + edge->getWalk());
        edge->getDest()->setPath(edge);

        return true;
    }

    return false;
}

void dijkstra_walk(Graph * g, const int &origin,
    const  unordered_set<int> &avoidNodes, const set<pair<int, int>> &avoidSegments) {

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

void dijkstra_drive_walk_wrapper(const InputData* input_data, OutputData* output_data, Graph* g) {
    output_data->source = input_data->source;
    output_data->destination = input_data->destination;

    //TODO
}
