// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "json.hpp"
#include <iostream>
#include <vector>
#include <fstream>

struct business {
	std::string address;
	std::string attributes;
	std::string businessId;
	std::string categories;
	std::string city;
	std::string hours;
	bool isOpen;
	double latitude;
	double longittude;
	std::string name;
	std::string neighborhood;
	std::string postalCode;
	double stars;
	std::string state;
	std::string busType;
};



using json = nlohmann::json;

int main() {

	//json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
	std::string line;
	std::ifstream myfileBusiness("business.json");

	if (myfileBusiness.is_open())
	{
		while (getline(myfileBusiness, line))
		{
			auto business = json::parse(line);
			std::cout << business.dump(4) << std::endl;
			if()
			//std::cout << j3["city"] << std::endl;
			if()
			//break;
			//std::cout << j3["address"] << std::endl;
		}
		myfileBusiness.close();
	}

	std::cout << "Hello, World!" << std::endl;
	return 0;
}

