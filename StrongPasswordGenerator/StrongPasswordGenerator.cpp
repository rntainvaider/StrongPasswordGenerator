#include <iostream>
#include <limits>

int getPasswordLength() {
	int lenPassword;
	constexpr int MIN = 8;
	constexpr int MAX = 32;

	while (true) {
		std::cout << "Enter a password length between " << MIN << " and " << MAX << ": ";
		std::cin >> lenPassword;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error! Please, enter a number." << std::endl;
		} else if (lenPassword < MIN || lenPassword > MAX) {
			std::cout << "Error! Length must be between " << MIN << " and " << MAX << std::endl;
		} else {
			std::cout << "Accepted: " << lenPassword << std::endl;
			return lenPassword;
		}
	}	
}

int main() {
	int lenPassword = getPasswordLength();

	return 0;
}