// Members: My Pham, Sneha Santani, Leslie Escalante
// Team 17 - section 506

#pragma once

#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "table.h"

class Database {

public:
	// Default constructor
	Database();
	// Destructor
	~Database();

	// add a table to the database 
	void addTable(const std::string& name, Table& table);
	// delete a table from the database
	void dropTable(const std::string& name);
	// return list of table NAMES
	std::vector<std::string> listTables();
	// return vector of Table object 
	std::vector<Table> getTables();
	// Querry
	Table Querry(std::string Select, std::string From, std::string Where);

private:
	// std::vector<Table> database;
	// std::vector<Table>::iterator databaseItr;
	std::map <std::string, Table> database;
	std::map <std::string,Table>::iterator databaseItr;
};

#endif