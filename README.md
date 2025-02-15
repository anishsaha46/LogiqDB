# Simple Database System

This project implements a basic database system with features such as:

* **Table Creation:** Create tables with specified columns and data types.
* **Data Insertion:** Insert rows of data into tables.
* **Data Retrieval:** Select and display data from tables.
* **Data Deletion:** Delete rows from tables based on conditions.
* **Data Update:** Update rows in tables based on conditions.
* **Inner Join:** Perform inner join operations between two tables.
* **Left Join:** Perform left join operations between two tables.

**Getting Started:**

1. **Compile the code:**
   - Make sure you have a C++ compiler (like g++) installed.
   - Compile the code using a command like:
     ```bash
     g++ -o database_system main.o Table.o QueryProcessor.o FileManager.o
     ```

2. **Run the program:**
   - Execute the compiled program:
     ```bash
     ./database_system
     ```

**Usage:**

*   The program currently supports the following basic SQL-like queries:
    *   `INSERT INTO table_name VALUES (value1, value2, ...)`
    *   `SELECT`
    *   `SELECT * FROM table_name WHERE condition`
    *   `UPDATE table_name SET column=value WHERE condition`
    *   `DELETE FROM table_name WHERE condition`
    *   `JOIN table1 ON table2` (currently supports basic inner joins)
    *   `LEFT JOIN table1 ON table2`

*   The program uses plain text files to store table data.

**Limitations:**

*   Limited query support (no complex joins, aggregations, etc.).
*   Basic error handling.
*   No data type enforcement.
*   No indexing for improved performance.

**Future Enhancements:**

*   Implement more advanced query features (e.g., WHERE clause with more operators, GROUP BY, ORDER BY).
*   Add support for data types (e.g., integers, floats, dates).
*   Implement indexing for faster data retrieval.
*   Improve error handling and data validation.
*   Consider using a database library (like SQLite) for more robust functionality.

**Note:**

This is a basic implementation for educational purposes. For production-level database systems, consider using established database solutions.

This `README.md` provides a concise overview of your project, including its features, usage instructions, limitations, and potential areas for future enhancements. You can customize it further to include more specific details and instructions relevant to your project.
