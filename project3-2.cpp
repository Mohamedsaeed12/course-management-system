/*
name == mohamed saeed
date == 4/15/2022
purpose == course maker with files

*/


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm> //used for tranform function which captilizes everything in the string

using namespace std;

struct CourseInfo {  //structure to store each course added
	int courseID;
	string courseName;
	string courseCode;
	string term;
	int courseSections[3];
};


int loadCourseInfo(CourseInfo student[]);
int addCourseInfo(int, CourseInfo student[]);
void displayCourseInfo(int, CourseInfo student[]);
void searchCourseInfo(int, CourseInfo student[]);
void saveCourseInfo(int, CourseInfo student[]);

int main() {
	int selection; //used for the selection of the menu
	int check1;  //used to correct the selection
	CourseInfo student[100];  //stores every input of each course
	int i = loadCourseInfo(student);




	do {
		cout << "Course Management System " << endl;    //menu for this program
		cout << "------------------------" << endl;
		cout << "1. Add a new course" << endl;
		cout << "2. Search for a course" << endl;
		cout << "3. Display course information" << endl;
		cout << "4. Save course information" << endl;
		cout << "5. Exit" << endl;
		cout << "Please enter a selection:";

		do {        //do while to get the selection from the menu
			check1 = 1;
			cin >> selection;
			cin.clear();
			cin.ignore();

			if (isdigit(selection) || selection > 5 || selection < 1) {
				cout << "error wrong input" << endl;
				cout << "Please enter a selection:";
				check1 = 0;
			}

		} while (check1 == 0);


		if (selection == 1) {  //if the user picks 1 it would add a course undeer the condition that it doesnt already exist and that the sections are not the same
			i = addCourseInfo(i, student); //returns i to know how much courses there are

		}


		if (selection == 2) {  //searches through courses depending on course name(1), course code(2), or term(3)
			searchCourseInfo(i, student);
		}


		if (selection == 3) {  //displays every course added already
			displayCourseInfo(i, student);
		}


		if (selection == 4) {     //saves updated infomation back into file
			saveCourseInfo(i, student);
		}

		if (selection == 5) {     //exit the program but asks if the user wants to save the information
			int saveSelection;
			do {
				cout << "do you want to save yes(1) or no(2)? ";
				cin >> saveSelection;
				if (saveSelection == 1) {
					displayCourseInfo(i, student);
				}
				else if (saveSelection == 2) {

				}
				else {
					cout << "error wrong input" << endl;
				}
			} while (saveSelection != 1 && saveSelection != 0);
		}
	} while (selection != 5);


}



int loadCourseInfo(CourseInfo extract[]) {  //opens file, extracts the information from the file and stores it in the array of courseInfo
											//everthing gets printed at the end



	string str1, str2;   //useed to getline from file and store them in each student array
	ifstream infile("courseInfo.txt"); //opens and input file called courseInfo.txt
	if (!infile) {  //check whether the file is open or not
		cout << "Unable to open file!";
		return 1;
	}

	int i = 0; //each course added is assoited with a number from variable i


	while (!infile.eof()) {  //gets the input file opened and takes each thing stored up to each comma and stores it in student array
		extract[i].courseID = i + 1;
		getline(infile, extract[i].courseName, ',');
		transform(extract[i].courseName.begin(), extract[i].courseName.end(), extract[i].courseName.begin(), toupper);
		getline(infile, str1, ',');
		getline(infile, str2, ',');
		extract[i].courseCode = str1 + "-" + str2;
		getline(infile, str1, ',');
		extract[i].courseSections[0] = stoi(str1);
		getline(infile, str2, ',');
		extract[i].courseSections[1] = stoi(str2);
		getline(infile, str1, ',');
		extract[i].courseSections[2] = stoi(str1);
		getline(infile, str1, ',');
		getline(infile, str2, '\n');
		extract[i].term = str1 + str2;

		cout << extract[i].courseID << ", " << extract[i].courseName << ", " << extract[i].courseCode << ", " << extract[i].courseSections[0] << ", " << extract[i].courseSections[1] << ", " << extract[i].courseSections[2] << ", " << extract[i].term << endl; //prints everything stored
		i++;
	}
	cout << endl;

	infile.close();
	return i;
}



int addCourseInfo(int j, CourseInfo student[]) { //used to add course only under the condition that it doesnt already exist and all sections are different


	string courseName, subject, courseNumber, semester, year, section[3];//temp store for added information 
	

	//get the information from the user for a new course
	cout << "enter course name: ";
	getline(cin, courseName);
	transform(courseName.begin(), courseName.end(), courseName.begin(), toupper);
	cout << "Enter subject code (format xxxx): ";
	getline(cin, subject);
	transform(subject.begin(), subject.end(), subject.begin(), toupper);
	cout << "Enter course number (format xxxx): ";
	getline(cin, courseNumber);
	cout << "Enter semester (S, F or W): ";
	getline(cin, semester);
	transform(semester.begin(), semester.end(), semester.begin(), toupper);
	cout << "Enter year (format yyyy): ";
	getline(cin, year);
	cout << "Enter section code 1: ";
	getline(cin, section[0]);
	cout << "Enter section code 2(if none put 0): ";
	getline(cin, section[1]);
	cout << "Enter section code 3(if none put 0): ";
	getline(cin, section[2]);


	string courseCode = subject + "-" + courseNumber;
	string term = semester + year;
	int verfitor = 0; //used to verify the test worked
	for (int k = 0; k < j; k++) {

		if (!courseCode.compare(student[k].courseCode) || section[0] == section[1] || section[1] == section[2] || section[2] == section[0]) {  //compares the temp course with every course that exist and checks wheter the course already exist
			if (!term.compare(student[k].term)) {  //prints if the coursecode and term are already being used
				cout << "error class already exists: " << endl;
			}
			else if (section[1] == "0" && section[2] == "0") { //used for none entery course
				verfitor = 1;
			}
			else if (section[0] == section[1] || section[1] == section[2] || section[2] == section[0]) { //if two or more sections exist that are the same
				k = j;
				cout << "error same number for sections" << endl;
			}
		}
		else {

			verfitor = 1;  //if everything passes the test
		}
	}
	if (verfitor == 1) { //adds the temp course to the CourseInfo student courses (main courses)
		student[j].courseID = j + 1;
		student[j].courseName = courseName;
		student[j].courseCode = courseCode;
		student[j].courseSections[0] = stoi(section[0]);
		student[j].courseSections[1] = stoi(section[1]);
		student[j].courseSections[2] = stoi(section[2]);
		student[j].term = term;
		j++;
	}
	return j;

}

void displayCourseInfo(int f, CourseInfo student[]) { //displays everything in the student array so the user can see what it has added
	cout << "ID Name Code Term Sections\n-----------------------------------------------\n";
	for (int j = 0; j < f; j++) {
		cout << student[j].courseID << ", " << student[j].courseName << ", " << student[j].courseCode << ", " << student[j].courseSections[0] << ", " << student[j].courseSections[1] << ", " << student[j].courseSections[2] << ", " << student[j].term << endl;
	}
	cout << endl;
}



void saveCourseInfo(int j, CourseInfo student[]) { //saves course back into the same file "courseInfo.txt"
	fstream outfile("courseInfo.txt", ios::out);
	cout << j << endl;
	for (int h = 0; h < j; h++) {
		if (h < j - 1)
			outfile << student[h].courseID << ", " << student[h].courseName << ", " << student[h].courseCode << ", " << student[h].courseSections[0] << ", " << student[h].courseSections[1] << ", " << student[h].courseSections[2] << ", " << student[h].term << endl;
		else
			outfile << student[h].courseID << ", " << student[h].courseName << ", " << student[h].courseCode << ", " << student[h].courseSections[0] << ", " << student[h].courseSections[1] << ", " << student[h].courseSections[2] << ", " << student[h].term;
	}
	outfile.close();
}


void searchCourseInfo(int j, CourseInfo student[]) {  //searches for courses that exist based on coursename, coursecode, or term
	int search;
	cout << " Do you want to search by course name(1), course code(2), or term(3) ? ";
	cin >> search;
	if (search == 1) {  //if the used wants to search by coursename
		string searchCourseName; 
		cin.ignore();
		cout << "Enter course name:";
		getline(cin, searchCourseName);  //course name user wants to see
		transform(searchCourseName.begin(), searchCourseName.end(), searchCourseName.begin(), toupper);
		cout << "ID Name Code Term Sections\n-----------------------------------------------\n";

		for (int h = 0; h < j; h++) { //compares every name in the array to the course name user wants to search for

			if (searchCourseName == student[h].courseName) {
				cout << student[h].courseID << ", " << student[h].courseName << ", " << student[h].courseCode << ", " << student[h].courseSections[0] << ", " << student[h].courseSections[1] << ", " << student[h].courseSections[2] << ", " << student[h].term << endl;
			}

		}
		cout << endl;

	}
	if (search == 2) { //search for course that have the same course code
		string searchSubject;
		string searchNumber;
		string searchCourseCode;
		cout << "Enter subject code (format xxxx):";
		cin >> searchSubject;  //coursecode user wants to see
		transform(searchSubject.begin(), searchSubject.end(), searchSubject.begin(), toupper);
		cout << "Enter course number (format xxxx):";
		cin >> searchNumber;
		searchCourseCode = searchSubject + "-" + searchNumber;
		cout << "ID Name Code Term Sections\n-----------------------------------------------\n";
		for (int h = 0; h < j; h++) {//compares every code in the array to the course code user wants to search for

			if (searchCourseCode == student[h].courseCode) {
				cout << student[h].courseID << ", " << student[h].courseName << ", " << student[h].courseCode << ", " << student[h].courseSections[0] << ", " << student[h].courseSections[1] << ", " << student[h].courseSections[2] << ", " << student[h].term << endl;
			}

		}
		cout << endl;
	}
	if (search == 3) {//searches all existing course with the same course term
		string searchSemester;
		string searchYear;
		string searchTerm;
		cout << " Enter semester (S, F or W):";
		cin >> searchSemester;
		transform(searchSemester.begin(), searchSemester.end(), searchSemester.begin(), toupper);
		cout << "Enter year (format yyyy): ";
		cin >> searchYear;
		searchTerm = searchSemester + searchYear;  //term user wants to see
		cout << "ID Name Code Term Sections\n-----------------------------------------------\n";
		for (int h = 0; h < j; h++) {

			if (searchTerm == student[h].term) {//compares every term in the array to the course term user wants to search for
				cout << student[h].courseID << ", " << student[h].courseName << ", " << student[h].courseCode << ", " << student[h].courseSections[0] << ", " << student[h].courseSections[1] << ", " << student[h].courseSections[2] << ", " << student[h].term << endl;

			}
		}
		cout << endl;
	}
}