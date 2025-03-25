//
// Created by Rafael dos Santos Rodrigues on 25/03/2025.
//

#ifndef DIJKSTRA__H
#define DIJKSTRA__H

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "../data_structures/InputData.h"
#include "../data_structures/OutputData.h"
#include <vector>
#include <map>
#include <set>
#include <utility> // para pair
#include <string>


bool relax_drive(Edge *edge);


void dijkstra_driving(Graph *g, const int &origin);


void dijkstra_restricted_driving(Graph *g, const int &origin,
                                const std::set<int> &avoidNodes,
                                const std::set<std::pair<int, int>> &avoidSegments);


std::vector<int> getPath(Graph *g, const int &origin, const int &dest);


bool relax_walk(Edge *edge);


void dijkstra_walk(Graph *g, const int &origin,
                  const std::set<int> &avoidNodes,
                  const std::set<std::pair<int, int>> &avoidSegments);


std::map<int, int> parking_nodes_dist(const Graph* g);


std::vector<int> getWalkPath(Graph *g, const int &origin, const int &dest);


std::pair<int, int> getBestPath(const std::map<int, int> &dist_map, const Graph* g);


void dijkstra_drive_walk_wrapper(const InputData* input_data, OutputData* output_data, Graph* g);

#endif //DIJKSTRA__H
