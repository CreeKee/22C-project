#pragma once
#include<string>
#include<iostream>
#ifndef CAR_H
#define CAR_H

const int END = 2020;
const int START = 1990;
const int CURRENT_YEAR = 2020;
const double DEPRECATION = .9;

class Car
{
private:
	// Declare a structure for the list
	std::string ID;
	std::string model;
	std::string maker;
	std::string condition;
	int year;
	double basePrice;
	bool warranty;



public:
	Car() { ID = ""; model = ""; maker = ""; condition = ""; year = -1; basePrice = -1; warranty = false; };  // Constructor
	Car(std::string code, std::string mod, std::string make, std::string cond, int y, double bp) { ID = code; model = mod; maker = make; condition = cond; year = y; basePrice = bp; warranty = setWarranty(); };  // Constructor
	~Car() {};   // Destructor

	void setID(std::string code) { ID = code; }
	void setModel(std::string mod) { model = mod; }
	void setMaker(std::string make) { maker = make; }
	void setCondition(std::string cond) { condition = cond; }
	void setYear(int y) { year = y; }
	void setBasePrice(double bp) { basePrice = bp; }
	bool setWarranty() { if (year > CURRENT_YEAR-5) { return true; } else { return false; }}

	std::string getID() const { return ID; }
	std::string getModel() const { return model; }
	std::string getMaker() const { return maker; }
	std::string getCondition() const { return condition; }
	int getYear() const { return year; }
	double getBasePrice() const { return basePrice; }
	bool getWarranty() const { return warranty; }
	double getCurrentPrice() const;

	bool operator==(const std::string&);
	bool operator==(const Car&);


	bool operator>(const std::string&);
	bool operator>(const Car&);

	bool operator<(const std::string&);
	bool operator<(const Car&);

	bool operator!=(const Car&);

	friend std::ostream& operator<<(std::ostream& os, const Car& dt);
};
#endif