#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure to hold courses info
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};


string toUpper(const string& str) {
    string upperStr = str;
    for (char& c : upperStr) c = toupper(c);
    return upperStr;
}

// Print course info 
void printCourse(const Course& course) {
    cout << course.courseNumber << ", " << course.courseName << endl;
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i != course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Load courses from file into map
bool loadCourses(const string& filename, map<string, Course>& courses) {
    ifstream file(filename);
    if (!file) {
        cout << "Error, file could not open." << endl;
        return false;
    }

    courses.clear();

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) continue;

        Course c;
        c.courseNumber = toUpper(tokens[0]);
        c.courseName = tokens[1];

        for (size_t i = 2; i < tokens.size(); i++) {
            c.prerequisites.push_back(toUpper(tokens[i]));
        }

        courses[c.courseNumber] = c;
    }
    file.close();
    cout << "Courses loaded successfully." << endl;
    return true;
}

// Print all courses sorted alphanumerically by course number
void printCourseList(const map<string, Course>& courses) {
    cout << "Here is a sample schedule:" << endl;

    // Extract keys and sort them
    vector<string> keys;
    for (const auto& p : courses) keys.push_back(p.first);
    sort(keys.begin(), keys.end());

    for (const string& key : keys) {
        cout << courses.at(key).courseNumber << ", " << courses.at(key).courseName << endl;
    }
}

int main() {
    map<string, Course> courses;
    bool dataLoaded = false;
    int option;

    cout << "Welcome to the course planner XD" << endl;

    do {
        cout << "\n1. to load file, enter the filename(put .csv at end)." << endl;//it will ask file name because file isnt hard coded, file name plus .csv
        cout << "2. Print the course List in order." << endl;//an example is ABCU.csv for a csv filename ABCU
        cout << "3. Print a courses info." << endl;
        cout << "9. Exit" << endl;
        cout << "Input a number to navigate ";

        if (!(cin >> option)) {
            // Handle incorrect inputs
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input,Please enter a number from the menu." << endl;
            continue;
        }

        switch (option) {
        case 1: {//the main issue was the csv file reading
            cout << "Enter file name: ";//include .csv at end
            string filename;
            cin >> filename;
            dataLoaded = loadCourses(filename, courses);
            break;
        }
        case 2:
            if (!dataLoaded) {
                cout << "Please load data." << endl;
            }
            else {
                printCourseList(courses);
            }
            break;
        case 3:
            if (!dataLoaded) {
                cout << "Please load data " << endl;//make sure to load data so it can read the file
            }
            else {
                cout << "What course do you want to know more about? ";
                string courseNum;
                cin >> courseNum;
                courseNum = toUpper(courseNum);
                if (courses.find(courseNum) != courses.end()) {
                    printCourse(courses[courseNum]);
                }
                else {
                    cout << "Course not found, try again" << endl;//error message
                }
            }
            break;
        case 9:
            cout << "Good-bye!" << endl;
            break;
        default:
            cout << option << " is not a valid option." << endl;
            break;
        }
    } while (option != 9);

    return 0;
}
//justine kummer
//cs-300 poject 2
