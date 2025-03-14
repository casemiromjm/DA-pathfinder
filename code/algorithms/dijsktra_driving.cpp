#include "./data_structures/Graph.h"
#include "./data_structures/PriorityQueue.h"

using namespace std;

template <class T>
bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    Vertex<T> * u = edge->getOrig();
    Vertex<T> * v = edge->getDest();
    if ( u->getDist() + edge->getDrive() < v->getDist()) {
        v -> setDist(u -> getDist() + edge->getDrive());
        v -> setPath(edge);
        return true;
    }
    return false;
}

template <class T>
void dijkstra_driving(Graph<T> * g, const int &origin) {

    if (g->getVertexSet().empty()) {
        return;
    }

    //inicializar variáveis auxiliares

    for (auto v : g->getVertexSet()) {
        v -> setDist(INF);
        v -> setPath(nullptr);
    }

    Vertex<T> *s = g->findVertex(origin); //nó de origem
    s -> setDist(0);

    MutablePriorityQueue<Vertex<T>> pq;
    pq.insert(s);

    while (!pq.empty()) {
        Vertex<T> * v = pq.extractMin();
        for (auto e : v -> getAdj()) { //para todos os edges do nó a ser processado
          if(!(e -> getDest() -> isVisited())) continue;
            double oldDist = e -> getDest() ->getDist();
            if (relax(e)) {
                if (oldDist == INF) {
                    pq.insert(e -> getDest());
                }
                else {
                    pq.decreaseKey(e -> getDest());
                }
            }
        }

    }

}

template <class T>
static std::vector<T> getPath(Graph<T> * g, const int &origin, const int &dest) {
    std::vector<T> res;
    Vertex<T> *q = g->findVertex(dest);

    res.push_back(q->getInfo());
    q = q->getPath()->getOrig();

    while (q->getInfo() != origin) {
        res.push_back(q->getInfo());
        q -> setVisited(true);  //nós que não sejam dest ou origin marcados como visitados após a primeira call do dijkstra
        q = q->getPath()->getOrig();

    }
    res.push_back(origin);
    reverse(res.begin(), res.end());

    return res;
}
