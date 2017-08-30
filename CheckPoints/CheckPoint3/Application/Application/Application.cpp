// Application.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "json.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct business {
	std::string businessId;
	std::string name;
	std::string neighborhood;
	std::string address;
	std::string city;
	std::string state;
	std::string postalCode;
	double latitude;
	double longitude;
	double stars;
	double reviewCount;
	int isOpen;
	//std::vector<std::string> attributes;
	std::vector<std::string> categories;
	std::vector<std::string> hours;
	std::string type;
};

struct review {
	std::string reviewId;
	std::string userId;
	std::string businessId;
	double stars;
	std::string date;
	std::string text;
	double useful;
	double funny;
	double cool;
	std::string type;
};

struct user {
	std::string userId;
	std::string name;
	double reviewCount;
	std::string yelpingSince;
	std::vector<std::string> friends;
	double useful;
	double funny;
	double cool;
	double fans;
	std::vector<std::string> elite;
	double avgStars;
	double complimentHot;
	double complimentMore;
	double complimentProfile;
	double complimentCute;
	double complimentList;
	double complimentNote;
	double complimentPlain;
	double complimentCool;
	double complimentFunny;
	double complimentWriter;
	double complimentPhotos;
	std::string type;
};

using json = nlohmann::json;

int main() {
	std::string line;
	struct business allBusiness[150];
	struct user allUser[150];
	struct review allReview[150];

	std::ifstream myfileBusiness("business.json");
	std::ifstream myfileUser("user.json");
	std::ifstream myfileReview("review.json");
	int countBusiness = 0;
	int countUser = 0;
	int countReview = 0;

	if (myfileBusiness.is_open()){
		while (getline(myfileBusiness, line)){
			auto business = json::parse(line);
			allBusiness[countBusiness].businessId = business["business_id"];
			allBusiness[countBusiness].name = business["name"];
			allBusiness[countBusiness].neighborhood = business["neighborhood"];
			allBusiness[countBusiness].address = business["address"];
			allBusiness[countBusiness].city = business["city"];
			allBusiness[countBusiness].state = business["state"];
			allBusiness[countBusiness].postalCode = business["postal_code"];
			allBusiness[countBusiness].latitude = business["latitude"];
			allBusiness[countBusiness].longitude = business["longitude"];
			allBusiness[countBusiness].stars = business["stars"];
			allBusiness[countBusiness].reviewCount = business["review_count"];
			allBusiness[countBusiness].isOpen = business["is_open"];
			//allBusiness[countBusiness].attributes.push_back("");
			//allBusiness[countBusiness].attributes = business["attributes"];
			allBusiness[countBusiness].categories = business["categories"];
			allBusiness[countBusiness].type = business["type"];
			/*if (business["hours"] == NULL) {
				allBusiness[countBusiness].hours.push_back("");
			}
			else {
				allBusiness[countBusiness].hours = business["hours"];
			}*/
			countBusiness++;
			//std::cout << business.dump(4) << std::endl;
			//break;
			//std::cout << business["attributes"] << std::endl;
		}
		/*std::cout << countBusiness << std::endl;
		for (int i = 0; i < countBusiness; i++) {
			std::cout << allBusiness[i].businessId<< std::endl;
		}*/
		myfileBusiness.close();
	}

	
	if (myfileUser.is_open()) {
		while (getline(myfileUser, line)) {
			auto user = json::parse(line);
			allUser[countUser].userId = user["user_id"];
			allUser[countUser].name = user["name"];
			allUser[countUser].reviewCount = user["review_count"];
			allUser[countUser].yelpingSince = user["yelping_since"];
			allUser[countUser].friends = user["friends"];
			allUser[countUser].useful = user["useful"];
			allUser[countUser].funny = user["funny"];
			allUser[countUser].cool = user["cool"];
			allUser[countUser].fans = user["fans"];
			allUser[countUser].elite = user["elite"];
			allUser[countUser].avgStars = user["average_stars"];
			allUser[countUser].complimentHot = user["compliment_hot"];
			allUser[countUser].complimentMore = user["compliment_more"];
			allUser[countUser].complimentProfile = user["compliment_profile"];
			allUser[countUser].complimentCute = user["compliment_cute"];
			allUser[countUser].complimentList = user["compliment_list"];
			allUser[countUser].complimentNote = user["compliment_note"];
			allUser[countUser].complimentPlain = user["compliment_plain"];
			allUser[countUser].complimentCool = user["compliment_cool"];
			allUser[countUser].complimentFunny = user["compliment_funny"];
			allUser[countUser].complimentWriter = user["compliment_writer"];
			allUser[countUser].complimentPhotos = user["compliment_photos"];
			allUser[countUser].type = user["type"];
			countUser++;
		}
		myfileUser.close();
	}

	if (myfileReview.is_open()) {
		while (getline(myfileReview, line)) {
			auto review = json::parse(line);
			allReview[countReview].reviewId = review["review_id"];
			allReview[countReview].userId = review["user_id"];
			allReview[countReview].businessId = review["business_id"];
			allReview[countReview].stars = review["stars"];
			allReview[countReview].date = review["date"];
			allReview[countReview].text = review["text"];
			allReview[countReview].useful = review["useful"];
			allReview[countReview].funny = review["funny"];
			allReview[countReview].cool = review["cool"];
			allReview[countReview].type = review["type"];
			countReview++;
		}
		myfileReview.close();
	}

	std::cout << "Hello, World!" << std::endl;
	return 0;
}


