#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <algorithm>

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

std::string generatePassword(int length, const CharSets& sets) {
	std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
	std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string numbers = "0123456789";
	std::string specialCharacters = "!@#$%^&*()_+-=[]{}|;:,.<>?";

	std::string full_pool;
	std::vector<const std::string*> required_pools;

	if (sets.lowercase) {
		full_pool += lowercase;
		required_pools.push_back(&lowercase);
	}

	if (sets.uppercase) {
		full_pool += uppercase;
		required_pools.push_back(&uppercase);
	}

	if (sets.numbers) {
		full_pool += numbers;
		required_pools.push_back(&numbers);
	}

	if (sets.specialCharacters) {
		full_pool += specialCharacters;
		required_pools.push_back(&specialCharacters);
	}

	std::string password(length, '\0');

	std::random_device rd;
	std::mt19937 gen(rd());

	for (size_t i = 0; i < required_pools.size(); i++) {
		const std::string* pool = required_pools[i];
		std::uniform_int_distribution<size_t> dist(0, pool->size() - 1);
		size_t idx = dist(gen);
		password[i] = (*pool)[idx];
	}

	for (size_t i = required_pools.size(); i < length; i++)
	{
		std::uniform_int_distribution<size_t> dist(0, full_pool.size() - 1);
		size_t idx = dist(gen);
		password[i] = full_pool[idx];
	}
	std::shuffle(password.begin(), password.end(), gen);

	return password;
}

int main() {
	int lengthPassword = getPasswordLength();
	CharSets sets = getCategories();
	std::string password = generatePassword(lengthPassword, sets);

	std::cout << "Generated password: " << password << std::endl;

	return 0;
}