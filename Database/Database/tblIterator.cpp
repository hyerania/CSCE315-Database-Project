// tblIterator.cpp : Defines the exported tblIterator functions for the DLL application.
//

#include <iostream>
#include <string>
#include "Database.h"
#include "stdafx.h"

Database::Record* Database::tblIterator::operator->() {
	return &table->getRecord(value);
}

Database::tblIterator& Database::tblIterator::operator++() {
	value = value + 1;
	return *this;
}

bool Database::tblIterator::operator!=(tblIterator param) {
	if (param.value == value) {
		return false;
	}
	return true;
}

bool Database::tblIterator::operator==(tblIterator param) {
	if (param.value == value) {
		return true;
	}
	return false;
}