#pragma once  

#ifdef DATABASE_EXPORTS  
#define DATABASE_API __declspec(dllexport)   
#else  
#define DATABASE_API __declspec(dllimport)   
#endif  

#include <iostream>
#include <vector>
#include <map>
#include <string>

namespace Database {

	class Record {
	private:
		std::vector<std::string> record;

	public:
		DATABASE_API Record(unsigned int size);
		DATABASE_API unsigned int getSize();
		DATABASE_API bool set(unsigned int index, std::string characteristic);
		DATABASE_API std::string get(unsigned int index);
		DATABASE_API void testLinkage();
		DATABASE_API bool remove(unsigned int index);
	};

	class Table;

	struct tblIterator {
		Table *table;
		int value;
		DATABASE_API Record* operator->();
		DATABASE_API tblIterator& operator++();
		DATABASE_API bool operator!=(tblIterator param);
		DATABASE_API bool operator==(tblIterator param);
	};

	class Table {

	private:
		tblIterator tableIterator;
		std::vector<Record> allRecords;
		std::vector<std::string> attributes;
		std::string key;
	public:
		DATABASE_API Table();
		DATABASE_API Table(std::vector<std::string> name);
		DATABASE_API bool addAttribute(std::string name);
		DATABASE_API bool deleteAttribute(std::string name);
		DATABASE_API bool insert(Record record);
		DATABASE_API std::vector<std::string> getAttributes();
		DATABASE_API unsigned int getSize();
		DATABASE_API tblIterator begin();
		DATABASE_API tblIterator end();
		DATABASE_API std::string getKey();
		DATABASE_API bool defineKey(std::string name);
		DATABASE_API Table crossJoin(Table tblOne, Table tblTwo);
		DATABASE_API Table naturalJoin(Table tblOne, Table tblTwo);
		DATABASE_API std::map<std::string, std::string> routines(std::string name);
		DATABASE_API void testLinkage();
		DATABASE_API std::vector<Record> getAllRecords();
		DATABASE_API Record& getRecord(int index);

		DATABASE_API void printTable();
		DATABASE_API bool deleteRecord(int index);

	};

	// This class is exported from the Database.dll
	class Database {
		std::map<std::string, Table> databaseTables;
		std::vector<Record> records;
		Table table;
		Table outputTable;
		class Query {
			std::vector<std::string> attributes;
			std::vector<std::string> parsedWhere;
			Table originalTable;
		public:
			Query(std::string select, std::string wherever, Table table);
			std::vector<std::string> parseSelect(std::string select, Table table);
			std::vector<std::string> parseWhere(std::string wherever);
			std::vector<std::string> getAttributes();
			std::vector<std::string> getParsedWhere();
			Table getResult();
			std::string Tokenizer(std::string & str);
		};
	public:
		void addRecords();
		std::vector<Record> findRecords();
		Table findTable(std::string from);
		DATABASE_API Database();
		DATABASE_API bool addTable(Table tbl, std::string name);
		DATABASE_API bool dropTable(std::string tblName);
		DATABASE_API std::vector<std::string> listTables();
		DATABASE_API std::map<std::string, Table> getTables();
		DATABASE_API Table query(std::string select, std::string from, std::string wherever);
		DATABASE_API void testLinkage();
	};
}
