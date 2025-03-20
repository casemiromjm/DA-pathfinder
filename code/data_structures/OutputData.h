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
    double min_time_1;
    double min_time_2;

    // methods

    // CLI SIGNIFICA QUE VAI PARA O TERMINAL

    /*!
     * print a vector in the format x1,x2,...,xn on terminal
     * @param vec the vector you want to print
     */
    void printRoute_cli(const std::vector<int>& vec) {
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

    /*!
     * print the best route and alternative route on terminal
     */
    void print_multiroute_cli() {
        printSource_cli(this->source);
        printDest_cli(this->destination);

        if (this->bestDrivingRoute.empty()) {
            std::cout << "BestDrivingRoute:none" << std::endl;
        } else {
            std::cout << "BestDrivingRoute:";
            printRoute_cli(this->bestDrivingRoute);
            std::cout << "(" << min_time_1 << ")";
            std::cout << std::endl;
        }

        if (this->alternativeDrivingRoute.empty()) {
            std::cout << "AlternativeDrivingRoute:none" << std::endl;
        } else {
            std::cout << "AlternativeDrivingRoute:";
            printRoute_cli(this->alternativeDrivingRoute);
            std::cout << "(" << min_time_2 << ")";
            std::cout << std::endl;
        }
    }

    /*!
     * print a vector in the format x1,x2,...,xn on out_file
     * @param vec the vector you want to print
     * @param out_file where the text will be written
     */
    void printRoute_file(const std::vector<int>& vec, std::ofstream& out_file) {
        for (auto node : vec) {
            if (node == vec[vec.size() - 1]) {
                out_file << node;
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

    /*!
     * print the best route and alternative route on an output file
     */
    void print_multiroute_file() {
        std::ofstream out_file;

        out_file.open("../input_output/output.txt");

        if (!out_file.is_open()) {
            std::cerr << "Failed to open output file" << std::endl;
        }

        printSource_file(this->source, out_file);
        printDest_file(this->destination, out_file);

        if (this->bestDrivingRoute.empty()) {
            out_file << "BestDrivingRoute:none" << std::endl;
        } else {
            out_file << "BestDrivingRoute:";
            printRoute_file(this->bestDrivingRoute, out_file);
            out_file << "(" << min_time_1 << ")";
            out_file << std::endl;
        }

        if (this->alternativeDrivingRoute.empty()) {
            out_file << "AlternativeDrivingRoute:none" << std::endl;
        } else {
            out_file << "AlternativeDrivingRoute:";
            printRoute_file(this->alternativeDrivingRoute, out_file);
            out_file << "(" << min_time_2 << ")";
            out_file << std::endl;
        }

        std::cout << "output.txt successfully created in ./input_output/" << std::endl;
        std::cout << std::endl;

        out_file.close();
    }

    void print_restricted_route_file() {
        std::ofstream out_file;

        out_file.open("../input_output/output.txt");

        if (!out_file.is_open()) {
            std::cerr << "Failed to open output file" << std::endl;
        }

        printSource_file(this->source, out_file);
        printDest_file(this->destination, out_file);

        if (this->restrictedDrivingRoute.empty()) {
            out_file << "RestrictedDrivingRoute:none" << std::endl;
        } else {
            out_file << "RestrictedDrivingRoute:";
            printRoute_file(this->restrictedDrivingRoute, out_file);
            out_file << "(" << min_time_1 << ")";
            out_file << std::endl;
        }

        std::cout << "output.txt successfully created in ./input_output/" << std::endl;
        std::cout << std::endl;

        out_file.close();
    }

};

#endif //OUTPUT_H
