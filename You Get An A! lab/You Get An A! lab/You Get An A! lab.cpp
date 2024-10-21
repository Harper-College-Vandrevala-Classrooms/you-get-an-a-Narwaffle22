#include <iostream>
#include <vector>
#include <string>

using namespace std;

#pragma region Student Class
class Student {
public:
	Student(string, string, int);
	string getName();
	int getID();
	int getGrade();
	void setGrade(int);
private:
	string firstname;
	string lastname;
	int stuID;
	int currGrade;
};
Student::Student(string firstname, string lastname, int stuID) {
	this->firstname = firstname;
	this->lastname = lastname;
	this->stuID = stuID;
	currGrade = 0;
}
string Student::getName() {
	return firstname + lastname;
}
int Student::getID() {
	return stuID;
}
int Student::getGrade() {
	return currGrade;
}
void Student::setGrade(int newGrade) {
	currGrade = newGrade;
}

#pragma endregion

#pragma region Assingment Class
class Assignment {
public:
	Assignment(string, int);
	Assignment();
	string getName();
	int getPoints();
private:
	string name;
	int pntsPoss;
};
Assignment::Assignment(string name, int pntsPoss) {
	this->name = name;
	this->pntsPoss = pntsPoss;
}
Assignment::Assignment() {}
string Assignment::getName() {
	return name;
}
int Assignment::getPoints() {
	return pntsPoss;
}
#pragma endregion

#pragma region Gradebook Class
class Gradebook {
public:
	Gradebook();
	void addStudent(string, string);
	void addAssingment(string, int);
	void grade(string, int, int);
	void grade(string, string, int);
	void dispGradebook();
private:
	vector<Student> students;
	vector<int> stuIDs;
	vector<Assignment> assignments;
	int randID();
};
Gradebook::Gradebook() {}
void Gradebook::addStudent(string firstname, string lastname) {
	int id = randID();
	cout << "\nNew Student: " << firstname << " " << lastname << "\nTheir ID is: " << id;
	students.push_back(Student(firstname, lastname, id));
	stuIDs.push_back(id);
}
int Gradebook::randID() {
	srand((unsigned)time(NULL));
	return 1000 + (rand() % 9001);
}
void Gradebook::addAssingment(string name, int points) {
	cout << "\nNew Assignment: " << name;
	assignments.push_back(Assignment(name, points));
}
void Gradebook::grade(string assignName, int stuID, int grade) {
	int index = 0;
	Assignment whichAssignment;
	try {
		for (int i = 0; i < stuIDs.size(); i++) {
			if (stuID == stuIDs[i])
				index = i;
		}
		for (int j = 0; j < assignments.size(); j++) {
			if (assignName == assignments[j].getName())
				whichAssignment = assignments[j];
		}
		if (grade > whichAssignment.getPoints())
			throw "That is way too many points, try again with a lower value\n";
		int currGrade = students[index].getGrade();
		students[index].setGrade(currGrade + grade);
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	catch (...) {
		cout << "Unexpected exception!" << endl;
	}
}
void Gradebook::grade(string assignName, string stuName, int grade) {
	int index = 0;
	Assignment whichAssignment;
	bool isNotInList = true;
	try {
		for (int i = 0; i < students.size(); i++) {
			if (students[i].getName().compare(stuName)) {
				index = i;
				isNotInList = false;
			}
		}
		if (isNotInList)
			throw "\nStudent Entered either does not exist or is formatted improperly\n";
		for (int j = 0; j < assignments.size(); j++) {
			if (assignName == assignments[j].getName())
				whichAssignment = assignments[j];
		}
		if (grade > whichAssignment.getPoints())
			throw "\nThat is way too many points, try again with a lower value\n";
		int currGrade = students[index].getGrade();
		students[index].setGrade(currGrade + grade);
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	catch (...) {
		cout << "Unexpected exception!" << endl;
	}
}
void Gradebook::dispGradebook() {
	cout << "\n------ STUDENTS -----\n";
	for (int i = 0; i < students.size(); i++) {
		cout << students[i].getName() << "      ";
		cout << students[i].getGrade() << "\n";
	}
	cout << "---------------------\n";
	for (int j = 0; j < assignments.size(); j++) {
		cout << assignments[j].getName() << "      ";
		cout << assignments[j].getPoints() << "\n";
	}
	cout << "---------------------\n";
}
#pragma endregion

#pragma region Prompert Class
class Prompter {
public:
	Prompter();
	void startTheGradebook();
private:
	void addStudent();
	void addAssignment();
	void gradeStudent();
	Gradebook* gradebook = new Gradebook();
};
Prompter::Prompter() {
}
void Prompter::startTheGradebook() {
	string firstName, lastName;
	int command;
	bool inProgress = true;

	cout << "+-------------------------------+" << "\n";
	cout << "+    Welcome to The Grabook     +" << "\n";
	cout << "+-------------------------------+" << "\n\n";
	cout << "In order to start you must add a student?\n=> Please enter a student's first name: ";
	getline(cin, firstName);
	cout << "\nAwesome, and the last?\n=> Please enter a student's last name: ";
	getline(cin, lastName);
	gradebook->addStudent(firstName, lastName);

	cout << "\n\n!Follow The Instructions to Navigate!\n" << endl;

	cout << "[1] Add New Student" << endl;
	cout << "[2] Add new Assignment" << endl;
	cout << "[3] Grade a student's assignment" << endl;
	cout << "[4] Show Gradebook" << endl;
	cout << "[5] Exit" << endl;

	cout << "SELECT Command: ";
	cin >> command;

	while (inProgress) {
		switch (command) {
		case 1: {
			addStudent();
			cout << "\n\n!Run it Back!\n" << endl;

			cout << "[1] Add New Student" << endl;
			cout << "[2] Add new Assignment" << endl;
			cout << "[3] Grade a student's assignment" << endl;
			cout << "[4] Show Gradebook" << endl;
			cout << "[5] Exit" << endl;

			cout << "SELECT Command: ";
			cin >> command;
			break;
		}
		case 2: {
			addAssignment();
			cout << "\n\n!Run it Back!\n" << endl;

			cout << "[1] Add New Student" << endl;
			cout << "[2] Add new Assignment" << endl;
			cout << "[3] Grade a student's assignment" << endl;
			cout << "[4] Show Gradebook" << endl;
			cout << "[5] Exit" << endl;

			cout << "SELECT Command: ";
			cin >> command;
			break;
		}
		case 3: {
			gradeStudent();
			cout << "\n\n!Run it Back!\n" << endl;

			cout << "[1] Add New Student" << endl;
			cout << "[2] Add new Assignment" << endl;
			cout << "[3] Grade a student's assignment" << endl;
			cout << "[4] Show Gradebook" << endl;
			cout << "[5] Exit" << endl;

			cout << "SELECT Command: ";
			cin >> command;
			break;
		}
		case 4: {
			gradebook->dispGradebook();
			cout << "\n\n!Run it Back!\n" << endl;

			cout << "[1] Add New Student" << endl;
			cout << "[2] Add new Assignment" << endl;
			cout << "[3] Grade a student's assignment" << endl;
			cout << "[4] Show Gradebook" << endl;
			cout << "[5] Exit" << endl;

			cout << "SELECT Command: ";
			cin >> command;
			break;
		}
		case 5: {
			inProgress = false;
			cout << "See ya!";
			break;
		}
		}
	}
}
void Prompter::addStudent() {
	string firstName, lastName;
	cin.ignore();
	cout << "=> Please enter a student's first name: ";
	getline(cin, firstName);
	cout << "\n=> Please enter a student's last name: ";
	getline(cin, lastName);
	gradebook->addStudent(firstName, lastName);
}
void Prompter::addAssignment() {
	string assignName, temp;
	int pntsPoss;
	bool isANum = false;
	cin.ignore();
	cout << "=> Please enter the name of the assignment: ";
	getline(cin, assignName);
	while (!isANum) {
		cout << "\n=> Please the amount of points possible for the assignment: ";
		getline(cin, temp);
		isANum = true;
		for (char c : temp) {
			if (!isdigit(c)) {
				isANum = false;
			}
		}
	}
	pntsPoss = stoi(temp);
	gradebook->addAssingment(assignName, pntsPoss);
}
void Prompter::gradeStudent() {
	string stuName, assName, temp, jemp;
	int stuID, pnts;
	bool isANum = true;
	bool isANum2 = false;
	cin.ignore();
	cout << "=> Please enter the name or the ID of the student you want to grade: ";
	getline(cin, temp);
	for (char c : temp) {
		if (!isdigit(c)) {
			isANum = false;
		}
	}
	stuName = temp;
	cout << "\n=> Please enter the assignment you want to grade: ";
	getline(cin, assName);
	cin.ignore();
	while (!isANum2) {
		cout << "\n=> Please enter how many points the student earned: ";
		getline(cin, jemp);
		isANum2 = true;
		for (char c : jemp) {
			if (!isdigit(c)) {
				isANum2 = false;
			}
		}
	}
	pnts = stoi(jemp);
	if (isANum) {
		stuID = stoi(temp);
		gradebook->grade(assName, stuID, pnts);
	} else {
		gradebook->grade(assName, stuName, pnts);
	}
}

#pragma endregion

int main() {
	Gradebook *gradebook = new Gradebook();
	Prompter* prompt = new Prompter();
	prompt->startTheGradebook();

	/*
	gradebook->addStudent("John", "Smith");
	gradebook->addStudent("Jane", "Doe");
	gradebook->addStudent("James", "Monroe");
	gradebook->addAssingment("Unit 1 Test", 100);
	gradebook->addAssingment("Unit 2 Test", 100);
	gradebook->addAssingment("Unit 3 Test", 100);

	gradebook->grade("Unit 1 Test", "JohnSmith", 100);

	gradebook->dispGradebook();*/
}