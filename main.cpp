#include <iostream>
#include "Table.h"
#include "QueryProcessor.h"
#include "FileManager.h"

int main() {
    // ✅ Creating a Table
    Table students("Students");
    students.addColumn("ID");
    students.addColumn("Name");
    students.addColumn("Age");

    Table courses("Courses");
    courses.addColumn("ID");
    courses.addColumn("Course");

    // ✅ Inserting Sample Data
    executeQuery(students, "INSERT INTO Students VALUES (1, John, 20)");
    executeQuery(students, "INSERT INTO Students VALUES (2, Alice, 22)");
    executeQuery(students, "INSERT INTO Students VALUES (3, Bob, 21)");

    executeQuery(courses, "INSERT INTO Courses VALUES (1, Math)");
    executeQuery(courses, "INSERT INTO Courses VALUES (2, Physics)");
    executeQuery(courses, "INSERT INTO Courses VALUES (4, Chemistry)");  // No matching student

    // ✅ Displaying Tables
    std::cout << "\n--- Students Table ---\n";
    executeQuery(students, "SELECT");

    std::cout << "\n--- Courses Table ---\n";
    executeQuery(courses, "SELECT");

    // ✅ Deleting a record
    executeQuery(students, "DELETE FROM Students WHERE ID=3");

    std::cout << "\n--- Students Table After Deletion ---\n";
    executeQuery(students, "SELECT");

    // ✅ Testing JOIN
    std::cout << "\n--- INNER JOIN Students & Courses ON ID ---\n";
    executeQuery(students, "JOIN Students ON Courses");

    // ✅ Testing LEFT JOIN
    std::cout << "\n--- LEFT JOIN Students & Courses ON ID ---\n";
    Table leftJoinTable = QueryProcessor::leftJoin(students, courses, "ID");
    for (const auto& row : leftJoinTable.rows) {
        for (const auto& field : row.fields) {
            std::cout << field.value << "\t";
        }
        std::cout << "\n";
    }

    return 0;
}
