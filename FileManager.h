#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Table.h"
#include <fstream>

void saveTableToFile(const Table& table, const std::string& filename);
Table loadTableFromFile(const std::string& filename);

#endif
