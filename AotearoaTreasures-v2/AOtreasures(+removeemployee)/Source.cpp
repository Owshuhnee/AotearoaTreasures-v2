#include <iostream>
#include <string>
#include <vector>
using namespace std;

//ADD USER ROLES HERE (CUSTOMER, ADMINISTRATOR)

//CLASS STORE HERE
class Store {
public:
	string name;
	int id;
};

//CLASS EMPLOYEE HERE
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

// Global list of all employees
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

// checks if ID already exists
bool existingEmployeeId(int employeeId) {
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].id == employeeId) {
			return true; // existing ID
		}
	}
	return false; // unique ID
}



// Add a new employee to the system
void addNewEmployee() {
	cout << "\nAdd New Employee" << endl;

	int id, storeId;
	string name, storeName;


	do {
		cout << "Please enter the new employee ID: ";
		cin >> id;

		if (existingEmployeeId(id)) {
			cout << "Error: That ID already exists" << endl;
			cout << "Please try again" << endl;
		}

	} while (existingEmployeeId(id));

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



void updateEmployee() {

	int employeeId;
	int foundIndex = -1;
	int updateOption;

	cout << "Please enter an Employee ID to update: ";
	cin >> employeeId;

	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].id == employeeId) {
			foundIndex = i;
			break;
		}
	}

	if (foundIndex == -1) {
		cout << "Could not find an employee with matching ID" << endl;
		return;
	}

	cout << "Employee's current details:" << endl;
	cout << "Name: " << employees[foundIndex].name << endl;
	cout << "Store ID: " << employees[foundIndex].id << endl;
	cout << "Store: " << employees[foundIndex].storeName << endl;

	cout << "Select what to update: " << endl;
	cout << "(1) Name" << endl;
	cout << "(2) Store ID" << endl;
	cout << "(3) Store Name" << endl;
	cout << "(4) Cancel" << endl;

	cin >> updateOption;

	switch(updateOption) {

	case 1: {

		string newName;
		cin.ignore();
		getline(cin, newName);
		employees[foundIndex].name = newName;

		cout << "Name updated" << endl;
		cout << "New name: " << employees[foundIndex].name << endl;
		break;
	}

	case 2: {

		int newId;
		do {
			cout << "Enter new Employee ID: ";
			cin >> newId;
			if (newId == employees[foundIndex].id) {
				break;
			}
			else if (existingEmployeeId(newId)) {
				cout << "That ID already exists. Please choose another ID" << endl;
			}
			else {
				break;
			}
		} while (true);

		employees[foundIndex].id = newId;

		cout << "Employee ID updated" << endl;
		cout << "New Employee ID: " << employees[foundIndex].id << endl;
		break;

	}

	case 3: {

		string newStoreName;
		cin.ignore();
		getline(cin, newStoreName);
		employees[foundIndex].storeName = newStoreName;

		cout << "Store has been updated successfully" << endl;
		cout << "New Store: " << employees[foundIndex].storeName << endl;
		break;
	}

	default:
		cout << "Cancelling updating" << endl;
		break;

	}
}



int main() {
	Store s1;
	s1.name = "Auckland";
	s1.id = 1;
	vector<Store> stores;
	stores.push_back(s1);

	setupEmployees();

	int choice;
	cout << " \n Welcome to the Employee Roster System  \n" << endl;

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

	return 0;
}