#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Table.h"
#include <fstream>

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
