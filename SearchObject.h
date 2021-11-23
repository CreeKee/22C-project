#pragma once
#include<string>

#ifndef SEARCH_OBJECT_H
#define SEARCH_OBJECT_H
#include"Car.h"

class Query
{
private:
	// Declare a structure for the list
	std::string model;
	std::string maker;
	std::string condition;
	int year;
	double maxPrice;
	double minPrice;



public:
	Query() { model = "Any"; maker = "Any"; condition = "Any"; year = 0; maxPrice = -1; minPrice = 0; }
	Query(std::string mod, std::string make, std::string cond, int y, double maxp, double minp ) { model = mod; maker = make; condition = cond; year = y; minPrice = minp; maxPrice = maxp; };  // Constructor
	~Query() {};   // Destructor

	std::string getMaker() const { return maker; }
	int getyear() const { return year; }

	bool operator==(const Car&);

	bool operator==(const int);
	bool operator<=(const int);
	bool operator>=(const int);

	bool operator==(const std::string&);
	bool operator<=(const std::string&);
	bool operator>=(const std::string&);
};
#endif