//
// Created by casemiromjm on 14-03-2025.
//

#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>

struct OutputData {
    int source;
    int destination;
    std::vector<int> bestDrivingRoute;
    std::vector<int> alternativeDrivingRoute;
    std::vector<int> restrictedDrivingRoute;

    // methods

    /*!
     * print a vector in the format x1,x2,...,xn
     * @param vec the vector you want to print
     */
    void printVector(const std::vector<int>& vec) {
        for (auto node : vec) {
            if (node == vec[vec.size() - 1]) {
                std::cout << node << std::endl;
            } else {
                std::cout << node << ",";
            }
        }
    }

    /*!
     * print the source
     * @param source the source node
     */
    void printSource(const int& source) {
        std::cout << "Source:" << source << std::endl;
    }

    /*!
     * print the dest
     * @param dest the dest node
     */
    void printDest(const int& dest) {
        std::cout << "Destination:" << dest << std::endl;
    }

    void out_multiroute(const OutputData& data) {
        printSource(data.source);
        printDest(data.destination);

        if (data.bestDrivingRoute.empty()) {
            std::cout << "BestDrivingRoute:none" << std::endl;
        } else {
            std::cout << "BestDrivingRoute:";
            printVector(data.bestDrivingRoute);
            std::cout << std::endl;
        }

        if (data.alternativeDrivingRoute.empty()) {
            std::cout << "AlternativeDrivingRoute:none" << std::endl;
        } else {
            std::cout << "AlternativeDrivingRoute:";
            printVector(data.alternativeDrivingRoute);
            std::cout << std::endl;
        }
    }
};

#endif //OUTPUT_H
