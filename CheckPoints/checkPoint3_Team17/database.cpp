#include "stdafx.h"
#include "database.h"
#include <sstream>
#include <istream>
#include <stdexcept>
#include <algorithm>

struct Token {
	std::string kind; //@ for string input
	std::string input;
	bool value;

	Token(bool c) : value(c) {}
	//Token(string ch) : kind(ch), value(false) {}
	//Token(string ch, string in) : kind(ch), input(in) {} 
	Token(std::string ch, bool val) : kind(ch), value(val) {}
	Token(std::string ch, std::string in, bool val) : kind(ch), input(in), value(val) {}
};


struct result {
	std::string input;
	bool value;

	result(std::string ch, bool val) : input(ch), value(val) {}
};

class Token_stream {
	bool full, val = false;
	Token buffer;

public:
	Token_stream() : full(false), buffer(false) {}

	void putback(Token t) {
		if (full) {
			throw std::runtime_error("putback into a full buffer");
		}
		buffer = t;
		full = true;
	}

	Token get() {
		std::string ch;
		std::cin >> ch;

		if (full) { full = false; return buffer; }

		if (ch == "(" || ch == ")" || ch == "=" || ch == "<>" || ch == "<" ||
			ch == ">" || ch == "<=" || ch == ">=" || ch == ";") {
			return Token(ch, false);
		}
		else if (ch == "AND" || ch == "OR" || ch == "NOT") {
			return Token(ch, false);
		}
		else { //is string input
			return Token("@", ch, false);
		}
	}
};

Token_stream ts;

result expression();  // declaration to deal with indirect recursion

result primary() {	// primary will deal with strings, NOT, (), and call expression
	Token t = ts.get();

	if (t.kind == "(") {
		result r = expression();
		t = ts.get();
		if (!(t.kind == ")")) {
			throw std::runtime_error(" ) expected.");
		}
		return r;
	}
	else if (t.kind == "NOT") {
		result r = expression();
		std::cout << "NOT: " << r.input << " " << r.value << std::endl;
		if (r.value == true) { //negate result
			return result(";", false);
		}
		else {
			return result(";", true);
		}
	}
	else if (t.kind == "@") {
		return result(t.input, false);
	}
	else {
		ts.putback(t);
		throw std::runtime_error("Error: A primary expected.\n");
	}
}
/******************************************************************
The primary() function must execute first, then it can do the string
comparison with the other input. Because of this, the <, >, <=, and
>= appear to be "reversed."

They do, however, work properly.

******************************************************************/
result expression() {
	result r = primary();

	if (r.input == ";") {
		return r;
	}

	Token t = ts.get();
	if (t.kind == "=") {
		return result("", (primary().input == r.input));
	}
	else if (t.kind == "<>") {
		return result("", (!(primary().input == r.input)));
	}
	else if (t.kind == ">") {
		return result("", (primary().input < r.input));
	}
	else if (t.kind == "<") {
		return result("", (primary().input > r.input));
	}
	else if (t.kind == ">=") {
		return result("", (primary().input <= r.input));
	}
	else if (t.kind == "<=") {
		return result("", (primary().input >= r.input));
	}
	else if (t.kind == "AND") {
		return result("", (primary().value && r.value));
	}
	else if (t.kind == "OR") {
		return result("", (primary().value || r.value));
	}
	else {
		ts.putback(t);
		throw std::runtime_error("Error: An expression expected.\n");
	}

}

bool beginParsing() {
	try {
		result r("", false);

		while (true) {
			Token t = ts.get();
			if (t.kind == ";") {
				//std::cout<<"after ;"<<std::endl;
				if (r.value == true) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				ts.putback(t);
			}
			r = expression();
		}
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		std::cin.clear();
		return false;
	}
	catch (...) {
		std::cerr << "Error: Undefined exception. \n";
		std::cin.clear();
		return false;
	}
}

Database::Database() {}
// Destructor
Database::~Database() {}

// add a table to the database 
void Database::addTable(const std::string& name, Table& table) {
	database.insert(std::pair<std::string, Table>(name, table));
}
// delete a table from the database
void Database::dropTable(const std::string& name) {
	databaseItr = database.find(name);
	database.erase(databaseItr);
}
// return list of table NAMES

std::vector<std::string> Database::listTables() {
	std::vector<std::string> tableNames;
	for (databaseItr = database.begin(); databaseItr != database.end(); ++databaseItr) {
		tableNames.push_back(databaseItr->first);
	}
	return tableNames;
}

// return vector of Table object 
std::vector<Table> Database::getTables() {
	std::vector<Table> allTables;
	for (databaseItr = database.begin(); databaseItr != database.end(); ++databaseItr) {
		allTables.push_back(databaseItr->second);
	}
	return allTables;
}

// Querry
Table Database::Querry(std::string Select, std::string From, std::string Where) {

	Table resultTable;
	// FROM
	Table searchTable;
	databaseItr = database.find(From);
	if (databaseItr != database.end()) {
		searchTable = databaseItr->second;
	}
	std::vector <std::string> searchTableAttrs = searchTable.getAttributeNames();
	for (int i = 0; i < searchTableAttrs.size(); ++i) {
		resultTable.addAttribute(searchTableAttrs.at(i));
	}



	// WHERE
	std::stringstream ss2(Where);
	std::string stemp;
	std::vector<std::string> vtemp;
	while (ss2 >> stemp) {
		if (stemp != "<" && stemp != ">" && stemp != "=" && stemp != "<=" && stemp != ">=" && stemp != "<>"
			&& stemp != "AND" && stemp != "OR" && stemp != "NOT" && stemp != "(" && stemp != ")") {
			vtemp.push_back(stemp);
		}
	}

	std::map <size_t, int> position;
	for (int i = 0; i < vtemp.size(); ++i) {
		auto it = find(searchTableAttrs.begin(), searchTableAttrs.end(), vtemp.at(i));
		if (it != searchTableAttrs.end()) {
			position.insert(std::pair<size_t, int>(Where.find(vtemp.at(i)), vtemp.at(i).size()));
		}
	}

	// find attribute index
	std::vector <int> attrIndex;
	std::vector <std::string> mainAttrs;
	std::vector <std::string> replaceString;
	for (int i = 0; i < vtemp.size(); ++i) {
		for (int j = 0; j < searchTableAttrs.size(); ++j) {
			if (vtemp.at(i) == searchTableAttrs.at(j)) {
				attrIndex.push_back(j);
				mainAttrs.push_back(vtemp.at(i));
			}
		}
	}

	// replace string with actual value 
	std::string s;
	std::string preReplace;
	int insertIndex = 0;
	for (int i = 0; i < searchTable.getTableSize(); ++i) {
		int k = 0;
		int l = 0;
		s = Where;
		for (auto it = position.begin(); it != position.end(); ++it) {
			std::string replaceString = (searchTable.tableRecord.at(i))[attrIndex.at(k)];
			++k;
			if (it == position.begin()) {
				if (s.at(0) != '(')
					replaceString = replaceString + " b";
				s.replace(it->first, it->second, replaceString);
				preReplace = replaceString;
			}
			else {
				if (preReplace.size() < mainAttrs.at(l).size()) {
					insertIndex = (it->first) - (mainAttrs.at(l).size() - preReplace.size());
				}
				else if (preReplace.size() > mainAttrs.at(l).size()) {
					insertIndex = (it->first) + (preReplace.size() - mainAttrs.at(l).size()) - 1;
				}
				++l;
				s.replace(insertIndex, it->second, replaceString);
				preReplace = replaceString;
			}
		}
		if (s.at(0) == '(')
			s.insert(2, "b ");
		s.append(" ;");
		std::streambuf *backup;
		std::istringstream oss(s);
		backup = std::cin.rdbuf();
		std::cin.rdbuf(oss.rdbuf());
		bool re = beginParsing();
		if (re) {
			resultTable.insertRecord(searchTable.tableRecord.at(i));
		}
	}

	// SELECT
	std::string token;
	std::vector <std::string> tokens;
	std::stringstream ss(Select);

	if (Select != "*") {

		while (ss >> token) {
			if (token.at(token.size() - 1) == ',') {
				token.erase(token.end() - 1);
			}
			tokens.push_back(token);
		}


		std::vector <std::string> resultTableAttrs = resultTable.getAttributeNames();
		for (int i = 0; i < searchTableAttrs.size(); ++i) {
			auto it = find(tokens.begin(), tokens.end(), searchTableAttrs.at(i));
			if (it != tokens.end()) {
				continue;
			}
			else {
				resultTable.deleteAttribute(searchTableAttrs.at(i));
			}
		}
	}

	return resultTable;
}