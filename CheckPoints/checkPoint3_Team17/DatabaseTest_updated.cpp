//
// Created by Kevin Nguyen on 2/20/17.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "stdafx.h"
#include "catch.hpp"
#include "dlibrary.h"
#include <iostream>
#include <vector>


TEST_CASE("Record Default Constructor", "[record]") {
    Record rd;
    REQUIRE(true);
}

TEST_CASE("Get Size","[record]") {
    Record rd;
    REQUIRE(rd.getRecordSize() == 0);
}

TEST_CASE("Constructor Arbitrary Size", "[record]") {
    // Functionality does not exist.
    REQUIRE(false);
}

TEST_CASE("Set and Get Values","[record]") {
    // Functionality does not exist to create record of arbitrary size. Read rubric for more information.
    Record rd(3);
    rd[2] = "Apples";
    REQUIRE(rd.getRecordSize() == 3);
    REQUIRE(rd[0] == "NULL");
    REQUIRE(rd[1] == "NULL");
    REQUIRE(rd[2] == "Apples");
}

TEST_CASE("Assignment Operator","[record]") {
    Record rd(2);
    rd[1] = "Apples";
    Record rd2 = rd;
    rd2 = rd;
    REQUIRE(rd2.getRecordSize() == 2);
    REQUIRE(rd2[1] == "Apples");
    REQUIRE(rd2[0] == "NULL");
}

TEST_CASE("Default Constructor", "[table]") {
    Table tb;
    REQUIRE(true);
}

TEST_CASE("Attribute Constructor","[table]") {
    std::vector<std::string> attributeNames = { "ID", "Name", "Email", "School"};
    Table tb(attributeNames);
    REQUIRE(tb.getTableSize() == 0);
    REQUIRE(tb.getAttributeNames() == attributeNames);
}

TEST_CASE("Assignment Constructor","[table]") {
    std::vector<std::string> attributeNames = { "ID", "Name", "Email", "School"};
    Table tb(attributeNames);
    Table tb2 = tb;
    REQUIRE(tb2.getTableSize() == tb2.getTableSize());
    REQUIRE(tb2.getAttributeNames() == attributeNames);
    REQUIRE(tb2.getAttributeNames() == tb.getAttributeNames());
}

TEST_CASE("Get and Set Key","[table]") {
    std::vector<std::string> attributeNames = { "ID", "Name", "Email", "School"};
    Table tb(attributeNames);
    const std::string key = "ID";
    tb.specifyKey(key);
    REQUIRE(tb.getTableKey() == key);
}

TEST_CASE("Insert Record and Get Table Size", "[table]") {
    std::vector<std::string> attributeNames = { "ID", "Name"};
    Table tb(attributeNames);
    Record rd(2); // Will always not compile until functionality is written.
    rd[0] = "01";
    rd[1] = "Apples";
    tb.insertRecord(rd);
    REQUIRE(tb.getTableSize() == 1);
}

TEST_CASE("Add Attribute","[table]") {
    std::vector<std::string> attributeNames = { "ID", "Name", "Email", "School"};
    Table tb(attributeNames);
    std::string newAttribute = "Food";
    tb.addAttribute(newAttribute);
    attributeNames.push_back(newAttribute);
    REQUIRE(tb.getAttributeNames() == attributeNames);
}

TEST_CASE("Delete Attribute", "[table]") {
    std::vector<std::string> attributeNames = { "ID", "Name", "Email", "School"};
    Table tb(attributeNames);
    std::string deleteAttribute = "School";
    tb.deleteAttribute(deleteAttribute);
    attributeNames.pop_back();
    REQUIRE(tb.getAttributeNames() == attributeNames);
}

TEST_CASE("Cross Join", "[table]") {

    // Following this example: http://stackoverflow.com/questions/17759687/cross-join-vs-inner-join-in-sql-server-2008

    std::vector<std::string> attributeNames = { "TeacherID", "TeacherName"};
    Table teacher(attributeNames);

    Record rd(2);
    rd[0] = "T1";
    rd[1] = "Mary";
    Record rd2(2);
    rd[0] = "T2";
    rd[1] = "Jim";
    teacher.insertRecord(rd);
    teacher.insertRecord(rd2);

    std::vector<std::string> studentNames = { "StudentID", "TeacherID", "StudentName"};
    Table student(studentNames);

    Record st(3);
    st[0] = "S1";
    st[1] = "T1";
    st[2] = "Apples";
    Record st2(3);
    st2[0] = "S2";
    st2[1] = "T1";
    st2[2] = "Pies";

    student.insertRecord(st);
    student.insertRecord(st2);

    const Table* teacherTable = new Table(teacher);
    const Table* studentTable = new Table(student);

    Table randomTable = teacher.crossJoin(teacherTable, studentTable);
    std::vector<std::string> joinedAttributes = {"TeacherID", "TeacherName", "StudentName"};
    REQUIRE(randomTable.getTableSize() == 4);
    REQUIRE(randomTable.getAttributeNames() == joinedAttributes);
}

TEST_CASE("Natural Join", "[table]") {
    std::vector<std::string> items = {"ItemID", "Name", "CompanyID"};
    Table foodTable(items);

    Record rd1(3);
    rd1[0] = "01";
    rd1[1] = "Green Apples";
    rd1[2] = "01";

    Record rd2(3);
    rd2[0] = "02";
    rd2[1] = "Red Apples";
    rd2[2] = "01";

    Record rd3(3);
    rd3[0] = "03";
    rd3[1] = "Bananas";
    rd3[2] = "02";

    foodTable.insertRecord(rd1);
    foodTable.insertRecord(rd2);
    foodTable.insertRecord(rd3);

    std::vector<std::string> foodColors = { "CompanyID", "Colors"};
    Table foodColor(foodColors);

    Record fc1(2);
    fc1[0] = "01";
    fc1[1] = "Any";

    Record fc2(2);
    fc2[0] = "02";
    fc2[1] = "Yellow";

    foodColor.insertRecord(fc1);
    foodColor.insertRecord(fc2);

    Table natJoin = foodTable.naturalJoin(new Table(foodTable), new Table(foodColor));

    std::vector<std::string> attributeResults = {"ItemID", "Name", "CompanyID", "Colors"};
    REQUIRE(natJoin.getAttributeNames() == attributeResults);
    REQUIRE(natJoin.getTableSize() == 3);
}

TEST_CASE("FindRoutine", "[table]") {
    std::vector<std::string> items = {"ItemID", "Name", "CompanyID"};
    Table foodTable(items);

    Record rd1(3);
    rd1[0] = "01";
    rd1[1] = "Green Apples";
    rd1[2] = "01";

    Record rd2(3);
    rd2[0] = "02";
    rd2[1] = "Red Apples";
    rd2[2] = "01";

    Record rd3(3);
    rd3[0] = "03";
    rd3[1] = "Bananas";
    rd3[2] = "02";

    foodTable.insertRecord(rd1);
    foodTable.insertRecord(rd2);
    foodTable.insertRecord(rd3);
    std::tuple<std::string, std::string, std::string> result = foodTable.findRoutine("ItemID");
    REQUIRE(std::get<0>(result) == "3");
    REQUIRE(std::get<1>(result) == "03");
    REQUIRE(std::get<2>(result) == "01");
}

TEST_CASE("Iterators", "[table]") {
    // Iterators need to be made public to be used.
    REQUIRE(false);
}

TEST_CASE("Database Constructor", "[database]") {
    Database db;
    REQUIRE(db.getTables().size() == 0);
    REQUIRE(db.listTables().size() == 0);
}

TEST_CASE("Add Table", "[database]") {
    Database db;
    Table tbl;
    db.addTable(tbl, "Table1");
    REQUIRE(db.listTables().size() == 1);
    REQUIRE(db.listTables()[0] == "Table1");
}

TEST_CASE("Drop Table", "[database]") {
    Database db;
    Table tbl;
    db.addTable(tbl, "Table1");
    db.dropTable("Table1");
    REQUIRE(db.getTables().size() == 0);
    REQUIRE(db.listTables().size() == 0);
}

TEST_CASE("Get Tables", "[database]") {
    Database db;
    Table tbl;
    db.addTable(tbl, "Table1");
    db.addTable(tbl, "Table2");
    db.addTable(tbl, "Table3");
    std::vector<std::string> tableNames = { "Table1", "Table2", "Table3" };
    REQUIRE(db.listTables() == tableNames);
}

TEST_CASE("Basic Query Test", "[database]") {
    Database db;
    std::vector<std::string> items = {"ItemID", "Name", "CompanyID"};
    Table foodTable(items);

    Record rd1(3);
    rd1[0] = "01";
    rd1[1] = "Green Apples";
    rd1[2] = "A";

    Record rd2(3);
    rd2[0] = "02";
    rd2[1] = "Red Apples";
    rd2[2] = "B";

    Record rd3(3);
    rd3[0] = "03";
    rd3[1] = "Bananas";
    rd3[2] = "C";

    foodTable.insertRecord(rd1);
    foodTable.insertRecord(rd2);
    foodTable.insertRecord(rd3);

    db.addTable(foodTable, "Food");
    Table tbl = db.Querry("ItemID, Name", "Food", "CompanyID='C'");

    REQUIRE(tbl.getTableSize() == 1);
    std::vector<std::string> names = {"ItemID", "Name"};
    REQUIRE(tbl.getAttributeNames() == names);
}