#include <iostream>
#include <map>
#include "./data_structures/Graph.h"
#include <string>
#include "include/csv.h"
#include <thread>


/*!
 * Function for constructing a graph
 * @param g is where the graph will be constructed
 * @retval true if the construction was successful
 * @retval false if it was not
 */
bool constructGraph(Graph<int>& g) {
    // poderia ser um metodo do grafo? e outra, devíamos dividir o Graph.h em outros .h?

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

        // handle the case when you cant drive
        g.addEdge(source, dest, edge_info[2] == "X" ? INF : stoi(edge_info[2]), stoi(edge_info[3]));
    }

    return true;
}

int main() {

    Graph<int> city;

    std::cout << "Building the city..." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (!constructGraph(city)) {
        std::cerr << "City construction failed" << std::endl;
        return 1;
    }

    std::cout << "City constructed successfully!" << std::endl;

    while (true) {
        int choice = 0;

        std::cout << "To choose an option, enter the symbol inside the brackets:" << std::endl;
        std::cout << std::endl;
        std::cout << "[1] Read an input.txt file" << std::endl;
        std::cout << "[x] Close the program" << std::endl;

        std::cin >> choice;

        switch (choice) {

            case 1:
                std::cout << "Reading the input file" << std::endl;
                break;
            case 2:
                break;
            case 3:
                break;
            case 'x':
                std::cout << "Finished the demo!" << std::endl;
                break;
        }

        break;
    }

    return 0;
}