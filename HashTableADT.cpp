#include "HashTableADT.h"
#include "Car.h"

template <class H>
void ManufacturerTable<H>::insert(Car* node) {
	int loc = hashFunction(node->getID());
	int j = 0;
	int i = 0;
	bool end = false;



		//starting at the hashed location use a linear probe to find either the correct manufacturer or find an appropriate slot
		while(i < maxSize && end == false) { 

			j = (loc + i) % maxSize;

			//std::cout << "searching maufacturer # " << j << std::endl;

			//check for whether the current slot has been initialized
			if (table[j].getManufacturer() != "") {

				//if so check that the manufacturers line up, if so insert the node, if not move linearly to the next slot
				if (table[j].getManufacturer() == node->getMaker()) {
					//std::cout << "found existing manu slot " <<j<< std::endl;
					table[j].insert(node);
					count++;
					end = true;
				}
			}

			//if the current slot is uninitialized then initialize it
			else {
				//std::cout << "setting new manu slot" << std::endl;

				table[j].setManufacturer(node->getMaker());

				table[j].insert(node);

				count++;
				unique++;
				end = true;
			}
			i++;
		}
	

	//if all else fails the only reason is because there are not enough maufacturer slots. if desired you can resize the hash table at this point
	if (!end) {
		std::cout << "ERROR: failed to find manufacturer" << std::endl;
	}
	return;
}

/*
given a specific key, this function
will attempt to find and remove
the desired car
*/
template <class H>
bool ManufacturerTable<H>::remove(std::string input) {

	int loc = hashFunction(input);
	int j = 0;
	int i = 0;
	int h = 0;
	bool end = false;
	bool skip = false;
	bool result = false;


	while (i < maxSize && end == false) {

		j = (loc + i) % maxSize;

		//check for whether the current slot has been initialized
		if (table[j].getManufacturer() != "") {

			//if so check that the manufacturers line up
			for (std::string::size_type h = 0; h < 3 && skip == false && h<input.length(); h++) {
				if (input[h] != std::toupper(table[j].getManufacturer()[h])) {

					//if the manufacturers do not line up, skip the current one and continue with the linear probing
					skip = true;
				}
			}

			//if the correct manufacturer has been located call the remove for that maker, passing the key down
			if (skip==false) {
				
				//call the remove and make sure it worked, if so then adjust the count and prepare to return
				if (table[j].remove(input)) {
					count--;
					result = true;
				}
				end = true;
			}
		}
		else {
			end = true;
		}
		skip = false;
		i++;
	}
	return result;
}

/*
given a precise key, this function
will find and display a certain car
*/
template <class H>
bool ManufacturerTable<H>::specificSearch(std::string input, void(*display)(Car&)) {

	int loc = hashFunction(input);
	int j = 0;
	int i = 0;
	int h = 0;
	bool end = false;
	bool skip = false;
	bool result = false;


	while (i < maxSize && end == false) {

		j = (loc + i) % maxSize;

		//check for whether the current slot has been initialized
		if (table[j].getManufacturer() != "") {

			//if so check that the manufacturers line up
			for (std::string::size_type h = 0; h < 3 && skip == false && h < input.length(); h++) {
				if (input[h] != std::toupper(table[j].getManufacturer()[h])) {

					//if the manufacturers do not line up, skip the current one and continue with the linear probing
					skip = true;
				}
			}

			//if the correct manufacturer has been located call the specific search for that maker, passing the key down
			if (skip == false) {
				//std::cout << "found existing manu slot " << j << std::endl;
				//call the call search and attempt to display the result
				result = table[j].specificSearch(input, display);
				end = true;
			}
		}
		else {
			end = true;
		}
		skip = false;
		i++;
	}
	return result;
}


/*
this function will take a broad
question in which some data parameters
can be filled and others are empty
and will display all cars that
fall under the given criteria
*/
template<class H>
bool ManufacturerTable<H>::broadSearch(Query* searchObject, void(*display)(Car&)) {

	std::string makerCode = searchObject->getMaker();
	int i = 0;
	int j = 0;
	bool found = false;
	bool cont = true;
	int loc = 0;

	//checks if unput year is valid
	if ((*searchObject == 0) || (*searchObject <= END && *searchObject >= START)) {

		//checks if maker is unspecified, if so print all occupied slots
		if (*searchObject == "Any") {

			while (j < unique) {
				if (table[i].getManufacturer() != "") {
					j++;

					//search the year table for the current manufacturer
					found = table[i].broadSearch(searchObject, display);
				}
				i++;
			}
		}

		//search for specified maker
		else {

			//format maker for hashing then hash it
			for (std::string::size_type i = 0; i < makerCode.length(); ++i) {
				makerCode[i] = toupper(makerCode[i]);
			}
			loc = hashFunction(makerCode);

			//use linear probing to find the desired year table
			while (j < maxSize && cont == true) {
				i = (loc + j) % maxSize;

				//check if correct manufacturer has been found, if so search it then finish the function
				if (*searchObject == table[i].getManufacturer()) {
					found = table[i].broadSearch(searchObject, display);
					cont = false;
				}
				j++;
			}
		}

	}
	else {
		std::cout << "ERROR: invalid year" << std::endl;
	}
	return found;
}

template<class H>
void ManufacturerTable<H>::listByModel(int(*compare)(Car&, Car&), Heap<Car>* displayHeap) {

	int i = 0;
	int j = 0;
	
	while (j < unique) {
		if (table[i].getManufacturer() != "") {
			j++;
			//search the year table for the current manufacturer
			table[i].listByModel(compare, displayHeap);
		}
		i++;
	}
	return;
}

template<class H>
int ManufacturerTable<H>::hashFunction(std::string id) const {
	char* ptr = &id[0];
	int protoKey = 0;
	for (int i = 0; i < 3; i++) {
		protoKey += static_cast<int>(ptr[i]);
	}

	return protoKey%maxSize;
}

template<class H>
void ManufacturerTable<H>::printIndented() {

	int i = 0;
	int j = 0;


	while (j < unique) {
		
		if (table[i].getManufacturer() != "") {
			j++;

			//search the year table for the current manufacturer
			table[i].printIndented();
		}
		
		i++;
	}

}

template<class H>
void ManufacturerTable<H>::displayStats() {
	int i = 0;
	int j = 0;
	std::cout << "Total number of cars in the list: " << count << std::endl;
	std::cout << "Load factor of the manufacturer list: " << (static_cast<double>(count) / maxSize) * 100 << "%" << std::endl;
	std::cout << "Number of collisions in the manufacturer list: " << count - unique << std::endl;


	while (j < unique) {

		if (table[i].getManufacturer() != "") {
			j++;

			//search the year table for the current manufacturer
			table[i].displayStats();
			table[i].findFarthest();
		}

		i++;
	}
	table[0].displayFarthest();


}