// Query.cpp : Defines the exported Query functions for the DLL application.
//

#include <iostream>
#include <sstream>
#include "Database.h"
#include "stdafx.h"

typedef std::map<std::string, Database::Table> database;


Database::Database::Query::Query(std::string select, std::string wherever, Table table) {
	originalTable = table;
	attributes = parseSelect(select, table);
	parsedWhere = parseWhere(wherever);
}

std::vector<std::string> Database::Database::Query::parseSelect(std::string select, Table table) {

	std::vector<std::string> tableAttributes; // End result table attribute names

	if (select == "*") { // Handling Wildcard
		tableAttributes = table.getAttributes();
	}
	else { // Handling arbitrary number of attribute names
		std::stringstream ss(select);
		std::string token;

		while (ss >> token) { // Grab a token, split by comma, 
			std::string delimiter = ",";
			std::string attribute = token.substr(0, token.find(delimiter));
			// @TODO Handle case where no space after comma
			tableAttributes.push_back(attribute);
		}

	}

	return tableAttributes;

}

std::vector<std::string> Database::Database::Query::getAttributes() {
	return attributes;
}

std::vector<std::string> Database::Database::Query::getParsedWhere() {
	return parsedWhere;
}

Database::Table Database::Database::Query::getResult() { // Generates the result of the query.

	/* Last step is to remove the attributes that were not present in the select query. The select query should be parsed in the constructor
	** and assigned to attributes. From this, the code below removes any attribute that is present in the where table but not in select. 
	*/
	std::vector<std::string> originalAttributes = originalTable.getAttributes();

	for (std::string str : originalAttributes) {
		if (std::find(attributes.begin(), attributes.end(), str) == attributes.end()) {
			originalTable.deleteAttribute(str);
		}
	}
	return originalTable;
}

std::string Database::Database::Query::Tokenizer(std::string& str) {
	return "";
}

std::vector<std::string> Database::Database::Query::parseWhere(std::string wherever) {
	std::vector<std::string> recordNames;
	return parsedWhere;
}