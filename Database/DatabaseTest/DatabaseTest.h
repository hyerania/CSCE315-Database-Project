#pragma once

class DatabaseTest {
public:
	//Record Tests
	static void record();
	//Table Tests
	static void tableListConstructor();
	static void addAttribute();
	static void deleteAttribute();
	static void insertRecord();
	static void getAttributes();
	static void getTableSize();
	static void tableBegin();
	static void tableEnd();
	static void join();
	//Database Tests
	static void addDropTable();
	static void query();
	static void QueryTest();
	//Run all tests
	static void run();
};