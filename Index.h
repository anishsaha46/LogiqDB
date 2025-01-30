#ifndef INDEX_H
#define INDEX_H

#include "Table.h"
#include <unordered_map>

class Index {
private:
    std::unordered_map<std::string, std::vector<int>> indexMap;
public:
    void buildIndex(const Table& table, const std::string& columnName);
    std::vector<int> findRowIndices(const std::string& key);
};

#endif
