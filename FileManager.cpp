#include "FileManager.h"
#include <sstream>

void saveTableToFile(const Table& table, const std::string& filename) {
    std::ofstream file("data/" + filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file for writing.\n";
        return;
    }

    file << table.tableName << "\n";
    for (const auto& col : table.columnNames) {
        file << col << ",";
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

Table loadTableFromFile(const std::string& filename) {
    std::ifstream file("data/" + filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file for reading.\n";
        return Table("");
    }

    std::string line;
    std::getline(file, line);
    Table table(line);

    std::getline(file, line);
    std::stringstream ss(line);
    std::string column;
    while (std::getline(ss, column, ',')) {
        table.addColumn(column);
    }

    while (std::getline(file, line)) {
        Row row;
        std::stringstream rowStream(line);
        std::string value;
        for (const auto& col : table.columnNames) {
            if (std::getline(rowStream, value, ',')) {
                row.addField(col, value);
            }
        }
        table.addRow(row);
    }

    file.close();
    return table;
}
