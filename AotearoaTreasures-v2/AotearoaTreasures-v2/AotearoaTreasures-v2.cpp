#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

//Function to check for errors in user input
void errorCheck(int& choice) {
	string input;
	while (true) {
		getline(cin, input);
		stringstream ss(input);
		if (ss >> choice && ss.eof()) {
			break;
		}
		else {
			cout << "Invalid choice. Please try again.\n";
			cout << "---------------------------------------------" << endl;
			cout << "Please select an option: ";
		}
	}
}

/*-------------------------------------- CLASS PRODUCT START ------------------------------------*/
class product {
	int id;
	string name;
	double price;
	int stock;
	string location;

public: //constructor
	product(int i, const string& n, double p, int s, const string& l)
		: id(i), name(n), price(p), stock(s), location(l) {
	}

	//Getters
	int getID() const { return id; }
	string getName() const { return name; }
	double getPrice() const { return price; }
	int getStock() const { return stock; }
	string getLocation() const { return location; }

	//Setters
	void setID(int newID) { id = newID; }
	void setName(const string& newName) { name = newName; }
	void setPrice(double newPrice) { price = newPrice; }
	void setStock(int newStock) { stock = newStock; }
	void setLocation(const string& newLocation) { location = newLocation; }

	//Display Product Details
	void display(bool showLocation = true) const {
		cout << "---------------------------------------------" << endl;
		if (showLocation)
			cout << "Location: " << location << endl;
			cout << "ID: " << id << endl;
			cout << "Name: " << name << endl;
			cout << "Price: $" << fixed << setprecision(2) << price << endl;
			cout << "Stock: " << stock << endl;
	}

};


/*-------------------------------------- CLASS EMPLOYEE START -----------------------------------*/
class Employee {
public:
	int id;
	string name;
	int storeId;
	string storeName;
	vector<string> schedule;

	// Constructor - creates a new employee with default "off" schedule
	Employee(int i, string n, int sId, string sName) {
		id = i;
		name = n;
		storeId = sId;
		storeName = sName;
		schedule = vector<string>(7, "off");

		for (int day = 0; day < 7; day++) {
			schedule[day] = "off";
		}
	}

	// Show this employee's schedule in a nice format
	void showRoster() {
		cout << "\nID: " << id << ", Name: " << name << ", Store: " << storeName << endl;
		cout << "Mon: " << schedule[0] << " Tue: " << schedule[1] << " Wed: " << schedule[2] << endl;
		cout << "Thu: " << schedule[3] << " Fri: " << schedule[4] << " Sat: " << schedule[5] << " Sun: " << schedule[6] << endl;
		cout << endl;
	}

	// Update a specific day's shift
	void updateShift(int day, string shift) {
		if (day >= 1 && day <= 7) {
			schedule[day - 1] = shift;
		}
		else {
			cout << "Entered incorrect day" << endl;
		}
	}
}; 


/*--------------------------------------- CLASS STORE START -------------------------------------*/
class Store {
public:
	string name;
	int id;
};


/*----------------------------------- EMPLOYEE FUNCTIONS START ----------------------------------*/
vector<Employee> employees;

// Example shifts
void setupEmployees() {
	Employee e1(101, "Example employee 1", 1, "Auckland");
	e1.schedule[0] = "am";
	e1.schedule[1] = "pm";
	e1.schedule[2] = "am";
	employees.push_back(e1);

	Employee e2(102, "Example employee 2", 1, "Auckland");
	e2.schedule[0] = "PM";
	e2.schedule[3] = "AM";
	e2.schedule[4] = "PM";
	employees.push_back(e2);
}

// Edit an existing employee shift
void editEmployeeShift() {
	cout << "\n========== EDIT EMPLOYEE SHIFT ==========" << endl;

	int id;
	cout << "Please enter the employee ID: ";
	cin >> id;

	int index = -1; // Sets ID to "not found yet"
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].id == id) {
			index = i; // Remembers where we found them
			break;
		}
	}

	if (index == -1) {
		cout << "No matching employee with entered ID" << endl;
		return;
	}

	employees[index].showRoster();

	int day;
	cout << "Select a day to change" << endl;
	cout << "(1) Monday, (2) Tuesday, (3) Wednesday, (4) Thursday, (5) Friday" << endl;
	cout << "(6) Saturday, (7) Sunday\n" << endl;
	cin >> day;

	string shift;
	cout << "Select a new shift (am/pm/off)" << endl;
	cin >> shift;

	employees[index].updateShift(day, shift);
	cout << "Shift has been updated" << endl;
	employees[index].showRoster();
}

// Add a new employee to the system
void addNewEmployee() {
	cout << "\nAdd New Employee" << endl;

	int id, storeId;
	string name, storeName;

	cout << "Please enter the new employee ID: ";
	cin >> id;

	cout << "Please enter the new employee name: ";
	cin.ignore();
	getline(cin, name);

	cout << "Please enter the store ID: ";
	cin >> storeId;

	cout << "Please enter the store name: ";
	cin.ignore();
	getline(cin, storeName);

	Employee newEmployee(id, name, storeId, storeName);
	employees.push_back(newEmployee);

	cout << "Thank you. New employee has now been added\n" << endl;
	newEmployee.showRoster();
}

// Remove an employee from the system
void removeEmployee() {
	cout << "\nRemove Employee" << endl;

	// Check if there are any employees to remove
	if (employees.size() == 0) {
		cout << "No employees in the system to remove" << endl;
		return;
	}

	// Show all current employees
	cout << "Current employees in the system:" << endl;
	for (int i = 0; i < employees.size(); i++) {
		cout << "ID: " << employees[i].id << " - " << employees[i].name
			<< " (Store: " << employees[i].storeName << ")" << endl;
	}
	cout << "" << endl;

	// Step 3: Enter which employee to remove
	int employeeIdToRemove;
	cout << "\nEnter the ID of the employee you want to remove (or enter 0 to cancel): ";
	cin >> employeeIdToRemove;

	// Check if user wants to cancel
	if (employeeIdToRemove == 0) {
		cout << "Operation cancelled. Returning to main menu." << endl;
		return; // Exit the function - go back to main menu
	}

	// Find employee
	int foundIndex = -1;
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].id == employeeIdToRemove) {
			foundIndex = i;
			break;
		}
	}

	// Checks if employee is found
	if (foundIndex == -1) {
		cout << "Error: No employee found with ID " << employeeIdToRemove << endl;
		return; // Exit the function early
	}

	// Shows the employee being removed
	cout << "\nEmployee to be removed: " << endl;
	employees[foundIndex].showRoster();

	// Ask for confirmation
	char confirmation;
	cout << "Confirm the removal of this employee? (y/n): ";
	cin >> confirmation;

	if (confirmation == 'y' || confirmation == 'Y') {
		string removedName = employees[foundIndex].name; // Save name for confirmation message

		employees.erase(employees.begin() + foundIndex);

		// Confirms
		cout << "\n✓ SUCCESS! Employee '" << removedName << "' has been removed from the system." << endl;
		cout << "Total employees remaining: " << employees.size() << endl;
	}
	else {
		// Cancels
		cout << "\nRemoval cancelled. Employee has NOT been removed." << endl;
	}
}


/*------------------------------------ PRODUCT FUNCTIONS START ----------------------------------*/
class manageProduct {
	vector<product> products; // Vector to store products

public:

	// Save products to a file
	void saveProductsToFile(const string& filename) {
		ofstream file(filename);  // Use filename, not hardcoded "products.txt"
		if (!file.is_open()) {
			cout << "Error opening file for writing.\n";
			return;
		}
		for (const auto& p : products) {
			file << p.getID() << "," << p.getName() << "," << p.getPrice() << ","
				<< p.getStock() << "," << p.getLocation() << "\n";
		}
	}

	//Load products from a file
	void loadProductsFromFile(const string& filename) {
		ifstream in(filename);
		if (!in) {
			cout << "No previous data found. Starting fresh.\n";
			return;
		}

		products.clear(); 

		string line;
		while (getline(in, line)) {
			stringstream ss(line);
			string name, location;
			int id, stock;
			double price;

			string token;
			getline(ss, token, ','); id = stoi(token);
			getline(ss, name, ',');
			getline(ss, token, ','); price = stod(token);
			getline(ss, token, ','); stock = stoi(token);
			getline(ss, location);

			products.emplace_back(id, name, price, stock, location);
		}
		in.close();
	}

	// FUNCTION TO ADD A PRODUCT
	void addProduct() {
		int id, stockLevel, choice;
		string name, location;
		double price;

		cout << "---------------------------------------------" << endl;

		cout << "Enter Product ID: ";
		while (!(cin >> id)) {
			cout << "Error: Please enter a valid ID: ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Enter Product Name: ";
		getline(cin, name);

	
		cout << "Enter Product Price: $";
		while (!(cin >> price)) {
			cout << "Error: Please enter a valid amount: $";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		
		cout << "Enter Stock: ";
		while (!(cin >> stockLevel)) {
			cout << "Error: Please enter a valid stock: ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		
		while (true) {
			cout << "\nChoose Store Location:\n";
			cout << "1. Auckland\n";
			cout << "2. Wellington\n";
			cout << "3. Christchurch\n";
			cout << "Please select an option: ";

			errorCheck(choice); 

			if (choice == 1) { location = "Auckland"; break; }
			else if (choice == 2) { location = "Wellington"; break; }
			else if (choice == 3) { location = "Christchurch"; break; }
			else {
				cout << " Invalid choice. Please try again.\n";
			}
		}

		addProduct(id, name, price, stockLevel, location);
	}


	// FUNCTION TO ADD A PRODUCT WITH VALIDATION
	void addProduct(int id, const string& name, double price, int stockLevel, const string& location) {
		for (const auto& p : products) {
			if (p.getID() == id && p.getLocation() == location) {
				cout << "\nPRODUCT ALREADY EXIST IN " << location << "." << endl;
				return;
			}
		}
		products.emplace_back(id, name, price, stockLevel, location);
		system("cls");
		cout << "\nPRODUCT ADDED SUCCESSFULLY" << endl;

		saveProductsToFile("products.txt");
	}

	
	// FUNCTION TO DISPLAY ALL PRODUCTS
	void displayProducts() const {
		if (products.empty()) {
			cout << "\nNO PRODUCTS AVAILABLE" << endl;
			return;
		}
		for (const auto& p : products) {
			p.display(true); // Show location
		}
	}


	// FUNCTION TO DISPLAY PRODUCTS BY LOCATION
	void displayProductsByLocation(const string& location) const {
		bool found = false;
		for (const auto& p : products) {
			if (p.getLocation() == location) {
				p.display(false); 
				found = true;
			}
		}
		if (!found) {
			cout << "NO PRODUCTS AVAILABLE" << endl;
		}
	}


	// FUNCTION TO DISPLAY LOW STOCK PRODUCTS
	void lowStockProducts() const {
		bool found = false;
		for (const auto& p : products) {
			if (p.getStock() < 5) {
				p.display();
				found = true;
			}
		}
		if (!found) {
			cout << "No products with low stock." << endl;
		}
	}


	// FUNCTION TO UPDATE A PRODUCT
	void updateProduct(int id, const string& location) {
		for (auto& p : products) {
			if (p.getID() == id && p.getLocation() == location) {
				string newName;
				double newPrice;
				int newStock;

				cout << fixed << setprecision(2);
				system("cls");
				cout << "\nUpdating product " << id << " in " << location << endl;
				cout << p.getName() << " $" << p.getPrice() << " - " << p.getStock() << " in stock" << endl;

				cout << "\n---------------------------------------------" << endl;
				cout << "Enter new name: ";
				getline(cin, newName);
				p.setName(newName);

				cout << "Enter new price: $";
				while (!(cin >> newPrice)) {
					cout << "Error: Please enter a valid Price $";
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				cout << "Enter new stock: ";
				while (!(cin >> newStock)) {
					cout << "Error: Please enter a valid stock ";
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				p.setPrice(newPrice);
				p.setStock(newStock);

				cout << "\nPRODUCT UPDATED SUCCESSFULLY" << endl;
				return;
			}
		}
		cout << "Product with ID " << id << " not found in " << location << "." << endl;
	}


	// FUNCTION TO DELETE A PRODUCT
	void deleteProduct(int id, const string& location) {
		for (auto it = products.begin(); it != products.end(); ++it) {
			if (it->getID() == id && it->getLocation() == location) {
				products.erase(it);
					cout << "\nPRODUCT DELETED SUCCESSFULLY" << endl;
				return;
			}
		}
		cout << "Product with ID " << id << " not found in " << location << "." << endl;
	}
}; 


/*------------------------------------ CUSTOMER FUNCTIONS START ---------------------------------*/
vector<product> products; 

//Customer buy product function
void buyProductAsCustomer() {
	manageProduct pm; 	
	int id, quantity;
	string location;
	pm.displayProducts();

	cout << "\n--- BUY PRODUCT ---" << endl;
	cout << "Enter Product ID to buy: ";
	cin >> id;
	cin.ignore();
	cout << "Enter Store Location: ";
	getline(cin, location);

	bool found = false;
	for (auto& p : products) { 
		if (p.getID() == id && p.getLocation() == location) {
			found = true;
			cout << "Enter quantity to buy: ";
			cin >> quantity;
			if (quantity <= 0) {
				cout << "Invalid quantity." << endl;
				return;
			}
			if (quantity > p.getStock()) {
				cout << "Not enough stock available." << endl;
				return;
			}
			p.setStock(p.getStock() - quantity);
			cout << "Purchase successful! " << quantity << " x " << p.getName()
				<< " bought for $" << p.getPrice() * quantity << endl;
			return;
		}
	}
	if (!found) {
		cout << "Product not found in the specified location." << endl;
	}
}


/*------------------------------------------- MENU START ----------------------------------------*/
void mainMenu() {
	system("cls");
	cout << "\n=============================================\n" << endl;
	cout << "       Welcome to Aotearoa Treasures!" << endl;
	cout << "    Your one-stop shop for NZ Souvenirs\n" << endl;
	cout << "=============================================\n" << endl;
	cout << "                   MAIN MENU\n" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "\n1. Customer" << endl;
	cout << "2. Administrator" << endl;
	cout << "3. Exit\n" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Please select an option: ";
}

void adminMenu() {
	system("cls");
	cout << "=============================================\n" << endl;
	cout << "              ADMINISTRATOR MENU\n" << endl;
	cout << "=============================================\n" << endl;
	cout << "1. Manage Employees" << endl;
	cout << "2. Manage Products" << endl;
	cout << "3. Back to previous menu\n" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Please select an option: ";
}

void adminProductsMenu() {
	cout << "=============================================\n" << endl;
	cout << "                PRODUCTS MENU\n" << endl;
	cout << "=============================================\n" << endl;
	cout << "1. View Products" << endl;
	cout << "2. Add a Product" << endl;
	cout << "3. Update a Product" << endl;
	cout << "4. Delete a Product" << endl;
	cout << "5. View Low stock Products" << endl;
	cout << "6. Back to previous menu\n" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Please select an option: ";
}

void storelocationsMenu() {
	system("cls");
	cout << "\nChoose Store Location:" << endl;
	cout << "1. Auckland" << endl;
	cout << "2. Wellington" << endl;
	cout << "3. Christchurch" << endl;
	cout << "4. All Branches" << endl;
	cout << "5. Back to previous menu\n" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Please select an option: ";
}

void customerMenu() { //Porky has done this function
	cout << "\n=============================================\n" << endl;
	cout << "                 CUSTOMER MENU\n" << endl;
	cout << "=============================================\n" << endl;
	cout << "1. Buy Item" << endl;
	cout << "2. Back to Store selection\n" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Please select an option: ";
}/*----------------------------------- MENU FUNCTIONS END ---------------------------------------*/


/*-------------------------------------- SUB-FUNCTIONS START ------------------------------------*/
void runadminEmployeesFunction() {
		Store s1;
		s1.name = "Auckland";
		s1.id = 1;
		vector<Store> stores;
		stores.push_back(s1);

		setupEmployees();

		int choice;
		cout << " \nWelcome to the Employee Roster System  \n" << endl;

		do {
			cout << "\nSelect an option" << endl;
			cout << "(1) View Employees" << endl;
			cout << "(2) Edit a shift" << endl;
			cout << "(3) Add new employee" << endl;
			cout << "(4) Remove employee" << endl;
			cout << "(5) Exit" << endl;
			cout << "\nEnter your choice (1-5): ";
			cin >> choice;

			if (choice == 1) {
				// Show all employees
				cout << "\nAll Employees: " << endl;
				if (employees.size() == 0) {
					cout << "No employees in the system." << endl;
				}
				else {
					for (int i = 0; i < employees.size(); i++) {
						employees[i].showRoster();
					}
				}
			}
			else if (choice == 2) {
				// Edit a shift
				if (employees.size() == 0) {
					cout << "\nNo employees in the system to edit!" << endl;
				}
				else {
					editEmployeeShift();
				}
			}
			else if (choice == 3) {
				// Add new employee
				addNewEmployee();
			}
			else if (choice == 4) {
				// Remove employee
				removeEmployee();
			}
			else if (choice == 5) {
				// Exit the program
				cout << "\nThank you for using the Employee Roster System!" << endl;
				cout << "Goodbye!" << endl;
			}
			else {
				// Invalid choice
				cout << "\nInvalid choice! Please enter a number between 1 and 5." << endl;
			}

		} while (choice != 5);
	}

void runadminProductsFunction(manageProduct& pm) {
	int choice;

	do {
		adminProductsMenu();
		errorCheck(choice);

		switch (choice) {

		case 1:
			// CALL FUNCTION TO VIEW PRODUCTS HERE
			int choice;
			storelocationsMenu(); 
			errorCheck(choice);

			switch (choice) {
				case 1: // Auckland
					system("cls");
					cout << "\nProducts in Auckland" << endl;
					pm.displayProductsByLocation("Auckland");
					break;

				case 2: // Wellington
					system("cls");
					cout << "\nProducts in Wellington" << endl;
					pm.displayProductsByLocation("Wellington");
					break;

				case 3: // Christchurch
					system("cls");
					cout << "\nProducts in Christchurch" << endl;
					pm.displayProductsByLocation("Christchurch");
					break;

				case 4: // All Branches
					system("cls");
					cout << "\nProducts in all store locations:" << endl;
					pm.displayProducts(); 
					break;

				case 5: // Back to previous menu
					break;

				default:
					cout << "Invalid choice. Please try again.\n";
				}
			break;

		case 2: // CALL FUNCTION TO ADD PRODUCT HERE
			system("cls");
			cout << "\nADD PRODUCT: " << endl;
			pm.addProduct();
			break;

		case 3: { // CALL FUNCTION TO UPDATE PRODUCT HERE
			int id, choice;
			string location;

			system("cls");
			cout << "=============================================" << endl;
			cout << "UPDATE PRODUCT: " << endl;
			cout << "=============================================" << endl;
			cout << "\nChoose Store Location:\n";
			cout << "1. Auckland\n";
			cout << "2. Wellington\n";
			cout << "3. Christchurch\n";
			
			while (true) {
				cout << "---------------------------------------------" << endl;
				cout << "Please select an option: ";
				errorCheck(choice);
				
				if		(choice == 1) { location = "Auckland"; break; }
				else if (choice == 2) { location = "Wellington"; break; }
				else if (choice == 3) { location = "Christchurch"; break; }
				else {
					cout << "Invalid choice. Please try again.\n";
				}
			}
				system("cls");	
				cout << "\nProducts in " << location << endl;
				pm.displayProductsByLocation(location);
				cout << "---------------------------------------------" << endl;
				cout << "Enter Product ID to update: ";
				cin >> id;
				cin.ignore();

				pm.updateProduct(id, location);
				break;
		}

		case 4: {// CALL FUNCTION TO DELETE PRODUCT HERE
			int id, locationChoice;
			string location;

			system("cls");
			cout << "=============================================" << endl;
			cout << "DELETE PRODUCT: " << endl;
			cout << "=============================================" << endl;
			cout << "\nChoose Store Location:\n";
			cout << "1. Auckland\n";
			cout << "2. Wellington\n";
			cout << "3. Christchurch\n";
			
			while (true) {
				cout << "---------------------------------------------" << endl;
				cout << "Please select an option: ";
				errorCheck(choice);
							
				if		(choice == 1) { location = "Auckland"; break; }
				else if (choice == 2) { location = "Wellington"; break; }
				else if (choice == 3) { location = "Christchurch"; break; }
				else {
					cout << "Invalid choice. Please try again.\n";
				}
			}
			system("cls");
			cout << "\nProducts in " << location << endl;
			pm.displayProductsByLocation(location);
			cout << "---------------------------------------------" << endl;
			cout << "Enter Product ID to delete: ";
			cin >> id;
			cin.ignore();

			pm.deleteProduct(id, location);
			break;
		}

		case 5: // CALL FUNCTION TO VIEW LOW STOCK PRODUCTS HERE
			system("cls");
			cout << "\nLow Stock products - All Stores:" << endl;
			pm.lowStockProducts();
			break;

		case 6:
			// BACK TO PREVIOUS MENU
			break;

		default:
			cout << "---------------------------------------------" << endl;
			cout << "Invalid choice. Try again.\n";
			}
	} while (choice != 6);
};

void runCustomerFunction() {
	
		customerMenu(); 
		int customerChoice;
		cin >> customerChoice;
		switch (customerChoice) {
		case 1:
			buyProductAsCustomer();
			break;
		case 2:
			break;
		default:
			cout << "Invalid input. Please try again" << endl;
			break;
		}
	}



/*-------------------------------------- MAIN FUNCTION START ------------------------------------*/
int main() {
	int mainChoice;
	manageProduct pm; 
	pm.loadProductsFromFile("products.txt");
	
	do {
		mainMenu();
		errorCheck(mainChoice); 

		// CUSTOMER FUNCTIONS HERE
		if (mainChoice == 1) {
			runCustomerFunction(); //This calls out the script done by Porky
		}
			
		// ADMINISTRATOR FUNCTIONS HERE
		else if (mainChoice == 2) {
			int adminChoice;
			do {
				adminMenu();
				errorCheck(adminChoice);
				
				switch (adminChoice) {
				case 1:
					runadminEmployeesFunction(); //This calls out the script done by ROSS
					break;

				case 2:
					runadminProductsFunction(pm); //This calls out the script done by JOVE
					break;
							
				case 3:
					// BACK TO PREVIOUS MENU
					break;

				default:
					cout << "Invalid input. Please try again" << endl;
					break;
				}
			} while (adminChoice != 3);
		}

		else if (mainChoice == 3) {
			cout << "Exiting program." << endl;
			cout << "Thank you for using Aotearoa Treasures" << endl;
			return 0;
		}
		else {
			cout << "Error" << endl;
		}
	} while (mainChoice != 3);
		pm.saveProductsToFile("products.txt");
		return 0;
	} 