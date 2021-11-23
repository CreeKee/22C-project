#pragma once

#include<string>
#include<iostream>
#include "Car.h"
#include "Heap.h"
#include "SearchObject.h"
#ifndef HASH_TABLE_ADT_H
#define HASH_TABLE_ADT_H



template <class H>
class ManufacturerTable
{
private:
	// Declare a structure for the list

	int maxSize;
	H* table;
	int count;
	int unique;

public:
	ManufacturerTable() { maxSize = 0; table = nullptr; count = 0; unique = 0;};  // Constructor
	ManufacturerTable(int i) { maxSize = i; table = new H[i]; count = 0; unique = 0; };  // Constructor
	~ManufacturerTable() {delete [] table; };   // Destructor

	void insert(Car*);
	bool remove(std::string);
	bool specificSearch(std::string, void(*display)(Car&));
	bool broadSearch(Query* searchObject, void(*display)(Car&));
	void listByModel(int(*compare)(Car&,Car&), Heap<Car>* displayHeap);
	int hashFunction(std::string) const;
	void printIndented();
	void displayStats();

	double getDensity() const { return static_cast<double>(unique) / maxSize; }
	double getYdensity(int i) const { return table[i]->getYdensity(); }
	int getCount() const { return count; }
	int getMaxSize() const { return maxSize; }


};
#endif