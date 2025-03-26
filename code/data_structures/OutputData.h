#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <fstream>

struct OutputData {
    int source;
    int destination;
    int parkingNode;
    std::vector<int> bestDrivingRoute;
    std::vector<int> alternativeDrivingRoute;
    std::vector<int> drivingRoute;
    std::vector<int> walkingRoute;
    std::string message;
    double min_time_1;
    double min_time_2;
    double total_time;

    // methods

    // CLI SIGNIFICA QUE VAI PARA O TERMINAL

    /*!
     * Function for printing a vector in the format x1,x2,...,xn on terminal
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
     * Function for printing the source on terminal
     * @param source source node
     */
    void printSource_cli(const int& source) {
        std::cout << "Source:" << source << std::endl;
    }

    /*!
     * Function for printing the dest on terminal
     * @param dest destination node
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
        std::cout << std::endl;
    }

    /*!
     * Print a vector in the format x1,x2,...,xn on out_file
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
     * Function for printing the source on out_file
     * @param source the source node
     * @param out_file where the text will be written
     */
    void printSource_file(const int& source, std::ofstream& out_file) {
        out_file << "Source:" << source << std::endl;
    }

    /*!
     * Prints the destination on out_file
     * @param dest the dest node
     * @param out_file where the text will be written
     */
    void printDest_file(const int& dest, std::ofstream& out_file) {
        out_file << "Destination:" << dest << std::endl;
    }

    /*!
     * Prints the best route and alternative route on an output file
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

    /*!
     * Prints the best route, considering restrictions, to output file
     */
    void print_restricted_route_file() {
        std::ofstream out_file;

        out_file.open("../input_output/output.txt");

        if (!out_file.is_open()) {
            std::cerr << "Failed to open output file" << std::endl;
        }

        printSource_file(this->source, out_file);
        printDest_file(this->destination, out_file);

        if (this->bestDrivingRoute.empty()) {
            out_file << "RestrictedDrivingRoute:none" << std::endl;
        } else {
            out_file << "RestrictedDrivingRoute:";
            printRoute_file(this->bestDrivingRoute, out_file);
            out_file << "(" << min_time_1 << ")";
            out_file << std::endl;
        }

        std::cout << "output.txt successfully created in ./input_output/" << std::endl;
        std::cout << std::endl;

        out_file.close();
    }

    /*!
     * Prints the best route, considering restrictions, to terminal
     */
    void print_restricted_route_cli() {

        printSource_cli(this->source);
        printDest_cli(this->destination);

        if (this->bestDrivingRoute.empty()) {
            std::cout << "RestrictedDrivingRoute:none" << std::endl;
        } else {
            std::cout << "RestrictedDrivingRoute:";
            printRoute_cli(this->bestDrivingRoute);
            std::cout << "(" << min_time_1 << ")";
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    /*!
     * Prints the best route, considering restrictions and driving+walking, to an output file
     */
    void print_restricted_drive_walk_file() {
        std::ofstream out_file;

        out_file.open("../input_output/output.txt");

        if (!out_file.is_open()) {
            std::cerr << "Failed to open output file" << std::endl;
        }

        printSource_file(this->source, out_file);
        printDest_file(this->destination, out_file);

        if (this->drivingRoute.empty()) {
            out_file << "DrivingRoute:" << std::endl;
            out_file << "ParkingNode:" << std::endl;
            out_file << "WalkingRoute:" << std::endl;
            out_file << "TotalTime:" << std::endl;
            out_file << "Message:" << message << std::endl;

        } else {
            out_file << "DrivingRoute:";
            printRoute_file(this->drivingRoute, out_file);
            out_file << "(" << min_time_1 << ")" << std::endl;

            out_file << "ParkingNode:" << parkingNode << std::endl;

            out_file << "WalkingRoute:";
            printRoute_file(this->walkingRoute, out_file);
            out_file << "(" << min_time_2 << ")" << std::endl;

            out_file << "TotalTime:" << total_time << std::endl;

        }

        std::cout << "output.txt successfully created in ./input_output/" << std::endl;
        std::cout << std::endl;

        out_file.close();
    }

    /*!
     * Prints the best route, considering restrictions and driving+walking, to an output file
     */
    void print_restricted_drive_walk_cli() {

    }

    /*!
     * Wrapper function to output data
     * @param choice stores from where it took the inputs and to where it should output route information
     * @param mode mode of the route planning. can be "driving" or "driving-walking"
     * @param isRestricted stores if there are restrictions on the route or not
     */
    void out(const char& choice, const std::string& mode, const bool& isRestricted) {
        // file
        if (choice == '1') {
            if (mode == "driving") {
                if (!isRestricted) {
                    print_multiroute_file();
                }
                else {
                    print_restricted_route_file();
                }
            }

            else if (mode == "driving-walking") {
                print_restricted_drive_walk_file();
            }
        }

        // command line
        else if (choice == '2') {
            if (mode == "driving") {
                if (!isRestricted) {
                    print_multiroute_cli();
                }
                else {
                    print_restricted_route_cli();
                }
            }

            else if (mode == "driving-walking") {
                print_restricted_drive_walk_cli();
            }
    }

};

#endif //OUTPUT_H
