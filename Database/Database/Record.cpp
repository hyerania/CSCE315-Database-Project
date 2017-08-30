// Record.cpp : Defines the exported Record functions for the DLL application.
//

#include "Database.h"
#include "stdafx.h"

Database::Record::Record(unsigned int size) {
	record = std::vector<std::string>(size, "NULL");
}

unsigned int Database::Record::getSize() {
	return record.size();
}

bool Database::Record::set(unsigned int index, std::string characteristic) {
	if (index < record.size()) {
		record[index] = characteristic;
		return true;
	}
	return false;
}

std::string Database::Record::get(unsigned int index) {
	if (index < record.size()) {
		return record[index];
	}
	return "";
}

bool Database::Record::remove(unsigned int index) {
	if (index >= record.size()) return false;
	record.erase(record.begin() + index);
	return true;
}


void Database::Record::testLinkage() {
	std::cout << "Size: " << getSize() << std::endl;
	set(4, "hello");
	std::cout << get(4) << std::endl;
	std::cout << get(3) << std::endl;
	std::cout << "Record: All Functions Work!" << std::endl;
}