#include "Index.h"

void Index::buildIndex(const Table& table, const std::string& columnName) {
    for (size_t i = 0; i < table.rows.size(); ++i) {
        for (const auto& field : table.rows[i].fields) {
            if (field.name == columnName) {
                indexMap[field.value].push_back(i);
                break;
            }
        }
    }
}

std::vector<int> Index::findRowIndices(const std::string& key) {
    return indexMap.count(key) ? indexMap[key] : std::vector<int>();
}
