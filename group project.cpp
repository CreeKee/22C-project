// group project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include "HashTableADT.h"
#include "HashTableADT.cpp"
#include "yearTable.h"
#include "yearTable.cpp"
#include "BST_ADT.hpp"
#include "BST_ADT.cpp"
#include "Car.h"
#include "SearchObject.h"
#include"Heap.h"
#include"Heap.cpp"
#include"QueueADT.hpp"
#include"QueueADT.cpp"
using namespace std;

const bool TEST = false;
const string INPUTFILENAME = "loader.txt";
const string OUTPUTFILENAME = "carsOut.txt";



void formatInput(string&);
void vDisplay(Car&);

void heapByID(Car&);
bool isPrime(int);
ManufacturerTable<YearTable<bTree<Car>>>* buildList(int&); //generates a new Car object then pushes is into a queue counting how many unique manufacturers there are, then push from queue to structure

void displayMenu();
bool selectMenuOption(ManufacturerTable<YearTable<bTree<Car>>>*, int&, int&);

void dataInsertionManager(ManufacturerTable<YearTable<bTree<Car>>>*, int&); //converts an input into a new car then inserts it
void dataDeletionManager(ManufacturerTable<YearTable<bTree<Car>>>*); //seaches by a key and then deletes the desired object
void specificSearchManager(ManufacturerTable<YearTable<bTree<Car>>>*); //searches by a key then returns the object
void broadSearchManager(ManufacturerTable<YearTable<bTree<Car>>>*);
void broadSearchManager(ManufacturerTable<YearTable<bTree<Car>>>*, int);
void orderedDisplayManager(ManufacturerTable<YearTable<bTree<Car>>>*); //use priority queue to sort the data into a proper list
void printIndentedManager(ManufacturerTable<YearTable<bTree<Car>>>*);
void writeToFile(ManufacturerTable<YearTable<bTree<Car>>>*);
void displayStats(ManufacturerTable<YearTable<bTree<Car>>>*);
void dispalyNamesHIDDEN();
void help();
void displayWelcome();

string generateID(string, string, int, int);
//string generateID(string, string, int, int);



int main()
{
	//this is used for id generation (to ensure that all id's are unique) and does not truly represent the number of cars
	int count = 0;

	//used in certain menu choices
	int action = 0;

	bool printAtEnd = true;

	//this is the over arching data structure that is used for searching/inserting/removing/etc
	ManufacturerTable<YearTable<bTree<Car>>>* DataStructure = buildList(count);

	Car* ptr;
	
	bool proceed = true;
	
	displayWelcome();
	displayMenu();
	proceed = selectMenuOption(DataStructure, count, action);
	while (proceed) {
		if (action != 1) {
			displayMenu();			
		}
		if (action == 2) {
			printAtEnd = false;
		}

		proceed = selectMenuOption(DataStructure, count, action);
		action = 0;
	}
	if(TEST)
		delete ptr;
	if (printAtEnd) {
		writeToFile(DataStructure);
	}
	
	
	return 0;
}


void formatInput(string& input) {
	for (string::size_type i = 0; i < input.length(); ++i)
		input[i] = tolower(input[i]);
	input[0] = toupper(input[0]);
}
void vDisplay(Car& node)
{
	cout << "          ID: " << node.getID() << endl;
	cout << "Manufacturer: " << node.getMaker() << endl;
	cout << "       Model: " << node.getModel() << endl;
	cout << "   Condition: " << node.getCondition() << endl;
	cout << "       Price: $" << node.getCurrentPrice() << endl;
	cout << "        Year: " << node.getYear() << endl;
	cout << "\n-------------------------------------------------\n\n";
}
int compareByModel(Car& a, Car& b) {
	if (a.getModel() < b.getModel())
		return -1;
	
	return 1;
}

int compareByID(Car& a, Car& b) {
	if (a.getID() < b.getID())
		return -1;
	
	return 1;
}
bool isPrime(int a)
{
	int counter = 0; 
	for (int i = 2; i <= a / 2; i++) 
		if (a % i == 0) 
			counter++; 

	if (counter == 0) 
		return true;
	else 
		return false;
}

/*
thsi function simply displays
all of the menu options (minus
the hidden ones)
*/
void displayMenu() {

	cout << "please choose an option from the list below: " << endl;
	cout << "1. Insert data" << endl;
	cout << "2. Delete Data" << endl;
	cout << "3. Search by ID" << endl;
	cout << "4. General search" << endl;
	cout << "5. Write data to a file" << endl;
	cout << "6. Display statistics" << endl;
	cout << "7. Display all cars sorted by model" << endl;
	cout << "8. Help" << endl;
	cout << "9. Exit" << endl;

};

/*
This function will take in an
input from the user then uses 
a switch statement to select the
option based off of the menu
options
*/
bool selectMenuOption(ManufacturerTable<YearTable<bTree<Car>>>* data, int& count, int& action) {
	int choice = 0;
	bool proceed = true;

	
	cout << "Action choice #";
	cin >> choice;
	cout << endl;
	
	//this if statement determines whether or not the in put is valid (it is invalid if it is not an integer)
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10, '\n');
		cout << "unkown choice, try again" << endl;
	}
	else {
		//switch statement takes the input and chooses the action
		switch (choice) {
		case 1:
			dataInsertionManager(data, count);
			break;

		case 2:
			dataDeletionManager(data);
			break;

		case 3:
			specificSearchManager(data);
			break;

		case 4:
			broadSearchManager(data);
			break;

		case 5:
			writeToFile(data);
			action = 2;
			break;

		case 6:
			data->displayStats();
			break;

		case 7:
			orderedDisplayManager(data);
			break;

		case 8:
			help();
			action = 1;
			break;
		
		case 9:
			proceed = false;
			break;

		case 10:
			data->printIndented();
			break;
		
		case 11:
			dispalyNamesHIDDEN();
			break;

		default:
			cout << "unkown choice, try again" << endl;
			break;
		}
	}
	return proceed;
};

/*
This function takes an input
file and will read the pre-formated
information from it into a new car
object then insert that object into
the data structure
*/
ManufacturerTable<YearTable<bTree<Car>>>* buildList(int& count) { //generates a new Car object then pushes is into a queue counting how many unique manufacturers there are, then push from queue to structure
	
	ManufacturerTable<YearTable<bTree<Car>>>* newList = NULL;
	bool cont = true;
	Car* ptr = NULL;
	ifstream inFile(INPUTFILENAME);
	Queue<Car*> countingQueue;

	int maxSize = 0;

	string id;
	string maker;
	string model;
	string condition;
	int year;
	double price;

	//check if the input file is valid
	if (!inFile) {
		cout << "Error opening the input file: \"" << INPUTFILENAME << "\"" << endl;
		cont = false;
	}

	//if it is run through the input file and generate new cars and insert them
	if (cont) {
		while (inFile) {
			inFile >> maker;
			inFile >> model;
			inFile >> condition;
			inFile >> year;
			inFile >> price;
			if (year <= END && year >= START) {
				count++;
				id = generateID(maker, model, year, count);
				ptr = new Car(id, model, maker, condition, year, price);
				countingQueue.enqueue(ptr);
			}
			//no error message here for invalid year because this function builds the list from an input and may be somewhat annoying to possibly get spammed with errors at the start
		}
		
		//get the correct size for the manufacturing table
		for (maxSize = countingQueue.getLength()*2; !isPrime(maxSize); maxSize++);

		newList = new ManufacturerTable<YearTable<bTree<Car>>> (maxSize);
		for (int i = 0; i < countingQueue.getLength();i++) {
			newList->insert(countingQueue.dequeue());
		}
	}
	return newList;

}

/*
This function requires the user
to input information about a car
that they wish to add to the data
structure, once they have inputed
the data a new car object with 
that information and insert it
into the data structure
*/
void dataInsertionManager(ManufacturerTable<YearTable<bTree<Car>>>* list, int& count) {
	
	string maker;
	string model;
	string id;
	string condition;
	int year = 0;
	double basePrice;
	Car* ptr;

	//ask for all the necessary information
	cout << "Who is the manufacturer of the car? ";
	cin >> maker;
	formatInput(maker);
	cout << endl;

	cout << "What model car is it? ";
	cin >> model;
	formatInput(model);
	cout << endl;

	//make sure to validate the year
	while (year<START || year>END) {
		cout << "What year car is it? ";
		cin >> year;
		cout << endl;

		if (year<START || year>END) {
			cout << "Invalid year, try again" << endl;
		}
	}

	cout << "What is the car's base price? $";
	cin >> basePrice;
	cout << endl;

	//it would be easy to force the user into a choice, but because of the currently limited options we wanted to allow the user some freedom
	cout << "What condition is the car in? (it is recomended that you choose from Poor, Good, Great, or New)";
	cin >> condition;
	formatInput(condition);
	cout << endl;

	//increase the car ID seed counter
	count++;

	//genreate a new id for the car that will be inserted
	id = generateID(maker, model, year, count);

	//create a new car and insert it
	ptr = new Car(id, model, maker, condition, year, basePrice);
	list->insert(ptr);
	cout << "Insertion completed" << endl;

	return;
}

/*
this function requires the
user to input the ID of a car
then it will attempt to find 
and delete that car
*/
void dataDeletionManager(ManufacturerTable<YearTable<bTree<Car>>>* list){
	
	string id;

	//get the ID of the car
	cout << "What is the ID of the car you wish to be removed? ";
	cin >> id;
	cout << endl;

	//attempt to remove the car with the matching ID
	if (!list->remove(id)) {
		cout << "That car could not be located" << endl;
	}
	else {
		cout << "Deletion succesful!" << endl;
	}
	
	return;
}

/*
this function takes a
specific ID and will search
for a key with that ID and 
display the information of 
that car
(change to get pointer?)
*/
void specificSearchManager(ManufacturerTable<YearTable<bTree<Car>>>* list) {
	
	string id;

	//get the ID of the car
	cout << "What is the ID of the car you wish to be seached for? ";
	cin >> id;
	cout << endl;

	//search for the car with the matching ID
	if (!list->specificSearch(id, vDisplay)) {
		cout << "That car could not be located" << endl;
	}

	return;
}

/*
this function will take
broad search queries and
display all cars that fit
the search criteria.
note that the secondary key
is technically just the model
but we wanted to have an
extremeley dynamic search
function that can search by
any parameter(s)
*/
void broadSearchManager(ManufacturerTable<YearTable<bTree<Car>>>* list) {

	//initialize all the search paramaters to a default of 'Any'
	string model = "Any";
	string maker = "Any";
	string condition = "Any";
	string inTemp;
	int year = 0;
	double maxPrice = -1;
	double minPrice = 0;
	bool continueInput = true;
	Query* searchObject;

	//output a message then begin asking for input paramaters
	cout << "Please begin inputing search paramaters, to begin the search at any time simply enter 'Search' (skipped parameters default to any)" << endl << endl;

	cout << "What brand car do you want? (for any brand enter 'Any') ";
	cin >> inTemp;
	cout << endl;

	//after inputing each parameter format the input (caps do not matter) and check to make sure that the user does not want to begin searching
	formatInput(inTemp);
	if (inTemp != "Search") {
		maker = inTemp;
	}
	else {
		continueInput = false;
	}
	cout << endl;

	if (continueInput) {
		cout << "What model car do you want? (for any model enter 'Any') ";
		cin >> inTemp;
		cout << endl;
		formatInput(inTemp);
		if (inTemp != "Search") {
			model = inTemp;
		}
		else {
			continueInput = false;
		}
		cout << endl;
	}

	if (continueInput) {
		cout << "What condition car do you want? primary options are: Poor, Good, Great, and New (for any condition enter 'Any', user added cars may containg other conditions) ";
		cin >> inTemp;
		cout << endl;
		formatInput(inTemp);
		if (inTemp != "Search") {
			condition = inTemp;
		}
		else {
			continueInput = false;
		}
		cout << endl;
	}

	if (continueInput) {
		cout << "What year car do you want? (for any year enter 'Any') ";
		cin >> inTemp;
		formatInput(inTemp);

		//check to make sure that the input does not cause errors
		if (static_cast<int>(inTemp[0]) >= 47 && static_cast<int>(inTemp[0]) <= 57) {
			year = stoi(inTemp);

		}
		else {
			if (inTemp == "Search") {
				continueInput = false;
			}
		}
		cout << endl;
	}


	if (continueInput) {
		cout << "What should the maximum price be? (for any price enter 'Any') $";
		cin >> inTemp;
		formatInput(inTemp);
		if (static_cast<int>(inTemp[0]) >= 47 && static_cast<int>(inTemp[0]) <= 57) {
			maxPrice = stod(inTemp);
		}
		else {
			continueInput = false;
		}
		cout << endl;
	}

	if (continueInput) {
		cout << "What should the minimum price be? $";
		cin >> inTemp;
		formatInput(inTemp);
		if (static_cast<int>(inTemp[0]) >= 47 && static_cast<int>(inTemp[0]) <= 57) {
			minPrice = stod(inTemp);
		}
		else {
			if (inTemp == "Search") {
				continueInput = false;
			}
		}
		cout << endl;
	}

	//cout << model << " " << maker << " " << condition << " " << year << " " << maxPrice << " " << minPrice << endl;


	if (maxPrice != -1 && maxPrice < minPrice) {
		cout << "ERROR: invalid price range" << endl;
	}
	else {
		searchObject = new Query(model, maker, condition, year, maxPrice, minPrice);
		if (list->broadSearch(searchObject, vDisplay)) {

		}
		else {
			cout << "no cars matching that description can be found" << endl;
		}
		delete searchObject;
	}

}
void broadSearchManager(ManufacturerTable<YearTable<bTree<Car>>>* list, int overloadSignal) {

	string model = "Any";
	string maker = "Any";
	string condition = "Any";
	string inTemp;
	int year = 0;
	double maxPrice = -1;
	double minPrice = 0;
	bool continueInput = true;
	Query* searchObject;


	searchObject = new Query(model, maker, condition, year, maxPrice, minPrice);
	if (list->broadSearch(searchObject, vDisplay)) {

	}
	else {
		cout << "no cars matching that description can be found" << endl;
	}
	delete searchObject;

}

void orderedDisplayManager(ManufacturerTable<YearTable<bTree<Car>>>* list) { //use priority queue to sort the data into a proper list?

	//create a heap to be used in sorting the information
	Heap<Car>* displayHeap = new Heap<Car>(list->getCount());
	Car retObject;
	Query* anyAndEvery = new Query;
	
	//add all the data to the heap
	list->listByModel(compareByModel, displayHeap);
	
	//print from the heap
	while (!displayHeap->isEmpty()) {
		displayHeap->deleteHeap(retObject, compareByModel);
		vDisplay(retObject);
	}

	delete displayHeap;

}

void writeToFile(ManufacturerTable<YearTable<bTree<Car>>>* list) {
	
	Car retObject;
	ofstream outFile;
	Heap<Car>* outPutHeap = new Heap<Car>(list->getCount());

	outFile.open(OUTPUTFILENAME);

	//the output sorting is based on ID so that all cars with the same maker will be grouped togethere
	list->listByModel(compareByID, outPutHeap);


	//The output format follows the input format except that it outputs the current price instead of the base price and adds a '$' (you could not use this output file as an input file)
	while (!outPutHeap->isEmpty()) {
		outPutHeap->deleteHeap(retObject, compareByID);
		outFile << retObject.getModel() << " " << retObject.getMaker() << " " << retObject.getCondition() << " " << retObject.getYear() << " $" << retObject.getCurrentPrice() << endl;
	}


	outFile.close();

}

void displayStats(ManufacturerTable<YearTable<bTree<Car>>>* list) {

	//total number of cars
	cout << "The total Number of cars in the list is: " << list->getCount() << endl;
	//density of maufacturers
	cout << "the density of manufacturers is: " << list->getDensity() * 100 <<"%"<< endl;
	//density of decades?

	return;
}

void dispalyNamesHIDDEN() {

	cout << "Project members:" << endl;
	cout << "Seth Kiefer & Cong Shen" << endl;

	return;
}

string generateID(string maker, string model, int year, int count) {
	
	string id;

	//take the frst 3 characters from the manufacturer and add that to the ID
	for (string::size_type i = 0; i < 3; ++i) {
		id += toupper(maker[i]);
	}

	//next add the year
	id.append(to_string(year));

	//then add the model of the car
	for (string::size_type i = 0; i < model.length(); ++i)
		id.append(1, toupper(model[i]));

	//finally add the number of current cars, this way there will be no duplicates <----need to change because removing a car then adding one may cause duplicates, which may cause issues
	id.append(to_string(count));

	//given toyota, corolla, 2000
	//the final id will be along the lines of: TOY2000COROLLA4
	return id;
}

void help() {

	cout << "1. Insert data - will ask for a set of information which will be compiled into car object that will be inserted into the database" << endl;
	cout << "2. Delete Data - will ask for the key of a specific car, feel free to use the general search to locate one, and then try to delete the chosen car" << endl;
	cout << "3. Search by ID - as before this option will aske for a specific key and then display the stats of the chosen car" << endl;
	cout << "4. General search - will ask for a set of data paramters to search by, feel free to include as many or phew as you want" << endl;
	cout << "5. Write data to a file - will write the current database to an output file" << endl;
	cout << "6. Display statistics - will show some of the statistics about the data structures being used" << endl;
	cout << "7. Display all cars sorted by model - will sort the cars in the database then display them alpabetically by their model" << endl;
	cout << "8. Help - displays useful information" << endl;
	cout << "9. Exit - exits the programm" << endl;
}

void displayWelcome() {

	cout << "Welcome to the car database!\nthis is a set of cars sorted into a data structure\nthe cars have data parameters such as manufacturer, model, year, condition and more, have fun!" << endl;

}

/*
X Add new data 
X Delete data
X Find and display one element using the primary key
X (plus some) Find and display elements using the secondary key (all matches)
X List data sorted by the secondary key
X Hidden print option (details are given in Team Project-Part2)
X Write data to a file. 
- Statistics (details are given in Team Project-Part2) (fix)
X Hidden option (do not show it in the menu): when selected, display the names of the
team members
X Help – to show the menu. Show the menu once, before the loop, then show the menu
upon request: “Enter an option (H – for help): ”
X Exit
*/