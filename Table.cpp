#include "Table.h"

void Row::addField(const std::string& fieldName, const std::string& fieldValue) {
    fields.push_back({fieldName, fieldValue});
}

Table::Table(const std::string& name) : tableName(name) {}

void Table::addColumn(const std::string& columnName) {
    columnNames.push_back(columnName);
}

void Table::addRow(const Row& row) {
    rows.push_back(row);
}
