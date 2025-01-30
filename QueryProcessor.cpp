#include "QueryProcessor.h"
#include <sstream>
#include <algorithm>

void executeQuery(Table& table, const std::string& query) {
    std::istringstream ss(query);
    std::string command;
    ss >> command;

    // SELECT query
    if (command == "SELECT") {
        std::cout << "Table: " << table.tableName << "\n";
        for (const auto& col : table.columnNames) {
            std::cout << col << "\t";
        }
        std::cout << "\n---------------------\n";

        for (const auto& row : table.rows) {
            for (const auto& field : row.fields) {
                std::cout << field.value << "\t";
            }
            std::cout << "\n";
        }
    }