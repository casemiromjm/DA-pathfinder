#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

/*!
 * Function for reading CSV files
 * @param file_name is the file name for better error messages
 * @return return all lines separated in vectors
 */
std::vector<std::vector<std::string>> readCSV(const std::string& file_name);

#endif