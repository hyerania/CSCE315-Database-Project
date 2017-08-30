#pragma once
// Members: My Pham, Sneha Santani, Leslie Escalante
// Team 17 - section 506


#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <vector>
#include <string>

class Record {
public:
	// default constructor
	Record();
	// constructor 
	Record(int sz);
	// copy constructor
	Record(const Record& record);
	// destructor 
	~Record();

	// get record size
	int getRecordSize();
	// accessor operator
	std::string& operator [] (int index);

	void extendRecord ();
	void discard (int index);
	

private:
	std::vector<std::string> recordData;
};

#endif
