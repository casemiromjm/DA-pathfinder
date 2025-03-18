#include <iostream>
#include <map>
#include "./data_structures/Graph.h"
#include "data_structures/InputData.h"
#include <string>
#include "include/csv.h"
#include <thread>


int main() {
    Graph city;

    std::cout << "Building the city..." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (!city.constructCity()) {
        std::cerr << "City construction failed" << std::endl;
        return 1;
    }

    std::cout << "City constructed successfully!" << std::endl;

    bool isRunning = true;
    while (isRunning) {
        char choice = 0;

        std::cout << "To choose an option, enter the symbol inside the brackets:" << std::endl;
        std::cout << std::endl;
        std::cout << "[1] Read an input.txt file" << std::endl;
        std::cout << "[x] Close the program" << std::endl;

        std::cin >> choice;
        choice = std::tolower(choice);

        switch (choice) {

            case '1':
                std::string filename;
                std::cout << "Please enter the filename: ";
                std::cin >> filename;

                InputData input_data = readInputFile(filename);

                std::cout << "Mode: " << input_data.mode << "\n";
                std::cout << "Source: " << input_data.source << "\n";
                std::cout << "Destination: " << input_data.destination << "\n";
                std::cout << "MaxWalkTime: " << input_data.maxWalkTime << "\n";

            break;

            case 'x':
                std::cout << "Finished the demo!" << std::endl;
                isRunning = false;
            break;

            default:
                std::cout << "Invalid option! Please try again." << std::endl;
            break;
        }



        return 0;
    }
}
