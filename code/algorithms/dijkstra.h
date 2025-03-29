#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../data_structures/Graph.h"
#include "../data_structures/InputData.h"
#include "../data_structures/OutputData.h"
#include <vector>
#include <map>

/*!
 * Relaxes an edge during Dijkstra's algorithm for driving paths.
 * Updates the shortest path distance to the destination node if a shorter path is found.
 * @param edge The edge to be relaxed
 * @return True if the new distance is better than the old one. False otherwise
 */
bool relax_drive(Edge *edge);

/*!
 * Compute the shortest driving distances from a given origin node to all other nodes in
 * the graph using Dijkstra's algorithm
 * @param g The graph itself
 * @param origin The origin node of a route
 * @note
 * Time Complexity: O(
 */
void dijkstra_driving(Graph *g, const int &origin);

/*!
 * Compute the shortest driving distances from a given origin node to all other nodes in
 * the graph using Dijkstra's algorithm considering restrictions
 * @param g The graph previously initialized
 * @param origin The origin node
 * @param avoidNodes Nodes to be avoided, in other words, it can't be part of the route
 * @param avoidSegments Edges to be avoided, in other words, it can't be part of the route
 * @note
 * Time Complexity: O(
 */
void dijkstra_restricted_driving(Graph *g, const int &origin,
                                 const std::set<int> &avoidNodes,
                                 const std::set<std::pair<int, int>> &avoidSegments);

/*!
 * Reconstructs the shortest path between two nodes in a graph after route calculation
 * has been executed. The path is returned as an ordered
 * vector of node IDs from origin to destination.
 * @param g The graph previously initialized
 * @param origin The origin node
 * @param dest The destination node
 * @return A vector of node IDs representing the shortest path, ordered from 'origin' to 'dest'.
 * If no path exists, returns an empty vector.
 */
std::vector<int> getPath(Graph *g, const int &origin, const int &dest);

/*!
 * Relaxes an edge during Dijkstra's algorithm for walking paths.
 * Updates the shortest path distance to the destination node if a shorter path is found.
 * @param edge The edge to be relaxed
 * @return True if the new distance is better than the old one. False otherwise
 */
bool relax_walk(Edge *edge);

/*!
 * Compute the shortest walking distances from a given origin node to all other nodes in
 * the graph using Dijkstra's algorithm considering restrictions
 * @param g The graph previously initialized
 * @param origin The origin node
 * @param avoidNodes Nodes to be avoided, in other words, it can't be part of the route
 * @param avoidSegments Edges to be avoided, in other words, it can't be part of the route
 * @note
 * Time Complexity: O(
 */
void dijkstra_walk(Graph *g, const int &origin,
                   const std::set<int> &avoidNodes,
                   const std::set<std::pair<int, int>> &avoidSegments);

/*!
 * Associates a distance to each parking node
 * @param g The graph previously initialized
 * @return A map<int, double>, where:
 * - Key: parking node ID
 * - Value: Computed distance from a node to that parking node
 * @note
 * To be possible to have the correct distances, this function should be invoked after a dijkstra
 * function call so the distances are already computed
 */
std::map<int, double> parking_nodes_dist(const Graph* g);

/*!
 * Reconstructs the shortest walking path between two nodes in a graph after route calculation
 * has been executed. The path is returned as an ordered
 * @param g The graph previously initialized
 * @param origin The origin node
 * @param dest The destination node
 * @return A vector of node IDs representing the shortest path, ordered from 'origin' to 'dest'.
 * If no path exists, returns an empty vector.
 */
std::vector<int> getWalkPath(Graph *g, const int &origin, const int &dest);

/*!
 * Finds the optimal parking node for the fastest route to destination
 * @param dist_map A map containing precomputed distances where:
 * - Key: Parking node ID
 * - Value: Total travel time (sum of driving time with walking time)
 * @param g The graph previously initialized
 * @return a pair<int, double>, where:
 * - first: The node ID of the optimal parking location
 * - second: The total route time (driving + walking)
 */
std::pair<int, double> getBestPath(const std::map<int, double> &dist_map, const Graph* g);

/*!
 * Finds alternative routes in case of not having one that respects the original max walk time
 * @param input_data Struct that contains the input itself (e.g., source, destination, constraints...)
 * @param output_data Struct to store computed routes and distances
 * @param dist_map A map containing precomputed distances where:
 * - Key: Parking node ID
 * - Value: Total travel time (sum of driving time with walking time)
 * @param isRestricted If True, there are restrictions and in this case also an alternative route
 * @param parking_nodes_drive A map containing the shortest driving time to each parking node
 * - Key: Parking node ID
 * - Value: The driving time to that node
 * @param parking_nodes_walk A map containing the shortest walking time to each parking node
 * - Key: Parking node ID
 * - Value: The walking time to that node
 * @param g The graph previously initialized
 * @note
 * Time Complexity: O(
 */
void findAlternativeRoutes(const InputData* input_data, OutputData* output_data, std::map<int, double>& dist_map,
    bool& isRestricted, std::map<int,double> parking_nodes_drive, std::map<int,double> parking_nodes_walk, Graph* g);

/*!
 * Wrapper function for driving-walking route planning logic. Populates the output_data with results
 * @param input_data Struct that contains the input itself (e.g., source, destination, constraints...)
 * @param output_data Struct to store computed routes and distances
 * @param g The graph previously initialized
 * @param isRestricted If True, there are restrictions
 */
void dijkstra_drive_walk_wrapper(const InputData* input_data, OutputData* output_data, Graph* g, bool& isRestricted);

/*!
 * Wrapper function for driving route planning logic. Populates the output_data with results
 * @param input_data Struct that contains the input itself (e.g., source, destination, constraints...)
 * @param output_data Struct to store computed routes and distances
 * @param g The graph previously initialized
 * @param isRestricted If True, there are restrictions
 */
void dijkstra_driving_wrapper(const InputData* input_data, OutputData* output_data, Graph* g, bool& isRestricted);

#endif //DIJKSTRA_H
