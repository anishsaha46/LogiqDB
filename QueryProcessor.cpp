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

    // INSERT query
    else if (command == "INSERT") {
        std::string intoKeyword, tableName, valuesKeyword, values;
        ss >> intoKeyword >> tableName >> valuesKeyword;

        if (intoKeyword != "INTO" || valuesKeyword != "VALUES") {
            std::cerr << "Syntax Error: Expected 'INTO' and 'VALUES'.\n";
            return;
        }

        std::getline(ss, values);
        values.erase(std::remove(values.begin(), values.end(), '('), values.end());
        values.erase(std::remove(values.begin(), values.end(), ')'), values.end());

        std::istringstream valueStream(values);
        std::vector<std::string> rowValues;
        std::string val;
        while (std::getline(valueStream, val, ',')) {
            rowValues.push_back(val);
        }

        if (rowValues.size() != table.columnNames.size()) {
            std::cerr << "Error: Column count mismatch.\n";
            return;
        }

        Row newRow;
        for (size_t i = 0; i < table.columnNames.size(); ++i) {
            newRow.addField(table.columnNames[i], rowValues[i]);
        }
        table.addRow(newRow);

        std::cout << "Inserted new row.\n";
    }