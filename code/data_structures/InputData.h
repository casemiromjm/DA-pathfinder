#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <string>
#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include <utility>


/*!
 * given a string, transforms it to its lower form
 * @param str string that will be transformed
 * @return void
 */
void str_tolower(std::string& str) {
    for (char& c : str) {
        if (c >= 'A' && c <= 'Z') {
            c = 'a' + (c - 'A');
        }
    }
}

/*!
 * stores the input data
 */
struct InputData {
    std::string mode;
    int source;
    int destination;
    int maxWalkTime = -1;
    std::set<int> avoidNodes;
    std::set<std::pair<int,int>> avoidSegments;
    int includeNode = -1;

    // methods

    /*!
     * Function for reading an input file
     * @param filename which file you are trying to read from input_output folder
     */
    void readInputFile(const std::string &filename) {
    std::ifstream file("../input_output/" + filename); //recebe o filename e procura na pasta input_output

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string input;
        std::string value;

        getline(ss, input, ':');
        getline(ss, value);

        str_tolower(input);

        if (input == "mode") {
            this->mode = value;
        }

        else if (input == "source") {
            this->source = std::stoi(value);
        }

        else if (input == "destination") {
            this->destination = std::stoi(value);
        }

        else if (input == "maxwalktime") {
            if (!value.empty()) {
                this->maxWalkTime = std::stoi(value);
            }
        }

        else if (input == "avoidnodes") {
            std::stringstream ssNodes(value);
            std::string node;

            while (getline(ssNodes, node, ',')) {
                this->avoidNodes.insert(std::stoi(node));
            }
        }

        else if (input == "avoidsegments") {
            std::stringstream ssSegments(value);
            int first, second;
            char ch;

            while (ssSegments >> ch) {
                if (ch == '(') {
                    ssSegments >> first;
                    ssSegments >> ch;
                    ssSegments >> second;
                    ssSegments >> ch;
                    this->avoidSegments.insert(std::make_pair(first, second));
                }
            }
        }

        else if (input == "includenode") {
            if (!value.empty()) {  //Só converte n estiver vazio
                this->includeNode = std::stoi(value);
            }
        }
    }

        file.close();
    }

    /*!
     * Function for reading inputs from terminal
     */
    void readTerminal() {

        std::string line;
        while (std::getline(std::cin, line)) {

            if (line == "q") {
                break;
            }

            std::istringstream iss(line);
            std::string input;
            std::string value;

            std::getline(iss, input, ':');
            std::getline(iss, value);

            str_tolower(input);

            if (input == "mode") {
                this->mode = value;
            }

            else if (input == "source") {
                this->source = std::stoi(value);
            }

            else if (input == "destination") {
                this->destination = std::stoi(value);
            }

            else if (input == "maxwalktime") {
                if (!value.empty()) {
                    this->maxWalkTime = std::stoi(value);
                }
            }

            else if (input == "avoidnodes") {
                std::stringstream ssNodes(value);
                std::string node;

                while (getline(ssNodes, node, ',')) {
                    this->avoidNodes.insert(std::stoi(node));
                }
            }

            else if (input == "avoidsegments") {
                std::stringstream ssSegments(value);
                int first, second;
                char ch;

                while (ssSegments >> ch) {
                    if (ch == '(') {
                        ssSegments >> first;
                        ssSegments >> ch;
                        ssSegments >> second;
                        ssSegments >> ch;
                        this->avoidSegments.insert(std::make_pair(first, second));
                    }
                }
            }

            else if (input == "includenode") {
                if (!value.empty()) {  //Só converte n estiver vazio
                    this->includeNode = std::stoi(value);
                }
            }
        }
    }

    /*!
     * Wrapper function to read inputs
     * @param choice method of the input (1 for file or 2 for CLI)
     * @param filename file name if it is via file
     */
    void in (const char &choice, const std::string& filename="") {
        if (choice == '1') {
            this->readInputFile(filename);
        }
        else if (choice == '2') {
            this->readTerminal();
        }
    }
};

#endif //INPUTDATA_H
