#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <fstream>

/*!
 * Stores output data
 */
struct OutputData {
    int source;
    int destination;
    int parkingNode1;
    int parkingNode2;
    std::vector<int> bestDrivingRoute;
    std::vector<int> bestWalkingRoute;
    std::vector<int> alternativeDrivingRoute1;
    std::vector<int> alternativeDrivingRoute2;
    std::vector<int> alternativeWalkingRoute1;
    std::vector<int> alternativeWalkingRoute2;
    std::string message;
    double min_time_1;
    double min_time_2;
    double min_time_3;
    double min_time_4;
    double total_time1;
    double total_time2;

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
     * Prints the best route and alternative route on terminal
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

        if (this->alternativeDrivingRoute1.empty()) {
            std::cout << "AlternativeDrivingRoute:none" << std::endl;
        } else {
            std::cout << "AlternativeDrivingRoute:";
            printRoute_cli(this->alternativeDrivingRoute1);
            std::cout << "(" << min_time_2 << ")";
            std::cout << std::endl;
        }
        std::cout << std::endl;
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
     * Prints the best route, considering restrictions and driving+walking, to terminal
     */
    void print_restricted_drive_walk_cli() {

        printSource_cli(this->source);
        printDest_cli(this->destination);

        if (this->bestDrivingRoute.empty() && this->bestWalkingRoute.empty()) {
            std::cout << "DrivingRoute:" << std::endl;
            std::cout << "ParkingNode:" << std::endl;
            std::cout << "WalkingRoute:" << std::endl;
            std::cout << "TotalTime:" << std::endl;
            std::cout << "Message:" << message << std::endl;

        } else {
            std::cout << "DrivingRoute:";
            printRoute_cli(this->bestDrivingRoute);
            std::cout << "(" << min_time_1 << ")" << std::endl;

            std::cout << "ParkingNode:" << parkingNode1 << std::endl;

            std::cout << "WalkingRoute:";
            printRoute_cli(this->bestWalkingRoute);
            std::cout << "(" << min_time_2 << ")" << std::endl;

            std::cout << "TotalTime:" << total_time1 << std::endl;

        }

        std::cout << std::endl;
    }

    /*!
     * Prints the alternative routes, considering restrictions and driving+walking, to terminal
     */
    void print_alternative_drive_walk_cli() {

        printSource_cli(this->source);
        printDest_cli(this->destination);


        std::cout << "DrivingRoute1:";
        printRoute_cli(this->alternativeDrivingRoute1);
        std::cout<< "(" << min_time_1 << ")" << std::endl;

        std::cout << "ParkingNode1:" << parkingNode1 << std::endl;

        std::cout << "WalkingRoute1:";
        printRoute_cli(this->alternativeWalkingRoute1);
        std::cout << "(" << min_time_2 << ")" << std::endl;

        std::cout << "TotalTime1:" << total_time1 << std::endl;


        std::cout << "DrivingRoute2:";
        printRoute_cli(this->alternativeDrivingRoute2);
        std::cout << "(" << min_time_3 << ")" << std::endl;

        std::cout << "ParkingNode2:" << parkingNode2 << std::endl;

        std::cout << "WalkingRoute2:";
        printRoute_cli(this->alternativeWalkingRoute2);
        std::cout << "(" << min_time_4 << ")" << std::endl;

        std::cout << "TotalTime2:" << total_time2 << std::endl;

        std::cout << std::endl;
    }

    /*!
     * Prints a vector in the format x1,x2,...,xn on out_file
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
     * Prints the source on out_file
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

        if (this->alternativeDrivingRoute1.empty()) {
            out_file << "AlternativeDrivingRoute:none" << std::endl;
        } else {
            out_file << "AlternativeDrivingRoute:";
            printRoute_file(this->alternativeDrivingRoute1, out_file);
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

        if (this->bestDrivingRoute.empty() && this->bestWalkingRoute.empty()) {
            out_file << "DrivingRoute:" << std::endl;
            out_file << "ParkingNode:" << std::endl;
            out_file << "WalkingRoute:" << std::endl;
            out_file << "TotalTime:" << std::endl;
            out_file << "Message:" << message << std::endl;

        } else {
            out_file << "DrivingRoute:";
            printRoute_file(this->bestDrivingRoute, out_file);
            out_file << "(" << min_time_1 << ")" << std::endl;

            out_file << "ParkingNode:" << parkingNode1 << std::endl;

            out_file << "WalkingRoute:";
            printRoute_file(this->bestWalkingRoute, out_file);
            out_file << "(" << min_time_2 << ")" << std::endl;

            out_file << "TotalTime:" << total_time1 << std::endl;

        }

        std::cout << "output.txt successfully created in ./input_output/" << std::endl;
        std::cout << std::endl;

        out_file.close();
    }


    void print_alternative_drive_walk_file() {
        std::ofstream out_file;

        out_file.open("../input_output/alternative_routes.txt");

        if (!out_file.is_open()) {
            std::cerr << "Failed to open output file" << std::endl;
        }

        printSource_file(this->source, out_file);
        printDest_file(this->destination, out_file);


        out_file << "DrivingRoute1:";
        printRoute_file(this->alternativeDrivingRoute1, out_file);
        out_file << "(" << min_time_1 << ")" << std::endl;

        out_file << "ParkingNode1:" << parkingNode1 << std::endl;

        out_file << "WalkingRoute1:";
        printRoute_file(this->alternativeWalkingRoute1, out_file);
        out_file << "(" << min_time_2 << ")" << std::endl;

        out_file << "TotalTime1:" << total_time1 << std::endl;


        out_file << "DrivingRoute2:";
        printRoute_file(this->alternativeDrivingRoute2, out_file);
        out_file << "(" << min_time_3 << ")" << std::endl;

        out_file << "ParkingNode2:" << parkingNode2 << std::endl;

        out_file << "WalkingRoute2:";
        printRoute_file(this->alternativeWalkingRoute2, out_file);
        out_file << "(" << min_time_4 << ")" << std::endl;

        out_file << "TotalTime2:" << total_time2 << std::endl;


        std::cout << "alternatives_routes.txt successfully created in ./input_output/" << std::endl;
        std::cout << std::endl;

        out_file.close();
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
                print_alternative_drive_walk_file();
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

                if (isRestricted) {
                    std::cout << message << std::endl;
                    std::cout << std::endl;
                    std::cout << "Alternative routes found:" << std::endl;
                    std::cout << std::endl;
                    print_alternative_drive_walk_cli();
                }

                else {
                    print_restricted_drive_walk_cli();
                }
            }
        }
    }

};

#endif //OUTPUT_H
