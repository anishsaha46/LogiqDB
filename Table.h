#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

struct Field {
    std::string name;
    std::string value;
};

struct Row {
    std::vector<Field> fields;
    void addField(const std::string& name, const std::string& value) {
        fields.push_back({name, value});
    }
};

class Table {
public:
    std::string tableName;
    std::vector<std::string> columnNames;
    std::unordered_map<std::string, bool> primaryKeys;
    std::vector<Row> rows;

    Table(const std::string& name) : tableName(name) {}

    void addColumn(const std::string& columnName, bool isPrimaryKey = false) {
        columnNames.push_back(columnName);
        if (isPrimaryKey) {
            primaryKeys[columnName] = true;
        }
    }

    bool isPrimaryKey(const std::string& column) {
        return primaryKeys.find(column) != primaryKeys.end();
    }

    bool isPrimaryKeyDuplicate(const std::string& column, const std::string& value) {
        if (!isPrimaryKey(column)) return false;
        for (const auto& row : rows) {
            for (const auto& field : row.fields) {
                if (field.name == column && field.value == value) {
                    return true;
                }
            }
        }
        return false;
    }

    void addRow(const Row& row) {
        rows.push_back(row);
    }
};

#endif
