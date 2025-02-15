#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Table.h"
#include <fstream>
#include <sstream>
#include <iostream>

class FileManager {
public:
    static void saveTable(const Table& table) {
        std::ofstream file(table.tableName + ".txt");
        if (!file) {
            std::cerr << "Error opening file for saving: " << table.tableName << ".txt\n";
            return;
        }

        // Write column names
        for (size_t i = 0; i < table.columnNames.size(); ++i) {
            file << table.columnNames[i];
            if (i != table.columnNames.size() - 1) file << ",";  // Avoid trailing comma
        }
        file << "\n";

        // Write rows
        for (const auto& row : table.rows) {
            for (size_t i = 0; i < row.fields.size(); ++i) {
                file << row.fields[i].value;
                if (i != row.fields.size() - 1) file << ",";  // Avoid trailing comma
            }
            file << "\n";
        }

        file.close();
        std::cout << "Table saved successfully: " << table.tableName << ".txt\n";
    }

    static void loadTable(Table& table) {
        std::ifstream file(table.tableName + ".txt");
        if (!file) {
            std::cerr << "Error opening file: " << table.tableName << ".txt\n";
            return;
        }

        std::string line;
        if (std::getline(file, line)) { // Read the first line (column names)
            std::istringstream ss(line);
            std::string column;
            table.columnNames.clear(); // Clear existing column names

            while (std::getline(ss, column, ',')) {
                table.columnNames.push_back(column);
            }
        } else {
            std::cerr << "Error: Empty file or failed to read column names.\n";
            return;
        }

        // Read row data
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string value;
            Row row;

            for (const auto& column : table.columnNames) {
                if (!std::getline(ss, value, ',')) {
                    std::cerr << "Error: Mismatch in data for table '" << table.tableName << "'\n";
                    return;
                }
                row.addField(column, value);
            }

            // Check if there are extra values in the row
            if (std::getline(ss, value, ',')) {
                std::cerr << "Error: Extra data in row for table '" << table.tableName << "'\n";
                return;
            }

            table.addRow(row);
        }

        file.close();
        std::cout << "Table '" << table.tableName << "' loaded successfully.\n";
    }
};

#endif
