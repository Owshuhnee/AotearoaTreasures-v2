#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>	
using namespace std;

/*-------------------------------------- CLASS PRODUCT START ------------------------------------*/
class product {
	int id;
	string name;
	double price;
	int stock;
	string location;

public: //constructor
	product(int id, string name, double price, int stock, string location)
		: id(id), name(name), price(price), stock(stock), location(location) {
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
	void display() const {
		cout << "Location: " << location
			<< ", ID: " << id
			<< ", Name: " << name
			<< ", Price: $" << price
			<< ", Stock: " << stock << endl;
	}
}; /*------------------------------------ CLASS PRODUCT END -------------------------------------*/



/*------------------------------------ PRODUCT FUNCTIONS START ----------------------------------*/
class manageProduct {
	vector<product> products; // Vector to store products

public:
	// Function to add a product
	void addProduct() {
		int id, stockLevel;
		string name, location;
		double price;
		cout << "Enter Product ID: ";
		cin >> id;
		cin.ignore(); // Clear the newline character from the input buffer
		cout << "Enter Product Name: ";
		getline(cin, name);
		cout << "Enter Product Price: $";
		cin >> price;
		cout << "Enter Stock: ";
		cin >> stockLevel;
		cin.ignore(); // Clear the newline character from the input buffer
		cout << "Enter Location: ";
		getline(cin, location);
		addProduct(id, name, price, stockLevel, location);
	}

	// Function to add a product with validation
	void addProduct(int id, const string& name, double price, int stockLevel, const string& location) {
		for (const auto& p : products) {
			if (p.getID() == id && p.getLocation() == location) {
				cout << "Product with ID " << id << " already exists in " << location << "." << endl;
				return;
			}
		}
		products.emplace_back(id, name, price, stockLevel, location);
		cout << "\nPRODUCT ADDED SUCCESSFULLY" << endl;
	}

	// Function to display all products
	void displayProducts() const {
		if (products.empty()) {
			cout << "\nNo products available" << endl;
			return;
		}
		for (const auto& p : products) {
			p.display();
		}
	}

	// Function to display products for a specific branch/location
	void displayProductsByLocation(const string& location) const {
		bool found = false;
		for (const auto& p : products) {
			if (p.getLocation() == location) {
				p.display();
				found = true;
			}
		}
		if (!found) {
			cout << "\nNo products available in " << location << endl;
		}
	}

	// Function to update a product details
	void updateProduct(int id, const string& location) {
		for (auto& p : products) {
			if (p.getID() == id && p.getLocation() == location) {
				string newName;
				double newPrice;
				int newStock;
				cout << "Updating product ID " << id << " in " << location << endl;
				cout << "Enter new name: ";
				getline(cin, newName);
				p.setName(newName);
				cout << "Enter new price: ";
				cin >> newPrice;
				p.setPrice(newPrice);
				cout << "Enter new stock: ";
				cin >> newStock;
				p.setStock(newStock);
				cout << "Product updated successfully." << endl;
				return;
			}
		}
		cout << "Product with ID " << id << " not found in " << location << "." << endl;
	}

	void deleteProduct(int id, const string& location) {
		for (auto it = products.begin(); it != products.end(); ++it) {
			if (it->getID() == id && it->getLocation() == location) {
				products.erase(it);
				cout << "Product with ID " << id << " in " << location << " deleted successfully." << endl;
				return;
			}
		}
		cout << "Product with ID " << id << " not found in " << location << "." << endl;
	}

}; /*----------------------------------- PRODUCT FUNCTIONS END ----------------------------------*/

/*------------------- GLOBAL PRODUCT MANAGER (MOVED HERE) -------------------*/
manageProduct pm; // Global instance for product management

/*------------------- CUSTOMER DISPLAY FUNCTION (NEW) -------------------*/
void displayProductsForBranch(const string& branch) {
	cout << "\nPRODUCTS IN " << branch << " STORE:" << endl;
	pm.displayProductsByLocation(branch);
}

/*-------------------------------------- MENU FUNCTIONS START -----------------------------------*/
void mainMenu() {
	cout << "\nWelcome to Aotearoa Treasures!" << endl;
	cout << "Your one stop shop for NZ Souvenirs" << endl;
	cout << "-----------------------------------" << endl;
	cout << "\n1. Customer" << endl;
	cout << "2. Administrator" << endl;
	cout << "3. Exit" << endl;
	cout << "Please select an option: ";
}

void adminMenu() {
	cout << "\nADMINISTRATOR MENU" << endl;
	cout << "\n1. Manage Employees" << endl;
	cout << "2. Manage Products" << endl;
	cout << "3. Manage Store Locations" << endl;
	cout << "4. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

void adminProductsMenu() {
	cout << "\nMANAGE PRODUCTS" << endl;
	cout << "\n1. View Products" << endl;
	cout << "2. Add a Product" << endl;
	cout << "3. Update a Product" << endl;
	cout << "4. Delete a Product" << endl;
	cout << "5. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

void adminEmployeesMenu() {
	cout << "\nMANAGE EMPLOYEES" << endl;
	cout << "\n1. Add a new employee" << endl;
	cout << "2. Update Employee Details" << endl;
	cout << "3. Remove an Employee" << endl;
	cout << "4. Manage Employee Roster" << endl;
	cout << "5. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

void adminStoreLocationsMenu() {
	cout << "\nMANAGE STORE LOCATIONS" << endl;
	cout << "\n1. Add a new Store Location" << endl;
	cout << "2. Update Store Location Details" << endl;
	cout << "3. Remove a Store Location" << endl;
	cout << "4. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

void storelocationsMenu() {
	cout << "\nSTORE LOCATIONS" << endl;
	cout << "\n1. Auckland" << endl;
	cout << "2. Wellington" << endl;
	cout << "3. Christchurch" << endl;
	cout << "4. All Branches" << endl;
	cout << "5. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

void customerMenu() {
	cout << "\nCUSTOMER MENU" << endl;
	cout << "1. Buy Item" << endl;
	cout << "2. Back to Store selection" << endl;
	cout << "Please select an option: ";
}
/*------------------------------------ MENU FUNCTIONS END ---------------------------------------*/


/*------------------------------------- ADMIN SUB-MENU START ------------------------------------*/
void runadminEmployeesMenu() {
	int empChoice;
	do {
		adminEmployeesMenu();  // Show Menu
		cin >> empChoice; // Enter Choice

		switch (empChoice) {
		case 1:
			cout << "\nADD EMPLOYEE: (not implemented)" << endl;
			//CALL FUNCTION TO ADD EMPLOYEE HERE c/o ROSS
			break;
		case 2:
			cout << "\nUPDATE EMPLOYEE DETAILS: (not implemented)" << endl;
			// CALL FUNCTION TO UPDATE EMPLOYEE DETAILS HERE - c/o ROSS
			break;
		case 3:
			cout << "\nREMOVE EMPLOYEE: (not implemented)" << endl;
			// CALL FUNCTION TO REMOVE EMPLOYEE HERE - c/o ROSS
			break;
		case 4:
			cout << "\nMANAGE EMPLOYEE ROSTER: (not implemented)" << endl;
			// CALL FUNCTION TO MANAGE EMPLOYEE ROSTER HERE - c/o ROSS
			break;
		case 5:
			// BACK TO PREVIOUS MENU
			break;
		default:
			cout << "Invalid choice. Try again.\n";
		}
	} while (empChoice != 5);
}

void runadminProductsMenu() {

	//manageProduct pm; // REMOVED: Now using global pm
	int prodChoice;

	do {
		adminProductsMenu();  // Show Menu
		cin >> prodChoice; // Enter Choice
		switch (prodChoice) {


		case 1:
			// CALL FUNCTION TO VIEW PRODUCTS HERE c/o JOVE
			cout << "\nPRODUCTS IN STORE: " << endl;
			pm.displayProducts();
			break;

		case 2: // CALL FUNCTION TO ADD PRODUCT HERE c/o JOVE
			cout << "\nADD PRODUCT: " << endl;
			pm.addProduct();
			break;

		case 3: { // CALL FUNCTION TO UPDATE PRODUCT HERE c/o JOVE
			int id;
			string location;

			cout << "\nUPDATE PRODUCT: " << endl;
			cout << "Enter Product ID to update: ";
			cin >> id;
			cin.ignore();

			cout << "Enter the Store Location: ";
			getline(cin, location);

			pm.updateProduct(id, location);
			break;
		}

		case 4: {// CALL FUNCTION TO DELETE PRODUCT HERE c/o JOVE
			int id;
			string location;

			cout << "\nDELETE PRODUCT: " << endl;
			cout << "Enter Product ID to delete :";
			cin >> id;
			cin.ignore();

			cout << "Enter the Store location: ";
			getline(cin, location);

			pm.deleteProduct(id, location);
			break;
		}

		case 5:
			// BACK TO PREVIOUS MENU
			break;

		default:
			cout << "Invalid choice. Try again.\n";
		}
	} while (prodChoice != 5);
}

void runadminStoreLocationsMenu() {
	int storeChoice;
	do {
		adminStoreLocationsMenu();  // Show Menu
		cin >> storeChoice; // Enter Choice

		switch (storeChoice) {
		case 1:
			cout << "\nADD STORE LOCATION: (not implemented)" << endl;
			// CALL FUNCTION TO ADD STORE LOCATION HERE
			break;
		case 2:
			cout << "\nUPDATE STORE LOCATION: (not implemented)" << endl;
			// CALL FUNCTION TO UPDATE STORE LOCATION HERE
			break;
		case 3:
			cout << "\nREMOVE STORE LOCATION: (not implemented)" << endl;
			// CALL FUNCTION TO REMOVE STORE LOCATION HERE
			break;
		case 4:
			// BACK TO PREVIOUS MENU
			break;
		default:
			cout << "Invalid choice. Try again.\n";
		}
	} while (storeChoice != 4);
}
/*------------------------------------- ADMIN SUB-MENU END --------------------------------------*/



/*-------------------------------------- MAIN FUNCTION START ------------------------------------*/
int main() {
	int choice;

	/*------------------ CUSTOMER FUNCTIONS HERE ------------------*/

	do {
		mainMenu(); // Show Main Menu
		cin >> choice;


		if (choice == 1) {
			int storeLocationsChoice;
			do {
				storelocationsMenu(); //Show Menu
				cin >> storeLocationsChoice; // Customer enters choice

				switch (storeLocationsChoice) {
				case 1:
					cout << "\nYou have selected Auckland Store" << endl;
					displayProductsForBranch("Auckland");
					break;

				case 2:
					cout << "\nYou have selected Wellington Store" << endl;
					displayProductsForBranch("Wellington");
					break;

				case 3:
					cout << "\nYou have selected Christchurch Store" << endl;
					displayProductsForBranch("Christchurch");
					break;

				case 4:
					cout << "\nYou have selected All Branches" << endl;
					pm.displayProducts();
					break;

				case 5: //BACK TO PREVIOUS MENU
					break;

				default:
					cout << "Invalid input. Please try again" << endl;
					break;
				}
			} while (storeLocationsChoice != 5);
		}

		/*------------------ ADMIN FUNCTIONS HERE ------------------*/

		else if (choice == 2) {
			int adminChoice;

			do {
				adminMenu(); // Show Menu
				cin >> adminChoice; //Admin enters choice

				switch (adminChoice) {
				case 1:
					runadminEmployeesMenu(); // Show Sub-Menu
					break;

				case 2:
					runadminProductsMenu(); // Show Sub-Menu
					break;

				case 3:
					runadminStoreLocationsMenu(); // Show Sub-Menu
					break;

				case 4:// BACK TO PREVIOUS MENU
					break;

				default:
					cout << "Invalid input. Please try again" << endl;
					break;
				}
			} while (adminChoice != 4);
		}

		else if (choice == 3) {
			cout << "Exiting program." << endl;
			cout << "Thank you for using Aotearoa Treasures" << endl;
			return 0;
		}
		else {
			cout << "Invalid Input. Please try again" << endl;
			mainMenu();
		}
	} while (choice != 3);
	return 0;
}
/*------------------------------------ MAIN FUNCTION END -----------------------------------*/
