#include <iostream>
#include "data_structures/Graph.h"
#include "data_structures/InputData.h"
#include <string>
#include "algorithms/dijsktra_driving.cpp"
#include "algorithms/dijkstra_drive_walk.cpp"
#include <thread>
#include "data_structures/OutputData.h"


int main() {
    // Graph city;
    // std::cout << "Building the city..." << std::endl;

    //std::this_thread::sleep_for(std::chrono::seconds(1));

    // if (!city.constructCity()) {
    //     std::cerr << "City construction failed" << std::endl;
    //     return 1;
    // }
    //
    // std::cout << "City constructed successfully!" << std::endl;

    Graph test_city;
    if (!test_city.constructCity()) {
        std::cerr << "Test City construction failed" << std::endl;
        return 1;
    }
    std::cout << "Test City constructed successfully!" << std::endl;

    bool isRunning = true;
    while (isRunning) {
        char choice = 0;

        std::cout << "To choose an option, enter the symbol inside the brackets:" << std::endl;
        std::cout << std::endl;
        std::cout << "[0] What we have implemented!" << std::endl;
        std::cout << "[1] Read an input via .txt file" << std::endl;
        std::cout << "[2] Read an input via CLI" << std::endl;
        std::cout << "[x] Close the program" << std::endl;

        std::cin >> choice;
        choice = std::tolower(choice);

        switch (choice) {

            case '1': {
                std::string filename;
                std::cout << "Please enter the filename: ";
                std::cin >> filename;

                InputData input_data; input_data.in(choice, filename);
                OutputData output_data;
                bool isRestricted = false;

                if (input_data.mode == "driving") {
                    dijkstra_driving_wrapper(&input_data, &output_data, &test_city, isRestricted);
                }

                else if (input_data.mode == "driving-walking") {
                    dijkstra_drive_walk_wrapper(&input_data, &output_data, &test_city);
                }

                output_data.out(choice, input_data.mode, isRestricted);
            }
            test_city.clear();
            break;

            case '2': {
                std::cout << "When you have finished passing inputs, enter 'q' " << std::endl;
                InputData input_data;
                input_data.in(choice);
                OutputData output_data;
                bool isRestricted = false;

                if (input_data.mode == "driving") {
                    dijkstra_driving_wrapper(&input_data, &output_data, &test_city, isRestricted);
                }

                output_data.out(choice, input_data.mode, isRestricted);
            }
            test_city.clear();
            break;

            case '0':
                std::cout << "- Receive inputs via CLI or via .txt file inside input_output/. Outputs are made in the same place where the inputs were." << std::endl;
                std::cout << "- Calculates the best route and an alternative given where you are and to where you want to go." << std::endl;
                std::cout << "- Calculates the best route that from a point to another respecting the constraints given." << std::endl;
                std::cout << std::endl;
            break;

            case 'x':
                std::cout << "Finished the demo!" << std::endl;
                isRunning = false;
            break;

            default:
                std::cout << "Invalid option! Please try again." << std::endl;
            break;
        }
    }

    return 0;
}
