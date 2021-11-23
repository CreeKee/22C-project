#include "yearTable.h"
#include "Car.h"
#include<iostream>



template <class Y>
void YearTable<Y>::insert(Car* node) {
		
	int loc = hashFunction(node->getYear());

	
	//std::cout << "searching decade #" << loc << std::endl;
	if (table[loc].getCount()!=0) {
		//std::cout << "found appropriate year slot " << loc<< std::endl;
		table[loc].insert(node);
		count++;
	}
	else {
		//std::cout << "setting new year slot" << std::endl;
		table[loc].setYear(loc);
		table[loc].insert(node);
		count++;
		unique++;
	}
	return;
}

template<class Y>
bool YearTable<Y>::remove(std::string input) {
	std::string protoYear;
	bool sucess;
	int index;
	//manipulate the key in order to extract the desired year then hash the year to get the decade
	for (std::string::size_type i = 3; i < 7 && i < input.length(); i++) {
		protoYear += input[i];
	}
	index = hashFunction(stoi(protoYear));

	//search the desired decade for the desired car if found delete it, then return success or failure
	sucess = table[index].remove(input);
	return sucess;
}

/*
given a precise key, this function
will find and display a certain car
*/
template<class Y>
bool YearTable<Y>::specificSearch(std::string input, void(*display)(Car&)) {
	std::string protoYear;
	bool sucess;
	int index;

	//manipulate the key in order to extract the desired year then hash the year to get the decade
	for (std::string::size_type i = 3; i < 7 && i < input.length(); i++) {
		protoYear += input[i];
	}

	index = hashFunction(stoi(protoYear));
	//std::cout << "found existing year slot " << index << std::endl;
	//search the desired decade for the desired car and return the result
	sucess = table[index].specificSearch(input, display);
	return sucess;
}

template<class Y>
int YearTable<Y>::hashFunction(int year) const {		
	int protoKey = year / 10;
	int difference = (END-START) - (START/10);
	return (protoKey+difference)%(END-START);
}

template<class Y>
bool YearTable<Y>::broadSearch(Query* searchObject, void(*display)(Car&)) {
	
	bool found = false;
	int i = 0;
	int j = 0;

	
	//year==0 means to print all years avaliable
	if (*searchObject == 0) {

		//go through as many years as have objects in them and search by the remainding criteria 
		while(j<=unique) {
			if (table[i].getYear() != -1) {
				table[i].broadSearch(searchObject, display, found);
				j++;
			}
			i++;
		}	
	}
	else {

		i = hashFunction(searchObject->getyear());
		table[i].broadSearch(searchObject, display, found);
	}
	return found;
}

template<class Y>
void YearTable<Y>::listByModel(int(*compare)(Car&, Car&), Heap<Car>* displayHeap) {
	
	bool found = false;
	int i = 0;
	int j = 0;

	

		//go through as many years as have objects in them and search by the remainding criteria 
		while(j<=unique) {
			if (table[i].getYear() != -1) {
				table[i].listByModel(compare, displayHeap);
				j++;
			}
			i++;
		}	

	return;
}

template<class Y>
void YearTable<Y>::printIndented() {

	//using this to drop the last digit and so just have the current decade
	int decade = START / 10;
	decade *= 10;
	int i = 0;
	int j = 0;
	while (j < unique) {
		std::cout << manufacturer << "s from the " << decade + ((i) * 10) << "'s: ";
		if (table[i].getYear() != -1) {
			std::cout << std::endl;
			table[i].print2D();
			j++;
			std::cout << "\n---------------------------------------------\n";
		}
		else {
			std::cout << " none";
		}
		std::cout << std::endl;
		i++;
		
	}
	std::cout << std::endl;
}

template<class Y>
void YearTable<Y>::displayStats() {
	std::cout << "Load factor for " << manufacturer << " is " << (static_cast<double>(count) / maxSize) * 100 <<"%" <<std::endl;
	std::cout << "The number of collisions is " << count - unique << std::endl;

}

template<class Y>
void YearTable<Y>::findFarthest() {
	int i = 0;
	int j = 0;
	while (j < unique) {
		if (table[i].getYear() != -1) {
			j++;
			table[i].findLongestPath();
		}
		i++;
	}

}