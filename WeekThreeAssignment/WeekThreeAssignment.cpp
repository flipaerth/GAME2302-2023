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

	// Average Formula
	average = total / numStudents;

	// Display Average Output
	cout << endl;
	cout << "Numer of Students: " << numStudents << endl;
	cout << "Grade Average: " << average << endl;
	
	return(0);
}