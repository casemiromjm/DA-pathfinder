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

    //inicializar variáveis auxiliares

    for (auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }

    //nó de origem
    Vertex* s = g->findVertex(origin);
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
        return res;     // dest ñ alcançável
    }

    while (d->getInfo() != origin) {
        res.push_back(d->getInfo());

        // nós que não sejam dest ou origin marcados como visitados após a primeira call do dijkstra
        // p não ter nós repetidos em cada rota
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

    //Verificar se a rota vai ser restrita
    if (input_data->includeNode != -1 || !input_data->avoidNodes.empty() || !input_data->avoidSegments.empty()) {
        isRestricted = true;
        //Verificar se tem include node
        if (input_data->includeNode != -1) {
            // se tem q passar por um nó, faz 2 dijkstras. 1 ate o nó e outro do nó ao destino

            dijkstra_restricted_driving(g, input_data->source, input_data->avoidNodes, input_data->avoidSegments);

            //depois do dijkstra vamos encontrar o caminho mais curto até ao "include Node"
            std::vector<int> path_to_include = getPath(g,input_data->source, input_data->includeNode);
            int path_size1 = g->findVertex(input_data->includeNode)->getDist();

            dijkstra_restricted_driving(g, input_data->includeNode, input_data->avoidNodes, input_data->avoidSegments);

            //depois fazemos outro dijkstra e encontramos o caminho mais curto do "include Node" até ao nó final
            std::vector<int> path_include_to_dest = getPath(g,input_data->includeNode, input_data->destination);
            int path_size2 = g->findVertex(input_data->destination)->getDist();

            path_to_include.pop_back(); //tirar o "include Node" do primeiro caminho
            //depois combinamos o caminho 1 com o 2 para ter o caminho final
            path_to_include.insert(path_to_include.end(), path_include_to_dest.begin(), path_include_to_dest.end());

            output_data->bestDrivingRoute = path_to_include;
            output_data->min_time_1 = path_size1 + path_size2;
        }

        //Não tem include node, mas tem restrições de vértices e/ou de arestas
        else {
            dijkstra_restricted_driving(g, input_data->source, input_data->avoidNodes, input_data->avoidSegments);
            output_data->bestDrivingRoute = getPath(g, input_data->source, input_data->destination);
            output_data->min_time_1 = g->findVertex(input_data->destination)->getDist();
        }
    }

    // sem quaisquer restrições
    else {
        dijkstra_driving(g, input_data->source);
        output_data->bestDrivingRoute = getPath(g, input_data->source, input_data->destination);
        output_data->min_time_1 = g->findVertex(input_data->destination)->getDist();

        dijkstra_driving(g, input_data->source);
        output_data->alternativeDrivingRoute = getPath(g, input_data->source, input_data->destination);
        output_data->min_time_2 = g->findVertex(input_data->destination)->getDist();
    }
}

