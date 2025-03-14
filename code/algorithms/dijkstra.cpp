#include "./data_structures/Graph.h"
#include "./data_structures/PriorityQueue.h"

using namespace std;

template <class T>
bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    Vertex<T> * u = edge->getOrig();
    Vertex<T> * v = edge->getDest();
    if ( u->getDist() + edge->getWeight() < v->getDist()) {
        v -> setDist(u -> getDist() + edge->getWeight());
        v -> setPath(edge);
        return true;
    }
    return false;
}

template <class T>
void dijkstra(Graph<T> * g, const int &origin) {

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

    while (q->getInfo() != origin) {
        res.push_back(q->getInfo());
        q = q->getPath()->getOrig();
    }
    res.push_back(origin);
    reverse(res.begin(), res.end());
    return res;
}





