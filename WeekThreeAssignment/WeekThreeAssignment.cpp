/* * * * * * * * * * * *
 * Austin Ozan         *
 * Week 3 Assignment   *
 * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                       * * * OBJECTIVE * * *                                           *
 * - You need to create a class called Student that holds a student's first name, last name, and grade   *
 *                                                                                                       *
 * - Your program should be able read a file that looks like the file "example.txt" included below.      *
 *   It should contain names of students and their grades, and resemble something like:                  *
 *                                                                                                       *
 * Dave Grohl 95                                                                                         *
 * Taylor Hawkins 75                                                                                     *
 *                                                                                                       *
 * - Your program should read each line from the text file, and store that line's data in a              *
 *   Student object (which should then be added to a vector of Students). You'll need to break           *
 *   down each line into the proper components (a firstName, lastName, and grade) by using string        *
 *   functions we previously discussed.                                                                  *
 *                                                                                                       *
 * - Once you've gotten each student into your list, sort it by highest grade to lowest,                 *
 *   and display the sorted list of students with their grades. Also print out the average grade.        *
 *   Your output should look something like:                                                             *
 *                                                                                                       *
 * Dave Grohl: 95                                                                                        *
 * Chris Shiflett: 90                                                                                    *
 * Rami Jaffee: 85                                                                                       *
 * Nate Mendel: 80                                                                                       *
 * Taylor Hawkins: 75                                                                                    *
 * Pat Smear: 70                                                                                         *
 *                                                                                                       *
 * Average: 82                                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Class of Student
class Student
{
private:
	string firstName;
	string lastName;
	int grade;

public:

	// Constructor
	Student(string f, string l, int g)
	{
		firstName = f;
		lastName = l;
		grade = g;
	}

	// Getter for first name
	string GetFirst() {
		return firstName;
	}

	// Getter for last name
	string GetLast() {
		return lastName;
	}

	// Getter for grade
	int GetGrade() {
		return grade;
	}

	// Function to output student info
	void studentInfo()
	{
		cout << this->firstName << " " << this->lastName << " " << this->grade << endl;
	}

};

int main()
{
	// Create a vector of students (a list or an array of students)
	vector<string> students;

	// Opens and reads the file
	ifstream studentsFile("example.txt");

	// The current ine of each string in the file
	string currentLine;

	// Variables
	int numStudents = 0;
	int average = 0;
	int total = 0;

	// If the file is open
	if (studentsFile.is_open())
	{

		// Step through each line at least once while the file is open
		while (getline(studentsFile, currentLine))
		{
			// Variables for student data
			string firstName;
			string lastName;
			int grade;

			// Adds each line to the vector of students
			students.push_back(currentLine);

			// Adds 1 to the total number of students per iteration
			numStudents += 1;

			// Finds the first space
			size_t firstSpace = currentLine.find(" ");
			// Sets the first name
			firstName = (currentLine.substr(0, firstSpace));
			// Removes the first name after setting it
			currentLine.erase(0, firstSpace + 1);

			// Confirmation
			cout << firstName << " ";

			// Finds the second space
			size_t secondSpace = currentLine.find(" ");
			// Sets the last name
			lastName = (currentLine.substr(0, secondSpace));
			// Removes the last name after setting it
			currentLine.erase(0, secondSpace + 1);

			// Confirmation
			cout << lastName << " ";

			// Converts the remainder of the string to an int and sets to grade
			grade = (stoi(currentLine));

			// Confirmation
			cout << grade << endl;

			total += grade;
		};

		// Closes the file
		studentsFile.close();
	}
	// Validation if the file cannot be opened
	else
	{
		cout << "Unable to open the student's files." << endl;
	}

	// Display Output
	cout << endl << "Sorting from highest grade to lowest grade." << endl << endl;

	// Variables
	//int temp;

	// Sorting
	for (int i = 0; i < students.size(); i++)
	{
		for (int j = 0; j < students.size(); j++)
		{
			if (students[i] > students[j])
			{
				string temp = students[j];
				students[j] = students[i];
				students[i] = temp;
			}
		}
	}
	
	for (int i = 0; i < students.size(); i++) {
		cout << students[i] << endl;
	}
	
	// Average Formula
	average = total / numStudents;

	// Display Average Output
	cout << endl;
	cout << "Numer of Students: " << numStudents << endl;
	cout << "Grade Average: " << average << endl;
	
	return(0);
}


// This version works, but I don't feel right submitting it, as it's not 100% my doing.

/*
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Class of Student
class Student
{
private:
	string firstName;
	string lastName;
	int grade;

public:

	// Constructor
	Student(string f, string l, int g) : firstName(f), lastName(l), grade(g) {}

	// Getter for first name
	string GetFirst() {
		return firstName;
	}

	// Getter for last name
	string GetLast() {
		return lastName;
	}

	// Getter for grade
	int GetGrade() {
		return grade;
	}

};

// Custom comparison function for sorting students by grade from highest to lowest
bool CompareStudentsByGrade(Student& a, Student& b) {
	return a.GetGrade() > b.GetGrade();
}

int main()
{
	// Create a vector of students (a list or an array of students)
	vector<Student> students;

	// Opens and reads the file
	ifstream studentsFile("example.txt");

	// The current ine of each string in the file
	string currentLine;

	// Variables
	int numStudents = 0;
	int average = 0;
	int total = 0;

	// If the file is open
	if (studentsFile.is_open())
	{

		// Step through each line at least once while the file is open
		while (getline(studentsFile, currentLine))
		{
			// Variables for student data
			string firstName;
			string lastName;
			int grade;

			// Finds the first space
			size_t firstSpace = currentLine.find(" ");
			// Sets the first name
			firstName = currentLine.substr(0, firstSpace);
			// Removes the first name after setting it
			currentLine.erase(0, firstSpace + 1);

			// Finds the second space
			size_t secondSpace = currentLine.find(" ");
			// Sets the last name
			lastName = currentLine.substr(0, secondSpace);
			// Removes the last name after setting it
			currentLine.erase(0, secondSpace + 1);

			// Converts the remainder of the string to an int and sets to grade
			grade = stoi(currentLine);

			// Create a Student object and add it to the vector
			students.emplace_back(firstName, lastName, grade);

			// Increment the total and number of students
			total += grade;
			numStudents++;
		};

		// Closes the file
		studentsFile.close();
	}
	// Validation if the file cannot be opened
	else
	{
		cout << "Unable to open the student's files." << endl;
	}

	// Sort the vector of students by grade in descending order using bubble sort
	sort(students.begin(), students.end(), CompareStudentsByGrade);

	// Output each student's information
	for (Student& student : students)
	{
		cout << student.GetFirst() << " " << student.GetLast() << " " << student.GetGrade() << endl;
	}

	// Average Formula
	average = total / numStudents;

	// Display Average Output
	cout << endl;
	cout << "Numer of Students: " << numStudents << endl;
	cout << "Grade Average: " << average << endl;

	return(0);
}
*/