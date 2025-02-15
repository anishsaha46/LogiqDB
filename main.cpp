#include <iostream>
#include "Table.h"
#include "QueryProcessor.h"
#include "FileManager.h"

int main() {
    std::cout << "===== LogiqDb: Testing All Features =====\n";

    // ✅ Creating Tables
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

    // ✅ Displaying All Data
    std::cout << "\n--- Students Table ---\n";
    executeQuery(students, "SELECT");

    std::cout << "\n--- Courses Table ---\n";
    executeQuery(courses, "SELECT");

    // ✅ SELECT with WHERE Clause
    std::cout << "\n--- Selecting Students WHERE Age > 20 ---\n";
    executeQuery(students, "SELECT * FROM Students WHERE Age>20");

    std::cout << "\n--- Selecting Students WHERE Age < 22 AND Name != Bob ---\n";
    executeQuery(students, "SELECT * FROM Students WHERE Age<22 AND Name!=Bob");

    std::cout << "\n--- Selecting Students WHERE Name = Alice OR Age = 21 ---\n";
    executeQuery(students, "SELECT * FROM Students WHERE Name=Alice OR Age=21");

    // ✅ UPDATE Student Data
    std::cout << "\n--- Updating Alice's Age to 23 ---\n";
    executeQuery(students, "UPDATE Students SET Age=23 WHERE Name=Alice");
    executeQuery(students, "SELECT * FROM Students WHERE Name=Alice");

    // ✅ DELETE a Record
    std::cout << "\n--- Deleting Student with ID = 3 ---\n";
    executeQuery(students, "DELETE FROM Students WHERE ID=3");
    executeQuery(students, "SELECT");

    // ✅ INNER JOIN Example
    std::cout << "\n--- INNER JOIN Students & Courses ON ID ---\n";
    executeQuery(students, "JOIN Students ON Courses");

    // ✅ LEFT JOIN Example
    std::cout << "\n--- LEFT JOIN Students & Courses ON ID ---\n";
    Table leftJoinTable = QueryProcessor::leftJoin(students, courses, "ID");
    for (const auto& row : leftJoinTable.rows) {
        for (const auto& field : row.fields) {
            std::cout << field.value << "\t";
        }
        std::cout << "\n";
    }

    // ✅ Saving to File 
    std::cout << "\n--- Saving Students Table to File ---\n";
    FileManager::saveTable(students);

    // ✅ Loading from File 
    std::cout << "\n--- Loading Students Table from File ---\n";
    Table loadedStudents("Students");
    FileManager::loadTable(loadedStudents);
    executeQuery(loadedStudents, "SELECT");

    std::cout << "\n===== Testing Completed Successfully! =====\n";
    return 0;
}
