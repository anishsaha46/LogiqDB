#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Table.h"
#include <fstream>

class FileManager {
public:
    static void saveTable(const Table& table) {
        std::ofstream file(table.tableName + ".txt");
        if (!file) {
            std::cerr << "Error opening file for saving.\n";
            return;
        }

        for (const auto& column : table.columnNames) {
            file << column << ",";
        }
        file << "\n";

        for (const auto& row : table.rows) {
            for (const auto& field : row.fields) {
                file << field.value << ",";
            }
            file << "\n";
        }

        file.close();
    }

    static void loadTable(Table& table) {
        std::ifstream file(table.tableName + ".txt");
        if (!file) {
            return;
        }

        std::string line;
        std::getline(file, line);  // Skip column names

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string value;
            Row row;
            for (const auto& column : table.columnNames) {
                std::getline(ss, value, ',');
                row.addField(column, value);
            }
            table.addRow(row);
        }

        file.close();
    }
};

#endif
