#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <random>

struct CharSets {
	bool lowercase;
	bool uppercase;
	bool numbers;
	bool specialCharacters;
};

int getPasswordLength() {
	int lengthPassword;
	constexpr int MIN = 8;
	constexpr int MAX = 32;

	while (true) {
		std::cout << "Enter a password length between " << MIN << " and " << MAX << ": ";
		std::cin >> lengthPassword;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error! Please, enter a number." << std::endl;
		} 
		else if (lengthPassword < MIN || lengthPassword > MAX) {
			std::cout << "Error! Length must be between " << MIN << " and " << MAX << std::endl;
		} 
		else {
			std::cout << "Accepted: " << lengthPassword << std::endl;
			return lengthPassword;
		}
	}	
}

void menuCategories() {
	std::cout << "1. Lowercase a - z" << std::endl;
	std::cout << "2. Uppercase A - Z" << std::endl;
	std::cout << "3. Numbers 0 - 9" << std::endl;
	std::cout << "4. Special characters !@#$ % ^&*()_ + -= [] {} | ;:, .<> ?" << std::endl;
}

CharSets getCategories() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (true) {
		CharSets selected{};
		bool hasValid = false;
		bool hasInvalid = false;

		menuCategories();
		std::cout << "Enter menu numbers separated by spaces: " << std::endl;
		std::string numberMenu;
		std::getline(std::cin, numberMenu);
		if (numberMenu == "") {
			hasInvalid = true;
		}
		std::istringstream iss(numberMenu);

		int number;
		while (iss >> number) {
			if (number >= 1 && number <= 4) {
				hasValid = true;
				switch (number)
				{
				case 1: selected.lowercase = true; break;
				case 2: selected.uppercase = true; break;
				case 3: selected.numbers = true; break;
				case 4: selected.specialCharacters = true; break;
				}
			}
			else {
				hasInvalid = true; break;
			}
		}
		if (hasInvalid || !hasValid) {
			std::cout << "Invalid numbers entered or no categories selected. Please try again." << std::endl;
		}
		else {
			return selected;
		}
	}
}

int generatePassword() {

	return 0;
}

int main() {
	//int lengthPassword = getPasswordLength();
	//CharSets sets = getCategories();
	generatePassword();

	return 0;
}