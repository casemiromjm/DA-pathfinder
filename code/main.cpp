#include <iostream>
#include <sstream>
#include <map>
#include "./data_structures/Graph.h"
#include <string>
#include <fstream>

/*!
 * Function for reading CSV files
 * @param file_name is the file name for better error messages
 * @return return all lines separated in vectors
 */
std::vector<std::vector<std::string>> readCSV(const std::string& file_name) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(file_name);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return data;
    }

    std::string line;
    std::getline(file, line);       // skips the header line
    while (getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

/*!
 * Function for constructing a graph
 * @retval true if the construction was successful
 * @retval false if it was not
 */
bool constructGraph(Graph<int>& g) {
    // readCSV faz com q leiamos o ficheiro 2x, mas faz a função ficar consideravelmente mais simples

    // read Locations.csv;

    auto data = readCSV("../data/Locations.csv");

    if (data.empty()) {
        std::cerr << "Failed to read Locations.csv or file is empty." << std::endl;
        return false;
    }

    std::map<std::string, int> loc_IdCode;      // maps each code to its id

    // create vertexes; create map
    for (auto loc_info : data) {
        int locId = std::stoi(loc_info[1]); // Convert loc ID to int
        int parkingStatus = std::stoi(loc_info[3]); // Convert parking status to int

        g.addVertex(locId, parkingStatus);
        loc_IdCode[loc_info[2]] = locId;
    }

    // read distances

    data = readCSV("../data/Distances.csv");

    if (data.empty()) {
        std::cerr << "Failed to read Distances.csv or file is empty." << std::endl;
        return false;
    }

    // create edges
    for (auto edge_info : data) {
        auto source = loc_IdCode[edge_info[0]];
        auto dest = loc_IdCode[edge_info[1]];

        g.addEdge(source, dest, edge_info[2] == "X" ? INF : stoi(edge_info[2]), stoi(edge_info[3]));
    }

    return true;
}

int main() {

    Graph<int> city;

    if (!constructGraph(city)) {
        std::cerr << "Graph construction failed" << std::endl;
        return 1;
    }

    std::cout << "Graph constructed successfully!" << std::endl;

    return 0;
}