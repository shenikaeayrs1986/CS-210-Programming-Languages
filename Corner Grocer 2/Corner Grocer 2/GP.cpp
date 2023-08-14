#include "GP.h"
//This is the default constructor to be used when default file names are needed.This is the default constructor to be used when default file names are needed.
GP::GP() {
	setInputFileName("Groceries.txt");
	setOutputFileName("frequency.dat");
	readFile();
	writeFile();
}
//This constructor is used to assign particular file names.
GP::GP(string inputFileName, string outputFileName) {
	setInputFileName(inputFileName);
	setOutputFileName(outputFileName);
	readFile();
	writeFile();
}

void GP::setInputFileName(string fileName) {
	inputFileName = fileName;
}

void GP::setOutputFileName(string fileName) {
	outputFileName = fileName;
}
void GP::writeFile() {
	ofstream outFS;
	//command to open
	outFS.open(outputFileName);
	
	if (!outFS.is_open()) {
		cout << "Could not open file." << endl;
	}
	
	for (auto itr = gpMap.begin(); itr != gpMap.end(); itr++) {
		outFS << itr->first << " " << itr->second << endl;
	}

	//command to close
	outFS.close();
}
void GP::readFile() {
	//command to read
	ifstream inFS;
	//command to open
	inFS.open(inputFileName);
	if (!inFS.is_open()) {
		cout << "Could not open file";
	}
	string tempString;
	map<string, int> tempMap;
	while (!inFS.fail()) {
		inFS >> tempString;
		if (tempMap.count(tempString)) {
			tempMap[tempString] += 1;
		}
		else {
			tempMap.insert(std::pair<std::string, int>(tempString, 1));
		}
	}
	gpMap = tempMap;
	//command to close
	inFS.close();
}
void GP::printGPMap() {
	for (auto itr = gpMap.begin(); itr != gpMap.end(); itr++) {
		cout << itr->first << " " << itr->second << endl;
	}
}
//printMenu
void GP::printMenu() {
	cout << "||||||||||||||||||||||||||||||||||||||||||||M|E|N|U||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; 
	cout << endl;
	cout << "\033[1m\033[4mMain Menu:\033[0m" << endl; 
	cout << "\033[33m1. Find Your Grocery Item.\033" << endl; 
	cout << "\033[32m2. Display Grocery Items And Purchase Frequency.\033" << endl; 
	cout << "\033[31m3. Display ALL Grocery Items In Histogram\033" << endl; 
	cout << "\033[34m4. Program EXIT\033" << endl; 
	cout << "[0m"; 
	cout << "||||||||||||||||||||||||||||||||||||||||||||C|H|O|I|C|E|S||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl; 
	cout << endl;

	int choice = getMenuOption();
	
	executeMenuOption(choice);
}
void GP::run() {
	while (true) {
		printMenu();
	}
}
int GP::getMenuOption() {
	int menuOption;
	while (true) {
		cout << "Choose a menu option: ";
		cin >> menuOption;
		try {
			if (menuOption < 1 || menuOption > 4) {
				throw std::out_of_range("Invalid input. Value must be between 1 and 4.");
				menuOption = 0;
			}
			else {
				break;
			}
		}
		catch (std::out_of_range& e) {
			std::cout << e.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return menuOption;
}
//This function allows the program to select an action for the menu option input.
void GP::executeMenuOption(int choice) {
	//This function is used to clear out the console.
	system("cls");
	//If the user chooses the first option, this function will search for item.
	if (choice == 1) {
		searchForItem();
	}
	//If the user chooses the seconf option, this function will print the GP.
	else if (choice == 2) {
		printGPMap();
	}
	//If the user chooses the third option, this function will generate a histogram of the GP.
	else if (choice == 3) {
		printGPHistogram();
	}
	//If the user chooses the fourth option, this function will terminate the user's session.
	else if (choice == 4) {
		exit(0);
	}
	system("pause");
	system("cls");
}
void GP::searchForItem() {
	// Once the term has been provided by the user
	//The program will return the quantity of that item in the map if it exists. 
	//If there are no items, the program will return 0. 
	string input;
	//This is the boolean variable used to loop the program when an invalid 
	//input is entered.This is the boolean variable used to loop the program 
	//when an invalid input is entered.

	bool inputIsValid = false;
	while (!inputIsValid) {
		cout << "Kindly input the name of the item you wish to locate: ";
		cin >> input;
		//This function uses a try-and-catch block to authenticate user input.
		try {
			for (char c : input) {
				if (!isalpha(c)) {
					throw invalid_argument("I apologize, but the input provided is not a valid string. Please try again.");
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}

			// Declaration of valid input
			inputIsValid = true;

			// The program will carry out the applicable action if the user input is authenticated.
			if (gpMap.find(input) != gpMap.end()) {
				cout << "There are " << gpMap[input] << " " << input << " in the system." << endl;
			}
			else {
				cout << "There are no " << input << " in the system." << endl;
			}
		}
		catch (const invalid_argument& e) {
			cout << "Error: " << e.what() << std::endl;
		}
	}
}
//This function allows for the display of a histogram format of the GP map.
void GP::printGPHistogram() {
	//This function enables the program to show all items along with their corresponding asterisks.
	for (auto itr = gpMap.begin(); itr != gpMap.end(); itr++) {
		cout << itr->first << " ";
		int tempInt = itr->second;
		for (int i = 0; i < tempInt; i++) {
			cout << "*";
		}
		cout << endl;
	}
}