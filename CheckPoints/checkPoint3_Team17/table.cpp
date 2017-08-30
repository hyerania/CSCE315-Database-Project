#include "table.h"
#include <set>
using namespace std;

// Default constructor
Table::Table() {}
// Constructor that takes in a vector of attribute names
Table::Table(std::vector<std::string> attributeNames) :tableAttributes(attributeNames) {}
// Copy constructor
Table::Table(const Table& t) {
	tableKey = t.tableKey;
	tableAttributes = t.tableAttributes;
	tableRecord = t.tableRecord;
}
// Destructor
Table::~Table() {}

// get key of table 
std::string Table::getTableKey() const {
	return tableKey;
}

// set key for table 
void Table::specifyKey(const std::string& key) {
	for (tableAttributesItr = tableAttributes.begin(); tableAttributesItr != tableAttributes.end(); ++tableAttributesItr) {
		if (key == *tableAttributesItr) {
			tableKey = key;
			return;
		}
	}
	if (tableAttributesItr == tableAttributes.end()) {
		std::cout << "No attribute name matches with the specified key value. Key could not be established." << std::endl;
	}
	return;
}

//add a new column to the table 
void Table::addAttribute(std::string& attributeName) {
	bool found = false;
	tableAttributesItr = tableAttributes.begin();
	for (; tableAttributesItr != tableAttributes.end(); ++tableAttributesItr) {
		if (attributeName == *tableAttributesItr) {
			found = true;
		}
	}

	if (!found) {
		tableAttributes.push_back(attributeName);
		for (tableRecordItr = tableRecord.begin(); tableRecordItr != tableRecord.end(); ++tableRecordItr) {
			(*tableRecordItr).extendRecord();
		}
	}
	
}
// delete a column from the table 
void Table::deleteAttribute(std::string& attributeName) {
	bool found = false;
	int foundIndex = 0;
	tableAttributesItr = tableAttributes.begin();
	for (; tableAttributesItr < tableAttributes.end(); ++tableAttributesItr) {
		if (attributeName == *tableAttributesItr) {
			found = true;
			break;
		}
		foundIndex++;
	}
	if (found) {
		tableAttributes.erase(tableAttributes.begin()+foundIndex);
		for (tableRecordItr = tableRecord.begin(); tableRecordItr != tableRecord.end(); ++tableRecordItr) {
			(*tableRecordItr).discard(foundIndex);
		}
	}
	
}
// add a record to the table 
void Table::insertRecord(Record& record) {
	if (record.getRecordSize() == tableAttributes.size()) {
		tableRecord.push_back(record);
	}
	return;
}

// get all attributes name from the table 
std::vector<std::string> Table::getAttributeNames() {
	std::vector<std::string> result;
	for (tableAttributesItr = tableAttributes.begin(); tableAttributesItr != tableAttributes.end(); ++tableAttributesItr) {
		result.push_back(*tableAttributesItr);
	}
	return result;
}

// get size of table (the number of records) 
int Table::getTableSize() {
	return tableRecord.size();
}

// join 2 tables into 1
Table Table::crossJoin(Table& table1, Table& table2) {
	
	Table resultTable;
	int expectedSize = (table1.tableRecord.size()) * (table2.tableRecord.size());
	std::vector<Record> tempVect (expectedSize);
	resultTable.tableRecord = tempVect;

	string dup = "";
	
	std::vector<std::string> attr1 = table1.getAttributeNames();
	std::vector<std::string> attr2 = table2.getAttributeNames();
	for (int i = 0 ; i < attr1.size(); ++i) {
		resultTable.addAttribute(attr1.at(i));
	}

	for (int i = 0 ; i < attr2.size(); ++i) {
		resultTable.addAttribute(attr2.at(i));
	}
	
	for (int i = 0; i < attr2.size(); ++i){
		for (int j = 0; j < attr1.size(); ++j){
			if (attr2.at(i) == attr1.at(j)){
				dup = attr2.at(i);
			}
		}
	}

	Table tableTemp(table2);
	tableTemp.deleteAttribute(dup);
	
	int expectedAttr1 = table1.tableAttributes.size();
	int expectedAttr2 = tableTemp.tableAttributes.size();
	int totalNumAttribute = resultTable.getAttributeNames().size();
	
	auto it = resultTable.tableRecord.begin();
	for (int i = 0; i < table1.getTableSize(); ++i) {
		for (int j = 0; j < tableTemp.getTableSize(); ++j){
			for (int k = 0; k < expectedAttr1; ++k){
				(*it)[k] = (table1.tableRecord.at(i))[k];
			}
			++it;
		}
	}

	it = resultTable.tableRecord.begin();
	for (int i = 0; i < table1.getTableSize(); ++i) {
		for (int j = 0; j < table2.getTableSize(); ++j) {
			for (int k = expectedAttr1; k < totalNumAttribute; ++k){
				(*it)[k] = (tableTemp.tableRecord.at(j))[k - expectedAttr1];
			}
			++it;
		}
	}

	return resultTable;
}
// natural join 2 tables
Table Table::naturalJoin(Table& table1, Table& table2) {
	bool exist = false;
	int t2KeyPos = -1;
	int resultKeyPos = -1;
	std::string resultKey = table1.getTableKey();
	if (resultKey == "") {
		std::cout << "Key for the first table must be specified" <<std::endl;
	}
	Table resultTable(table1);
	std::vector<std::string> attr2 = table2.getAttributeNames();
	for (int i = 0 ; i < attr2.size(); ++i) {
		if (attr2.at(i) == resultKey) {
			t2KeyPos = i;
			exist = true;
		}
		resultTable.addAttribute(attr2.at(i));
	}

	if (exist){
		std::vector<std::string> attR = resultTable.getAttributeNames();
		for (int i = 0; i < attR.size(); ++i){
			if (attR.at(i) == resultKey){
				resultKeyPos = i;
				break;
			}
		}
		
		string currKey;
		int insertIndex = 0;
		int numElementsT2 = (table2.getAttributeNames().size());
		auto it = resultTable.tableRecord.begin();
		
		
		for (; it != resultTable.tableRecord.end(); ++it){         //for each record in resultTable
			currKey = (*it)[resultKeyPos];
			insertIndex = (table1.getAttributeNames()).size();
			for (auto it2 = table2.tableRecord.begin(); it2 != table2.tableRecord.end(); ++it2) {		// for each record in the second table
				if ((*it2)[t2KeyPos] == currKey){					// search for the one with the shared key with currentKey
					for (int i = 0; i < numElementsT2; ++i){	
						if (i != t2KeyPos){
							(*it)[insertIndex] = (*it2)[i];
							++ insertIndex;
						}
					}
				}
			}
		}
		
	
	}
	
	
	return resultTable;
}
// routines, return count, max, and min
std::tuple<std::string, std::string, std::string> Table::findRoutine(const std::string& attributeName) {
	bool found = false;
	int foundIndex = 0;
	int findCount = 0;
	std::string count;
	std::string tempMin = "";
	std::string tempMax = "";

	for (tableAttributesItr = tableAttributes.begin(); tableAttributesItr != tableAttributes.end(); ++tableAttributesItr) {
		if (attributeName == *tableAttributesItr) {
			found = true;
			break;
		}
		foundIndex++;
	}

	if (found) {
		tempMin = (*tableRecord.begin())[foundIndex];
		tempMax = (*tableRecord.begin())[foundIndex];
		for (tableRecordItr = tableRecord.begin(); tableRecordItr != tableRecord.end(); ++tableRecordItr) {
			// find Count
			std::string compare = (*tableRecordItr)[foundIndex];
			if (compare != "NULL") {
				findCount++;
			}
			// find Max
			if (compare > tempMax && compare != "NULL") {
				tempMax = compare;
			}
			// find Min
			if (compare < tempMin) {
				tempMin = compare;
			}
		}
		count = std::to_string(findCount);
	}

	else {
		std::cout << "Attribute does not exist." << std::endl;
	}
	return std::make_tuple(count, tempMax, tempMin);
}

