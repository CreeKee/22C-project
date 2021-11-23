#pragma once
#include<string>
#include<iostream>
#include "Car.h"
#include "Heap.h"
#include "SearchObject.h"
#ifndef YEAR_TABLE_H
#define YEAR_TABLE_H



template <class Y>
class YearTable
{
private:

	int maxSize;
	Y* table;
	int count;
	int unique;
	std::string manufacturer;

public:
	YearTable() { maxSize = ((END - START) / 10)+1; table = new Y[maxSize]; count = 0; manufacturer = ""; unique = 0;  };  // Constructor
	~YearTable() { delete [] table; };   // Destructor

	void insert(Car*);
	bool remove(std::string);
	bool specificSearch(std::string, void(*display)(Car&));
	bool broadSearch(Query*, void(*display)(Car&));
	void listByModel(int(*compare)(Car&, Car&), Heap<Car>*);
	int hashFunction(int) const;
	void printIndented();
	void displayStats();
	void findFarthest();
	void displayFarthest() { table[0].displayFarthest(); }


	double getYDensity() const { return static_cast<double>(unique) / maxSize; }
	int getCount() const { return count; }
	int getMaxSize() const { return maxSize; }
	std::string getManufacturer() const { return manufacturer; }

	void setManufacturer(std::string maker) { manufacturer = maker; }

};
#endif