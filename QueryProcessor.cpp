#include "QueryProcessor.h"
#include <sstream>
#include <algorithm>
#include "FileManager.h"

void executeQuery(Table& table, const std::string& query) {
    std::istringstream ss(query);
    std::string command;
    ss >> command;

    if (command == "SELECT") {
        std::cout << "Table: " << table.tableName << "\n";
        for (const auto& col : table.columnNames) {
            std::cout << col << "\t";
        }
        std::cout << "\n---------------------\n";

        for (const auto& row : table.rows) {
            for (const auto& field : row.fields) {
                std::cout << field.value << "\t";
            }
            std::cout << "\n";
        }
    }





    else if (command == "INSERT") {
        std::string intoKeyword, tableName, valuesKeyword, values;
        ss >> intoKeyword >> tableName >> valuesKeyword;

        if (intoKeyword != "INTO" || valuesKeyword != "VALUES") {
            std::cerr << "Syntax Error: Expected 'INTO' and 'VALUES'.\n";
            return;
        }

        std::getline(ss, values);
        values.erase(std::remove(values.begin(), values.end(), '('), values.end());
        values.erase(std::remove(values.begin(), values.end(), ')'), values.end());

        std::istringstream valueStream(values);
        std::vector<std::string> rowValues;
        std::string val;
        while (std::getline(valueStream, val, ',')) {
            rowValues.push_back(val);
        }

        if (rowValues.size() != table.columnNames.size()) {
            std::cerr << "Error: Column count mismatch.\n";
            return;
        }

        Row newRow;
        for (size_t i = 0; i < table.columnNames.size(); ++i) {
            if (table.isPrimaryKeyDuplicate(table.columnNames[i], rowValues[i])) {
                std::cerr << "Error: Primary key violation.\n";
                return;
            }
            newRow.addField(table.columnNames[i], rowValues[i]);
        }
        table.addRow(newRow);
        FileManager::saveTable(table);
        std::cout << "Inserted new row.\n";
    }





    else if (command == "DELETE") {
        std::string fromKeyword, tableName, whereKeyword;
        ss >> fromKeyword >> tableName >> whereKeyword;
    
        if (fromKeyword != "FROM" || whereKeyword != "WHERE") {
            std::cerr << "Syntax Error: Expected 'FROM' and 'WHERE'.\n";
            return;
        }
    
        std::string condition;
        std::getline(ss, condition);
        condition.erase(std::remove(condition.begin(), condition.end(), ' '), condition.end());
    
        bool useAnd = condition.find("AND") != std::string::npos;
        bool useOr = condition.find("OR") != std::string::npos;
    
        std::vector<std::pair<std::string, std::string>> conditions;
        std::istringstream condStream(condition);
        std::string part;
        
        while (std::getline(condStream, part, useAnd ? 'A' : 'O')) { // Splitting on AND or OR
            size_t eqPos = part.find('=');
            if (eqPos != std::string::npos) {
                std::string col = part.substr(0, eqPos);
                std::string val = part.substr(eqPos + 1);
                conditions.push_back({col, val});
            }
        }
    
        table.rows.erase(std::remove_if(table.rows.begin(), table.rows.end(), [&](const Row& row) {
            bool match = useAnd;
            for (const auto& cond : conditions) {
                bool found = false;
                for (const auto& field : row.fields) {
                    if (field.name == cond.first && field.value == cond.second) {
                        found = true;
                        break;
                    }
                }
                if (useAnd)
                    match &= found; // AND condition: all must be true
                else
                    match |= found; // OR condition: at least one must be true
            }
            return match;
        }), table.rows.end());
    
        FileManager::saveTable(table);
        std::cout << "Deleted rows matching condition.\n";
    }
    






else if (command == "JOIN") {
    std::string table1Name, onKeyword, table2Name, condition;
    ss >> table1Name >> onKeyword >> table2Name;

    if (onKeyword != "ON") {
        std::cerr << "Syntax Error: Expected 'ON'.\n";
        return;
    }

    std::getline(ss, condition);
    condition.erase(std::remove(condition.begin(), condition.end(), ' '), condition.end());

    std::string col1, col2;
    std::istringstream conditionStream(condition);
    std::getline(conditionStream, col1, '=');
    std::getline(conditionStream, col2);

    Table table1(table1Name), table2(table2Name);
    FileManager::loadTable(table1);
    FileManager::loadTable(table2);

    std::cout << "Joined Table:\n";
    for (const auto& col : table1.columnNames) std::cout << col << "\t";
    for (const auto& col : table2.columnNames) std::cout << col << "\t";
    std::cout << "\n-------------------------------------------------\n";

    for (const auto& row1 : table1.rows) {
        std::string joinValue;
        for (const auto& field : row1.fields) {
            if (field.name == col1) {
                joinValue = field.value;
                break;
            }
        }

        Row* matchedRow = table2.findRowByColumn(col2, joinValue);
        if (matchedRow) {
            for (const auto& field : row1.fields) std::cout << field.value << "\t";
            for (const auto& field : matchedRow->fields) std::cout << field.value << "\t";
            std::cout << "\n";
        }
        }
    }
}





Table QueryProcessor::leftJoin(const Table& leftTable, const Table& rightTable, const std::string& joinColumn) {
    Table result("LeftJoin_" + leftTable.tableName + "_" + rightTable.tableName);

    // Adding columns from both tables
    result.columnNames = leftTable.columnNames;
    result.columnNames.insert(result.columnNames.end(), rightTable.columnNames.begin(), rightTable.columnNames.end());

    // Performing LEFT JOIN
    for (const auto& leftRow : leftTable.rows) {
        Row newRow;
        bool matchFound = false;

        for (const auto& rightRow : rightTable.rows) {
            std::string leftValue, rightValue;
            
            // Get the join column value for both tables
            for (const auto& field : leftRow.fields) {
                if (field.name == joinColumn) {
                    leftValue = field.value;
                    break;
                }
            }
            for (const auto& field : rightRow.fields) {
                if (field.name == joinColumn) {
                    rightValue = field.value;
                    break;
                }
            }

            // If values match, merge the rows
            if (leftValue == rightValue) {
                matchFound = true;
                newRow = leftRow;  // Copy left row
                for (const auto& field : rightRow.fields) {
                    newRow.addField(field.name, field.value);
                }
                result.addRow(newRow);
            }
        }

        // If no match found, add the left row with empty values for the right table
        if (!matchFound) {
            newRow = leftRow;  
            for (const auto& col : rightTable.columnNames) {
                newRow.addField(col, "NULL");
            }
            result.addRow(newRow);
        }
    }
    return result;
}