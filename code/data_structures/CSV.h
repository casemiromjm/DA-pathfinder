#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

class Csv {
    public:
        std::vector<std::vector<std::string>> getData();
        void readCSV(const std::string& file_name);
    private:
        std::vector<std::vector<std::string>> data;     // where the csv data is stored
};

/*!
 *access the CSV data
 *@return CSV data
 */
inline std::vector<std::vector<std::string>> Csv::getData() {
    return data;
}

/*!
 * Function for reading CSV files and storing it
 * @param file_name file name that you are trying to open
 * @return all lines in a 2D vector
 */
inline void Csv::readCSV(const std::string& file_name) {
    std::ifstream file(file_name);

    data.clear();

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);       // skips the header line
    while (getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();
}

#endif