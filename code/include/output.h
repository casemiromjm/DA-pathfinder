//
// Created by casemiromjm on 14-03-2025.
//

#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <fstream>

struct OutputData {
    int source;
    int destination;
    std::vector<int> bestDrivingRoute;
    std::vector<int> alternativeDrivingRoute;
    std::vector<int> restrictedDrivingRoute;

    // methods

    // CLI SIGNIFICA QUE VAI PARA O TERMINAL

    /*!
     * print a vector in the format x1,x2,...,xn on terminal
     * @param vec the vector you want to print
     */
    void printVector_cli(const std::vector<int>& vec) {
        for (auto node : vec) {
            if (node == vec[vec.size() - 1]) {
                std::cout << node << std::endl;
            } else {
                std::cout << node << ",";
            }
        }
    }

    /*!
     * print the source on terminal
     * @param source the source node
     */
    void printSource_cli(const int& source) {
        std::cout << "Source:" << source << std::endl;
    }

    /*!
     * print the dest on terminal
     * @param dest the dest node
     */
    void printDest_cli(const int& dest) {
        std::cout << "Destination:" << dest << std::endl;
    }

    void print_multiroute_cli(const OutputData& data) {
        printSource_cli(data.source);
        printDest_cli(data.destination);

        if (data.bestDrivingRoute.empty()) {
            std::cout << "BestDrivingRoute:none" << std::endl;
        } else {
            std::cout << "BestDrivingRoute:";
            printVector_cli(data.bestDrivingRoute);
            std::cout << std::endl;
        }

        if (data.alternativeDrivingRoute.empty()) {
            std::cout << "AlternativeDrivingRoute:none" << std::endl;
        } else {
            std::cout << "AlternativeDrivingRoute:";
            printVector_cli(data.alternativeDrivingRoute);
            std::cout << std::endl;
        }
    }
    /*!
     * print a vector in the format x1,x2,...,xn on out_file
     * @param vec the vector you want to print
     * @param out_file where the text will be written
     */
    void printVector_file(const std::vector<int>& vec, std::ofstream& out_file) {
        for (auto node : vec) {
            if (node == vec[vec.size() - 1]) {
                out_file << node << std::endl;
            } else {
                out_file << node << ",";
            }
        }
    }

    /*!
     * print the source to the out_file
     * @param source the source node
     * @param out_file where the text will be written
     */
    void printSource_file(const int& source, std::ofstream& out_file) {
        out_file << "Source:" << source << std::endl;
    }

    /*!
     * print the dest to the out_file
     * @param dest the dest node
     * @param out_file where the text will be written
     */
    void printDest_file(const int& dest, std::ofstream& out_file) {
        out_file << "Destination:" << dest << std::endl;
    }

    void print_multiroute_file(const OutputData& data) {
        std::ofstream out_file;

        out_file.open("/output.txt");

        if (!out_file.is_open()) {
            std::cerr << "Failed to open output file" << std::endl;
        }

        printSource_cli(data.source);
        printDest_cli(data.destination);

        if (data.bestDrivingRoute.empty()) {
            out_file << "BestDrivingRoute:none" << std::endl;
        } else {
            out_file << "BestDrivingRoute:";
            printVector_cli(data.bestDrivingRoute);
            out_file << std::endl;
        }

        if (data.alternativeDrivingRoute.empty()) {
            out_file << "AlternativeDrivingRoute:none" << std::endl;
        } else {
            out_file << "AlternativeDrivingRoute:";
            printVector_cli(data.alternativeDrivingRoute);
            out_file << std::endl;
        }

        out_file.close();
    }

};

#endif //OUTPUT_H
