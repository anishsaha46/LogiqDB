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