// DatabaseTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DatabaseTest.h"
#include "Database.h"
#include <assert.h>
#include <vector>
#include <string>
#include <iostream>

/****************
*  RECORD TESTS
*****************/

void DatabaseTest::record() {
	//Creates a record of size 2 and assigns it's attributes, then checks to see if it fails when it should
	Database::Record r = Database::Record(2);
	assert(("Record Size function not working", r.getSize() == 2));
	r.set(0, "Hello");
	assert(("String not saved successfully", r.get(0) == "Hello"));
	r.set(1, "World");
	assert(("String not saved successfully", r.get(1) == "World"));
	assert(("Set Passed when it shouldn't have", r.set(2, "World") == false));
}

/****************
*  TABLE TESTS
*****************/

void DatabaseTest::tableListConstructor() {
	//Create a table with 3 attributes, return its attributes and assert that the size of the attributes is three
	std::vector<std::string> attributes1;
	attributes1.push_back("attribute1");
	attributes1.push_back("attribute2");
	attributes1.push_back("attribute3");
	Database::Table tb1(attributes1);
	std::vector<std::string> attributes2 = tb1.getAttributes();
	assert(("Table instantiated with three attributes", attributes2.size() == 3));
}

void DatabaseTest::addAttribute() {
	//Create an empty table, add an attribute to it, assert that the size is one
	Database::Table tb;
	tb.addAttribute("attribute");
	std::vector<std::string> attributes = tb.getAttributes();
	assert(("Attribute added", attributes[0] == "attribute"));
}

void DatabaseTest::deleteAttribute() {
	//Create a table with one attribute, delete it and assert the size is zero
	std::vector<std::string> attributes1;
	attributes1.push_back("attribute");
	Database::Table tb(attributes1);
	tb.deleteAttribute("attribute");
	std::vector<std::string> attributes2 = tb.getAttributes();
	assert(("Attribute deleted", attributes2.size() == 0));
}

void DatabaseTest::insertRecord() {
	//Insert a record into the table, assert that the size is one
	Database::Record r(1);
	std::vector<std::string> attributes1;
	attributes1.push_back("attribute");
	Database::Table tb(attributes1);
	tb.insert(r);
	assert(("Record inserted", tb.getSize() == 1));
}

void DatabaseTest::getAttributes() {
	//Instantiates a table with an attribute and compares 
	//with the same attribute, asserts that they are the same
	std::vector<std::string> attributes;
	attributes.push_back("attribute");
	Database::Table tb = Database::Table(attributes);
	assert(("Correct attribute returned from table", tb.getAttributes()[0] == "attribute"));
}

void DatabaseTest::getTableSize() {
	//Creates a table with two attributes, asserts that the size is two
	std::vector<std::string> attributes;
	attributes.push_back("attribute1");
	attributes.push_back("attribute2");
	Database::Table tb = Database::Table(attributes);
	Database::Record r(2);
	Database::Record r2(2);
	tb.insert(r);
	tb.insert(r2);
	assert(("Returned correct size of table", tb.getSize() == 2));
}

void DatabaseTest::tableBegin() {
	//Creates a table with two records, asserts that begin() returned an object of tblIterator
	Database::Record r1(1);
	Database::Record r2(2);
	r1.set(0, "char1");
	r2.set(0, "char2");
	std::vector<std::string> attributes = { "Victoria", "Kevin" }; // <3

	Database::Table tb(attributes); // This was not part of the original test.

	tb.insert(r1);
	tb.insert(r2);

	assert(("Correct begin() iterator", tb.begin()->get(0) == "char1"));
}

void DatabaseTest::tableEnd() {
	//Creates an empty table, asserts that begin() and end() are equal
	std::vector<std::string> att = { "Victoria", "Kevin" }; // <3
	Database::Table tb = Database::Table(att);

	Database::tblIterator it = tb.begin();
	assert(("Empty Table Iterator Check", it == tb.end()));

	Database::Record rd(2);
	rd.set(0, "Love");
	rd.set(1, "You");

	tb.insert(rd);

	assert(("Non-Empty Begin vs End", it != tb.end()));

	++it;
	assert(("After increment", it == tb.end()));

	assert(("Correct end() iterator", tb.end() != tb.begin()));
}

void DatabaseTest::join() {
	//Creates 4 tables to test the natural join and cross join functions
	std::vector<std::string> attributes1 = { "key", "not key", "key2" };
	Database::Table t1(attributes1);
	t1.defineKey("key");
	std::vector<std::string> attributes2 = { "a", "b", "c", "key2" };
	Database::Table t2(attributes2);
	t2.defineKey("key2");
	Database::Table t3 = t2.crossJoin(t1, t2);
	Database::Table t4 = t2.naturalJoin(t1, t2);
	Database::Record r1(3);
	r1.set(0, "Kevin");
	Database::Record r2(3);
	r2.set(0, "Victoria");
	Database::Record r3(3);
	r3.set(0, "Yerania");
	t1.insert(r1);
	t1.insert(r2);
	t1.insert(r3);
	//Tests the routines function on one table but with one attribute that should be found and one that should not
	std::cout << t1.routines("key").find("min")->second << std::endl;
	std::cout << t1.routines("NotIntTable").find("min")->second << std::endl;
	std::cout << t1.routines("key").find("max")->second << std::endl;
	std::cout << t1.routines("NotIntTable").find("max")->second << std::endl;
	std::cout << t1.routines("key").find("count")->second << std::endl;
	std::cout << t1.routines("NotIntTable").find("count")->second << std::endl;
}


/******************
*  DATABASE TESTS
*******************/

void DatabaseTest::addDropTable() {
	//Create an empty database and assert that it has no tables
	Database::Database db = Database::Database();
	assert(("Empty Database", db.getTables().size() == 0));

	//Create two tables and add them to the db, assert that the db is of size two
	Database::Table t1 = Database::Table();
	Database::Table t2 = Database::Table();
	db.addTable(t1, "Table 1");
	db.addTable(t2, "Table 2");
	assert(("Two tables added", db.getTables().size() == 2));

	//List the tables and verify that the names are correct
	std::vector<std::string> tList = db.listTables();
	assert(("Table 1 Name Correct", tList.at(0) == "Table 1"));
	assert(("Table 2 Name Correct", tList.at(1) == "Table 2"));

	//Remove the two tables from the db, assert that is now emptys
	db.dropTable("Table 1");
	db.dropTable("Table 2");
	assert(("Two tables deleted", db.getTables().size() == 0));
}

void DatabaseTest::query() {

	//Create 10 records with 3 numbers and add them to table t
	Database::Table t = Database::Table(std::vector<std::string>{"a1", "a2", "a3"});
	for (int i = 0; i < 10; i++) {
		Database::Record r = Database::Record(3);
		//Insert numbers 1-30 into records
		for (int j = 0; j < 3; j++) {
			r.set(j, std::to_string((3 * i) + j + 1));
		}
		t.insert(r);
	}

	//Create test db
	Database::Database db = Database::Database();
	db.addTable(t, "Test");

	//Test wildcard operator
	Database::Table queriedTable = db.query("*", "Test", "True");

	int i = 0;
	for (Database::tblIterator it = queriedTable.begin(); it != queriedTable.end(); ++it) {
	for(unsigned int j = 0; j < it->getSize();j++){
	assert(("SELECT * FROM Test WHERE True",
	it->get(j) == std::to_string((3 * i) + j + 1)));
	}
	i++;
	}
	//Test select single attribute
	queriedTable = db.query("a1", "Test", "True");
	i = 1;
	for (Database::tblIterator it = queriedTable.begin(); it != queriedTable.end(); ++it) {
	assert(("SELECT a1 FROM Test WHERE True",
	it->get(0) == std::to_string(i)));
	i += 3;
	}
	//Test where clause comparisons
	queriedTable = db.query("a1", "Test", "a1 == 1");
	i = 1;
	for (Database::tblIterator it = queriedTable.begin(); it != queriedTable.end(); ++it) {
	assert(("SELECT a1 FROM Test WHERE a1 == 1",
	it->get(0) == std::to_string(i)));
	i += 3;
	}
	queriedTable = db.query("a1", "Test", "a1 > 1");
	i = 4;
	for (Database::tblIterator it = queriedTable.begin(); it != queriedTable.end(); ++it) {
	assert(("SELECT * FROM Test WHERE True",
	it->get(0) == std::to_string(i)));
	i += 3;
	}
	queriedTable = db.query("a1", "Test", "a1 < 19");
	i = 1;
	for (Database::tblIterator it = queriedTable.begin(); it != queriedTable.end(); ++it) {
	assert(("Queried records match original records",
	it->get(0) == std::to_string(i)));
	i += 3;
	}
	queriedTable = db.query("a1", "Test", "a1 =< 19");
	i = 1;
	for (Database::tblIterator it = queriedTable.begin(); it != queriedTable.end(); ++it) {
	assert(("Queried records match original records",
	it->get(0) == std::to_string(i)));
	i += 3;
	}
	queriedTable = db.query("a1", "Test", "a1 >= 1");
	i = 1;
	for (Database::tblIterator it = queriedTable.begin(); it != queriedTable.end(); ++it) {
	assert(("Queried records match original records",
	it->get(0) == std::to_string(i)));
	i += 3;
	}
}

void DatabaseTest::QueryTest() {
	using namespace std; // Remove Later

	cout << "Beginning Query Test" << endl;

	Database::Database db;
	std::vector<std::string> attributes = { "ID", "Name", "Color", "Food" };
	Database::Table tb(attributes);

	for (int i = 0; i < 10; i++) { // Populate a database to query from.
		Database::Record rd(4);
		rd.set(0, to_string(i));
		rd.set(1, "Kevin" + to_string(i));
		rd.set(2, "Red" + to_string(i));
		rd.set(3, "Apples" + to_string(i));
		tb.insert(rd);
	}

	cout << "--------------------------- ORIGINAL TABLE --------------------------" << endl;
	tb.printTable();
	
	db.addTable(tb, "Test");

	cout << endl << endl << "!!------------------------- QUERY TABLE ------------------------!!" << endl;

	Database::Table result = db.query("ID, Name, Food", "Test", "True");
	result.printTable();


}

void DatabaseTest::run() {
	/*record();
	std::cout << "Record Tests Passed" << std::endl;
	tableListConstructor();
	addAttribute();
	deleteAttribute();
	insertRecord();
	getAttributes();
	getTableSize();
	tableBegin();
	tableEnd();
	join();
	std::cout << "Table Tests Passed" << std::endl;
	addDropTable();
	//query();
	std::cout << "Database Tests Passed" << std::endl;
	std::cout << "All Tests Passed" << std::endl;*/

	std::cout << "Kevin's Query Test" << std::endl;
	QueryTest();
	std::cout << "Completed Test" << std::endl;

}

int main() {
	DatabaseTest::run();
}