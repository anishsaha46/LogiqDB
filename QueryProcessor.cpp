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
    
    // UPDATE query
    else if (command == "UPDATE") {
        std::string tableName, setKeyword, whereKeyword, columnToUpdate, newValue, whereColumn, whereValue;
        ss >> tableName >> setKeyword;

        if (setKeyword != "SET") {
            std::cerr << "Syntax Error: Expected SET.\n";
            return;
        }

        std::getline(ss, columnToUpdate, '=');
        ss >> newValue >> whereKeyword;

        if (whereKeyword != "WHERE") {
            std::cerr << "Syntax Error: Expected WHERE.\n";
            return;
        }

        std::getline(ss, whereColumn, '=');
        ss >> whereValue;

        // Trim spaces
        columnToUpdate.erase(std::remove(columnToUpdate.begin(), columnToUpdate.end(), ' '), columnToUpdate.end());
        whereColumn.erase(std::remove(whereColumn.begin(), whereColumn.end(), ' '), whereColumn.end());

        // Perform the update
        for (auto& row : table.rows) {
            for (auto& field : row.fields) {
                if (field.name == whereColumn && field.value == whereValue) {
                    for (auto& updateField : row.fields) {
                        if (updateField.name == columnToUpdate) {
                            updateField.value = newValue;
                            std::cout << "Updated " << columnToUpdate << " to " << newValue << " where " << whereColumn << "=" << whereValue << "\n";
                        }
                    }
                }
            }
        }
    }
    
    // DELETE query
    else if (command == "DELETE") {
        std::string fromKeyword, tableName, whereKeyword, whereColumn, whereValue;
        ss >> fromKeyword >> tableName >> whereKeyword;

        if (fromKeyword != "FROM" || whereKeyword != "WHERE") {
            std::cerr << "Syntax Error: Expected FROM and WHERE.\n";
            return;
        }

        std::getline(ss, whereColumn, '=');
        ss >> whereValue;

        // Trim spaces
        whereColumn.erase(std::remove(whereColumn.begin(), whereColumn.end(), ' '), whereColumn.end());

        // Perform the deletion
        table.rows.erase(std::remove_if(table.rows.begin(), table.rows.end(), [&](const Row& row) {
            for (const auto& field : row.fields) {
                if (field.name == whereColumn && field.value == whereValue) {
                    return true;
                }
            }
            return false;
        }), table.rows.end());

        std::cout << "Deleted rows where " << whereColumn << "=" << whereValue << "\n";
    } 
    
    else {
        std::cerr << "Error: Unknown query type.\n";
    }
}
