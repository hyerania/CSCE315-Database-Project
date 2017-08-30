// Database.cpp : Defines the exported Database functions for the DLL application.
//

#include <iostream>
#include "Database.h"
#include "stdafx.h"

typedef std::map<std::string, Database::Table> database;

Database::Database::Database() {}

/*
	If the Table already exists, do not replace the Table with
	a new table. Instead, return false.
*/
bool Database::Database::addTable(Table tbl, std::string name) {
	std::pair<database::iterator, bool> ret;
	ret = databaseTables.insert(std::pair<std::string, Table>(name, tbl));
	if (ret.second) {
		return true;
	}
	return false;
}

bool Database::Database::dropTable(std::string tblName) {
	int elementsErased = 0;
	elementsErased = databaseTables.erase(tblName);
	if (elementsErased == 1) {
		return true;
	}
	return false;
}

std::vector<std::string> Database::Database::listTables() {
	std::vector<std::string> tableNames;
	if (databaseTables.empty()) {
		std::cerr << "Database is Empty!" << std::endl;
	}
	else {
		for (database::iterator databaseTablesIterator = databaseTables.begin();
		databaseTablesIterator != databaseTables.end(); databaseTablesIterator++) {
			tableNames.push_back(databaseTablesIterator->first);
		}
	}
	return tableNames;
}

database Database::Database::getTables() {
	return databaseTables;
}

Database::Table Database::Database::query(std::string select, std::string from, std::string wherever) {
	std::cout << "Database: Query" << std::endl;

	table = findTable(from); // Search for the table. @TODO Throw error if no table found.

	Query query = Query(select, wherever, table); // Create a Query from the parameters passed.
	
	Table tb = query.getResult(); // Grab the result of the query.

	return tb; // Return the result.
}

void Database::Database::testLinkage() {
	Table table = Table();
	addTable(table,"Hello");
	std::cout << "Database Size: ";
	std::cout << getTables().size() << std::endl;
	for (unsigned int i = 0; i < listTables().size(); i++) {
		std::cout << listTables()[i] << std::endl;
	}
	dropTable("Hello");
	for (unsigned int i = 0; i < listTables().size(); i++) {
		std::cout << listTables()[i] << std::endl;
	}
	//query("Select", "From", "Where");
	std::cout << "Database: All Functions Work!" << std::endl;
}

Database::Table Database::Database::findTable(std::string from) {
	database::iterator databaseTablesIterator = databaseTables.find(from);
	return databaseTablesIterator->second;
}

void Database::Table::printTable() {
	using namespace std;

	cout << "Size: " << allRecords.size() << endl;
	cout << "-- Record Contents --" << endl;
	for (int i = 0; i < attributes.size(); ++i) {
		cout << " | " << attributes[i];
	}

	cout << " | " << endl;

	for (int i = 0; i < allRecords.size(); ++i) {
		Record rd = allRecords[i];
		for (int j = 0; j < rd.getSize(); j++) {
			cout << rd.get(j) << " ";
		}
		cout << endl;
	}
	
}

std::vector<Database::Record> Database::Database::findRecords() {
	return records;
}

void Database::Database::addRecords() {
	for (unsigned int i = 0; i < records.size(); i++) {
		outputTable.insert(records[i]);
	}
}