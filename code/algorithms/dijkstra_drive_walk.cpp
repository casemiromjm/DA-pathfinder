#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include <InputData.h>
#include <OutputData.h>
#include <string>
#include "../algorithms/dijkstra.h"

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
map<int, double> parking_nodes_dist(const Graph* g) {
    map<int,double> parking_nodes {};

    if (g->getVertexSet().empty()) {
        return {};
    }
    for (auto v : g->getVertexSet()) {
        if (v->getParking() == 1) {
            parking_nodes[v->getInfo()] = v->getDist();
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

    res.push_back(dest);
    return res;
}

//Devolve o nó de parking e distancia total do melhor trajeto
pair<int, double> getBestPath(const map<int, double> &dist_map, const Graph* g) {
    pair<int, int> best_path;

    int best_sum = INF, best_parking = 0;
    for (const auto &d : dist_map) {

        if (d.second < best_sum) {
            best_sum = d.second;
            best_parking = d.first;
        }

        //Maior distancia walk desempata
        else if (d.second == best_sum) {

            //Como o dijkstra_walk foi chamado mais recentemente, getDist retorna a distância walk
            if (g->findVertex(d.first)->getDist() > g->findVertex(best_parking)->getDist()) {
                best_parking = d.first;
                best_sum = d.second;
            }
        }
    }

    best_path.first = best_parking;
    best_path.second = best_sum;

    return best_path;
}

void dijkstra_drive_walk_wrapper(const InputData* input_data, OutputData* output_data, Graph* g, bool& isRestricted) {
    map<int, double> dist_map; //Vão se guardar o nó de parking usado por caminho e as somas das distâncias drive + walk
    output_data->source = input_data->source;
    output_data->destination = input_data->destination;

    //Computar distâncias driving da source aos nós com parking e guardá-las
    dijkstra_restricted_driving(g, input_data->source, input_data->avoidNodes, input_data->avoidSegments);
    map<int,double> parking_nodes_drive = parking_nodes_dist(g);

    //Computar distâncias walking da dest aos nós com parking e guardá-las
    dijkstra_walk(g, input_data->destination, input_data->avoidNodes, input_data->avoidSegments);
    map<int,double> parking_nodes_walk = parking_nodes_dist(g);

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

    else if (dist_map.empty()) {  //se não achar nenhum caminho com o maxWalkTime "normal"
        int helperWalkTime = input_data->maxWalkTime;
        map <int, double>  alternative_routes;

        //enquanto não tiver pelo menos 2 rotas alternativas (ou se não ultrapassar "gap" maximo do walkTime)
        while (alternative_routes.size() < 2 && helperWalkTime < 100) {

            //atualizar o dist_map com o novo walkTime
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

            //depois de fazer as combinações com o novo walkTime vamos colocando as melhores rotas no vetor "alternative_routes"
            //até o dist_map ficar vazio ou o vetor ter 2 rotas alternativas
            while (!dist_map.empty()) {
                auto best = getBestPath(dist_map, g);

                if (!alternative_routes.contains(best.first)) {
                    alternative_routes.insert(best);
                }

                dist_map.erase(best.first); //apaga o "best" atual

                if (alternative_routes.size() >= 2) break;
            }

            helperWalkTime += 10;
        }

        if (!alternative_routes.empty()) {
            isRestricted = true;
            auto first_elem = alternative_routes.begin(); //1 elemento
            auto second_elem = first_elem++; //2 elemento

            //logica para fazer output na ordem certa, ou seja, com o menor totalTime primeiro
            if (second_elem != alternative_routes.end()) {
                if (first_elem->second > second_elem->second) {
                    auto aux = first_elem;
                    first_elem = second_elem;
                    second_elem = aux;
                }
            }

            output_data->parkingNode1 = first_elem->first;
            output_data->total_time1 = first_elem->second;

            output_data->min_time_1 = parking_nodes_drive[first_elem->first];
            output_data->min_time_2 = parking_nodes_walk[first_elem->first];

            output_data->drivingRoute1 = getPath(g, input_data->source, first_elem->first);
            output_data->walkingRoute1 = getWalkPath(g, first_elem->first, input_data->destination);


            if (second_elem != alternative_routes.end()) {
                output_data->parkingNode2 = second_elem->first;
                output_data->total_time2 = second_elem->second;

                output_data->min_time_3 = parking_nodes_drive[second_elem->first];
                output_data->min_time_4 = parking_nodes_walk[second_elem->first];

                output_data->drivingRoute2 = getPath(g, input_data->source, second_elem->first);
                output_data->walkingRoute2 = getWalkPath(g, second_elem->first, input_data->destination);
            }
        }

        else {
            output_data->message = "No path with max. walk time of " + to_string(input_data->maxWalkTime) + " minutes was found.";
        }
    }

    else {
        pair<int, double> best_path = getBestPath(dist_map, g);

        output_data->parkingNode1 = best_path.first;
        output_data->total_time1 = best_path.second;

        output_data->min_time_1 = parking_nodes_drive[best_path.first];
        output_data->min_time_2 = parking_nodes_walk[best_path.first];

        output_data->drivingRoute1 = getPath(g, input_data->source, best_path.first);
        output_data->walkingRoute1 = getWalkPath(g, best_path.first, input_data->destination);
    }
}
