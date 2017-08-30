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

    json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

    std::string line;
    std::ifstream myfile("business.json");

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            auto j3 = json::parse(line);
            std::cout << j3.dump(4) << std::endl;
            break;
//            std::cout << j3["address"] << std::endl;
        }
        myfile.close();
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

