#include"Car.h"
double Car::getCurrentPrice() const {
	int years = CURRENT_YEAR-year;
	double multiplier = 1;
	double price = basePrice;
	if (condition == "Poor") {
		multiplier = .3;
	}
	else if (condition == "Good") {
		multiplier = .6;
	}
	else if (condition == "Great") {
		multiplier = .8;
	}

	for (int i = 0; i < years; i++) {
		price *= DEPRECATION;
	}
	price *= multiplier;
	return price;

}

bool Car::operator==(const std::string& code) {
	bool retval = false;

	if (code == ID) {
		retval = true;
	}
	return retval;
}

bool Car::operator==(const Car& code) {
	bool retval = false;

	if (code.getID() == ID) {
		retval = true;
	}
	return retval;
}

bool Car::operator>(const std::string& code) {
	bool retval = false;

	if (code > ID) {
		retval = true;
	}
	return retval;
}

bool Car::operator>(const Car& code) {
	bool retval = false;

	if (code.getID() > ID) {
		retval = true;
	}
	return retval;
}

bool Car::operator<(const std::string& code) {
	bool retval = false;

	if (code < ID) {
		retval = true;
	}
	return retval;
}

bool Car::operator<(const Car& code) {
	bool retval = false;

	if (code.getID() < ID) {
		retval = true;
	}
	return retval;
}

bool Car::operator!=(const Car& code) {
	bool retval = false;

	if (code.getID() != ID) {
		retval = true;
	}
	return retval;
}

std::ostream& operator<<(std::ostream& os, const Car& dt) {
	bool retval = false;

	os << dt.ID;
	return os;
}

