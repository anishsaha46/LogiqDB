#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <string>

struct Field {
    std::string name;
    std::string value;
};

struct Row {
    std::vector<Field> fields;
    void addField(const std::string& fieldName, const std::string& fieldValue);
};

class Table {
public:
    std::string tableName;
    std::vector<std::string> columnNames;
    std::vector<Row> rows;

    Table(const std::string& name);
    void addColumn(const std::string& columnName);
    void addRow(const Row& row);
};

#endif
