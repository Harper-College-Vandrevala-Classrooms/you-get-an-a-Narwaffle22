#include <iostream>
#include <vector>

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
private:
	vector<Student> students;
	vector<int> stuIDs;
	vector<Assingment> assignments;
	int randID();
};
Gradebook::Gradebook() {}
void Gradebook::addStudent(string firstname, string lastname) {
	int id = randID();
	students.push_back(Student(firstname, lastname, id));
	stuIDs.push_back(id);
}
int Gradebook::randID() {
	srand((unsigned)time(NULL));
	return 1000 + (rand() % 9001);
}
void Gradebook::addAssingment(string name, int points) {
	assignments.push_back(Assingment(name, points));
}

#pragma endregion

int main() {
	cout << "hello World";
}