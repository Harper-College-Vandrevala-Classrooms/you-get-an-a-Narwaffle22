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
class Assingment {
public:
	Assingment(string, int);
	Assingment();
	string getName();
	int getPoints();
private:
	string name;
	int pntsPoss;
};
Assingment::Assingment(string name, int pntsPoss) {
	this->name = name;
	this->pntsPoss = pntsPoss;
}
Assingment::Assingment() {}
string Assingment::getName() {
	return name;
}
int Assingment::getPoints() {
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
	vector<Assingment> assignments;
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
	assignments.push_back(Assingment(name, points));
}
void Gradebook::grade(string assignName, int stuID, int grade) {
	int index = 0;
	Assingment whichAssignment;
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
	Assingment whichAssignment;
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

int main() {
	Gradebook *gradebook = new Gradebook();

	gradebook->addStudent("John", "Smith");
	gradebook->addStudent("Jane", "Doe");
	gradebook->addStudent("James", "Monroe");
	gradebook->addAssingment("Unit 1 Test", 100);
	gradebook->addAssingment("Unit 2 Test", 100);
	gradebook->addAssingment("Unit 3 Test", 100);

	gradebook->grade("Unit 1 Test", "JohnSmith", 100);

	gradebook->dispGradebook();
}