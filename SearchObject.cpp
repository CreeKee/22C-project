#include "SearchObject.h"
#include <string>
#include <iostream>

bool Query::operator==(const Car& car) {
	bool retval = false;

	if (model == car.getModel() || model == "Any") {
		if (condition == car.getCondition() || condition == "Any") {
			if (maxPrice == -1 || (maxPrice >= car.getCurrentPrice() && minPrice <= car.getCurrentPrice())) {
				retval = true;
			}
		}
	}



	return retval;
}

bool Query::operator==(const int y) {
	bool retval = false;

	if (year == y) {
		retval = true;
	}

	return retval;
}

bool Query::operator<=(const int y) {
	bool retval = false;

	if (year <= y) {
		retval = true;
	}

	return retval;
}

bool Query::operator>=(const int y) {
	bool retval = false;

	if (year >= y) {
		retval = true;
	}

	return retval;
}

bool Query::operator==(const std::string& make) {
	bool retval = false;

	if (make == maker) {
		retval = true;
	}
	return retval;
}

bool Query::operator<=(const std::string& make) {
	bool retval = false;

	if (make <= maker) {
		retval = true;
	}
	return retval;
}

bool Query::operator>=(const std::string& make) {
	bool retval = false;

	if (make >= maker) {
		retval = true;
	}
	return retval;
}