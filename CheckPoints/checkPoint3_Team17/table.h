// Members: My Pham, Sneha Santani, Leslie Escalante
// Team 17 - section 506
#pragma once

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include "record.h"

class Table {
public:
	// Default constructor
	Table();
	// Constructor that takes in a string represents the table name and a vector of attribute names
	Table(std::vector<std::string> attributeNames);
	// Copy constructor
	Table(const Table& t);
	// Destructor
	~Table();

	// get key of table 
	std::string getTableKey() const;
	// set key for table 
	void specifyKey(const std::string& key);

	//add a new column to the table 
	void addAttribute(std::string& attributeName);
	// delete a column from the table 
	void deleteAttribute(std::string& attributeName);
	// add a record to the table 
	void insertRecord(Record& record);
	// get all attributes name from the table 
	std::vector<std::string> getAttributeNames();
	// get size of table (the number of records) 
	int getTableSize();
	// join 2 tables into 1
	Table crossJoin(Table& table1, Table& table2);
	// natural join 2 tables
	Table naturalJoin(Table& table1, Table& table2);
	// routines, return count, min, and max
	std::tuple<std::string, std::string, std::string> findRoutine(const std::string& attributeName);

	
	
public:
	std::string tableKey;
	// table is a vector of attribute name 
	std::vector<std::string> tableAttributes;
	std::vector<Record> tableRecord;
	std::vector<std::string>::iterator tableAttributesItr;
	std::vector<Record>::iterator tableRecordItr;
};
#endif