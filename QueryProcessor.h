#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include "Table.h"
#include <iostream>

void executeQuery(Table& table, const std::string& query);

class QueryProcessor {
public:
    // Performs a LEFT JOIN on two tables based on a common column
    static Table leftJoin(const Table& leftTable, const Table& rightTable, const std::string& joinColumn);
};

#endif
