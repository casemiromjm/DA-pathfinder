//
// Created by Rafael dos Santos Rodrigues on 14/03/2025.
//

#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <string>
#include <vector>
#include <iostream>

struct InputData {
    std::string mode;
    int source;
    int destination;
    int maxWalkTime;
    std::vector<int> avoidNodes;
    std::vector<std::pair<int,int> > avoidSegments;
    int includeNode;
 };


InputData readInputFile(std::string &filename) {
    std::ifstream file("./input_output/" + filename); //recebe o filename e procura na pasta input_output

    InputData input_data; //nao sei se vai ser necessário

    //perguntar se cada ficheiro vai ter só um input ou vários?
    //se tiver vários como fazer?

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string input;
        std::string value;

        getline(ss, input, ':');
        getline(ss, value);

        if (input == "Mode") {
            input_data.mode = value;
        }

        else if (input == "Source") {
            input_data.source = std::stoi(value);
        }

        else if (input == "Destination") {
            input_data.destination = std::stoi(value);
        }

        else if (input == "MaxWalkTime") {
            input_data.maxWalkTime = std::stoi(value);
        }

        else if (input == "AvoidNodes") {
            std::stringstream ssNodes(value);
            std::string node;

            while (getline(ssNodes, node, ',')) {
                input_data.avoidNodes.push_back(std::stoi(node));
            }
        }

        else if (input == "AvoidSegments") {
            std::stringstream ssSegments(value);
            int first, second;
            char ch;

            while (ssSegments >> ch) {
                if (ch == '(') {
                    ssSegments >> first;
                    ssSegments >> ch;
                    ssSegments >> second;
                    ssSegments >> ch;
                    input_data.avoidSegments.push_back(std::make_pair(first, second));
                }
            }
        }

        else if (input == "IncludeNodes") {
            input_data.includeNode = std::stoi(value);
        }
    }

    file.close();
    return intput_data;
}

#endif //INPUTDATA_H
