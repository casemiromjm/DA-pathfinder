#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include <algorithm>
#include <OutputData.h>

using namespace std;

bool relax(Edge *edge) { // d[u] + w(u,v) < d[v]

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

        for (auto e : v->getAdj()) { // para todos os edges do nó a ser processado
            if (e->getDest()->isVisited()) {
              // se o nó foi visitado na primeira visita, ignorar na segunda
              continue;
            }

            double oldDist = e->getDest()->getDist();

            if (relax(e)) {
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
    const  unordered_set<int> &avoidNodes, const unordered_set<pair<int, int>> &avoidSegments) {

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

        for (auto e : v->getAdj()) { // para todos os edges do nó a ser processado
            if (e->getDest()->isVisited() || e->isVisited()) {
                // se o nó ou a aresta em si foi visitado, ignorar
                continue;
            }

            double oldDist = e->getDest()->getDist();

            if (relax(e)) {
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
        return res;     // dest ñ alcançável
    }

    while (d->getInfo() != origin) {
        res.push_back(d->getInfo());

        // nós que não sejam dest ou origin marcados como visitados após a primeira call do dijkstra
        if (d->getInfo() != origin && d->getInfo() != dest) {
            d->setVisited(true);
        }

        d = d->getPath()->getOrig();
    }

    res.push_back(d->getInfo());
    reverse(res.begin(), res.end());

    return res;
}

void dijkstra_driving_wrapper(const InputData* input_data, OutputData* output_data, Graph* g) {
    output_data->source = input_data->source;
    output_data->destination = input_data->destination;

    //Verificar se a rota vai ser restrita
    if (input_data->includeNode != -1 || input_data->avoidNodes.size() != 0 || input_data->avoidSegments.size() != 0) {
        if (input_data->includeNode != -1) {
            //TODO
        }
    }

    else {
        dijkstra_driving(g, input_data->source);
        output_data->bestDrivingRoute = getPath(g, input_data->source, input_data->destination);
        output_data->min_time_1 = g->findVertex(input_data->destination)->getDist();

        dijkstra_driving(g, input_data->source);
        output_data->alternativeDrivingRoute = getPath(g, input_data->source, input_data->destination);
        output_data->min_time_2 = g->findVertex(input_data->destination)->getDist();
    }

    output_data->print_multiroute_file();
}

