#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../data_structures/Graph.h"
#include "../data_structures/InputData.h"
#include "../data_structures/OutputData.h"
#include <vector>
#include <map>


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


std::map<int, double> parking_nodes_dist(const Graph* g);

/*!
 * Finds
 * @param g the graph
 * @param origin origin node
 * @param dest destination node
 * @return path from origin to destination inside a vector
 */
std::vector<int> getWalkPath(Graph *g, const int &origin, const int &dest);

/*!
 * Finds the optimal parking node for the fastest route to destination
 * @param dist_map a map that links a distance from a parking node
 * @param g the graph
 * @return a pair containing the best (fastest route) parking node ID and its distance
 */
std::pair<int, double> getBestPath(const std::map<int, double> &dist_map, const Graph* g);

/*!
 * Finds alternative routes in case of not having one that respects the original max walk time
 * @param dist_map
 * @param g the graph
 */
void findAlternativeRoutes(const std::map<int, double> &dist_map, const Graph* g);

/*!
 * Wrapper function to aggregate route planning driving-walk logic and make code more modular
 * @param input_data struct to store data that got in the program
 * @param output_data struct to store data that will be returned by the program
 * @param g the graph
 * @param isRestricted bool value for managing the calculus logic
 */
void dijkstra_drive_walk_wrapper(const InputData* input_data, OutputData* output_data, Graph* g, bool& isRestricted);

/*!
 * Wrapper function to aggregate route planning driving logic and make code more modular
 * @param input_data struct to store data that got in the program
 * @param output_data struct to store data that will be returned by the program
 * @param g the graph
 * @param isRestricted bool value for managing the calculus logic
 */
void dijkstra_driving_wrapper(const InputData* input_data, OutputData* output_data, Graph* g, bool& isRestricted);

#endif //DIJKSTRA_H
