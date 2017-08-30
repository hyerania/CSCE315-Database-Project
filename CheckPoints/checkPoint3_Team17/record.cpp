
#include "record.h"
using namespace std;
// default constructor
Record::Record() {}

// constructor, initialize recordData with the given size and empty string
Record::Record(int sz) : recordData(sz, "NULL") {}
// copy constructor
Record::Record(const Record& copy) {
	recordData = copy.recordData;
}
// destructor 
Record::~Record() {
	recordData.clear();
}


// get record size
int Record::getRecordSize() {
	return recordData.size();
}
// accessor operator
std::string& Record::operator [] (int index) {
	return recordData.at(index);
}

void Record::extendRecord () {
	recordData.push_back("NULL");
}

void Record::discard (int index) {
	recordData.erase(recordData.begin()+index);
}