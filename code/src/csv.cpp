#include "../include/csv.h"

/*!
 * Function for reading CSV files
 * @param file_name is the file name for better error messages
 * @return return all lines separated in vectors
 */
std::vector<std::vector<std::string>> readCSV(const std::string& file_name) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(file_name);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return data;
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
    return data;
}