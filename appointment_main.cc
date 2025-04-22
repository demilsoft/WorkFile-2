/**
 *   @file: appointment_main.cc
 *   @author: Matthew Lewis
 *   @date: 4/17/2025
 *   @brief: This program uses seprate compilation to combine multiple files to prompt the user with a year, month, day, time, duration and asks for a name of the name of the appointment.
 */

/*
 *  1. Open and write appointment at end of file
 *          Format - Cleanup and add header
 *          save (append)
 *  2. Open and print current daily schedule ordered by military time
 *          Search by Year | Month | Day
 *          Sort by time
 *  3. Open and print matching military time
 *          Add header row
 *  4. Open and delete matching title
 *          Delete Record
 *  5. Open and delete matching starting military time
 *          Delete Record
 *
 * Will need a menu 1 = Add new Appt, 2 = Print Daily Schedule, 3 = Print Appts at Time, 4 = Delete Title, 5 = Delete Time
 */
#include <iostream>
#include <fstream>
#include <string>
#include "appointment.h"

// Function declarations
void addAppt();
void printDaily();
void findTime(string miltimeout);
string toUpper(const string& s);
string removeSpaces(const string& s);
string trimSpaces(const string& s);
int findDelimitPos(const std::string& str, char ch, int n);
void deleteRowByTime(string miltimeout);
void deleteRowByTitle(string stringtomatch);
void findTitle(string titlestring);

using namespace std;

int main(int argc, char const *argv[]) {

    // Class declaration
    Appointment a1;
    int menuitem, miltimein;
    bool quit = false;
    string titlename, miltimeout;

    /* While Loop for Menu Items */
    while (!quit) {
        cout << endl << "Menu: (1) Add Appt (2) Daily Sched  (3) Print By Time  (4) Del By Title  (5) Del By Time  (6) Quit : " << endl;
        cin >> menuitem;

        switch (menuitem) {
            case 1: /* add appointment here */;
                addAppt();
                break;
            case 2: /* print daily here */;
                printDaily();
                break;
            case 3: /* print by time here */
                // Complete
                cout << "Enter military time to search: " << endl;
                cin >> miltimein;
                miltimeout = a1.militaryToStandard(miltimein);
                findTime(miltimeout);
                break;
            case 4: /* delete by title  here */;
                // Complete
                cout << "Enter title to search: " << endl;
                cin >> titlename;
                deleteRowByTitle(titlename);
                break;
            case 5: /* delete by time here */;
                //Complete
                cout << "Enter military time to search: " << endl;
                cin >> miltimein;
                miltimeout = a1.militaryToStandard(miltimein);
                deleteRowByTime(miltimeout);
                break;
            case 6: /* quit the program */;
                quit = true;
                break;
        }
    }

    return 0;
}

void addAppt() {
    Appointment a1;

    string title, timeStr, inputline;
    int year, month, day, duration;

    cout << "Enter appointment title: ";
    cin >> title;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month (1-12): ";
    cin >> month;
    cout << "Enter day (1-31): ";
    cin >> day;
    cout << "Enter time (for example: 8:30 AM): ";
    cin.ignore();
    getline(cin, timeStr);
    cout << "Enter duration in minutes: ";
    cin >> duration;

    a1.setTitle(title);
    a1.setYear(year);
    a1.setMonth(month);
    a1.setDay(day);
    a1.setTime(Appointment::standardToMilitary(timeStr));
    a1.setDuration(duration);

    cout << "\nAdding Your Appointment:" << endl;
    cout << a1.getTitle() << " on " << a1.getDate() << " at " << a1.getStandardTime() << ", duration: " << a1.getDuration() << " mins\n";

    inputline = a1.getTitle() + '|' + std::to_string(a1.getYear()) + '|' + std::to_string(a1.getMonth()) + '|' + std::to_string(a1.getDay()) + '|' + a1.getStandardTime() + '|' + std::to_string(a1.getDuration());
    cout << inputline << endl;

    // Open file to add new record
    std::ifstream file("agenda.txt");
    std::ofstream tempFile("temp.txt");  // Creates new temp file to store appointments
    std::string line;

    // Write out lines in tem file to the end.
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }
    else {
        while (std::getline(file, line)) {    // Read lines until end of file
            if (line != "") {
                tempFile << line << std::endl;
            }
        }
        // Write new line
        tempFile << inputline << std::endl;


    file.close();
    tempFile.close();

    // Replace original file with the temporary file
    std::remove("agenda.txt");
    std::rename("temp.txt", "agenda.txt");
    }
}

void printDaily() {

    Appointment a1;
    int year, month, day, pos;

    // Get search day for daily schedule
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month (1-12): ";
    cin >> month;
    cout << "Enter day (1-31): ";
    cin >> day;

    a1.setYear(year);
    a1.setMonth(month);
    a1.setDay(day);

    std::ifstream file("agenda.txt");   // Open the file
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }

    std::string line;
    while (std::getline(file, line)) {    // Read lines until end of file
        line = trimSpaces(line);
        if (line != "") //Skips blank lines
        {
            // Use inputs to find matching year, month day for output
            pos = line.find(std::to_string(a1.getYear()));
            if (pos > 0) {
                pos = line.find(std::to_string(a1.getMonth()));
                if (pos > 0) {
                    pos = line.find(std::to_string(a1.getDay()));
                    if (pos > 0) {
                        // Find position of time in string
                        int startpos = 0;
                        int endpos = 0;
                        int milapptime = 0;

                        // Find delimiter positions for appointment time
                        startpos = findDelimitPos(line, '|', 4);
                        endpos = findDelimitPos(line, '|', 5);
                        //Extract Time from appointment using position
                        std::string appttime = line.substr(startpos + 1, endpos - startpos - 1); // Extract Time
                        //Trim and format time output
                        appttime = trimSpaces(appttime);
                        appttime = toUpper(appttime);
                        //Convert to military time
                        milapptime = a1.standardToMilitary(appttime);

                        std::cout << line << std::endl;
                    }
                }
            }
        }
    }
    file.close();   // Close the file
}

void findTime(string miltimeout) {
    std::ifstream file("agenda.txt");   // Open the file
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }

    std::string line;
    while (std::getline(file, line)) {    // Read lines until end of file
        string linetest = line;

        linetest = toUpper(linetest);
        int pos = linetest.find(miltimeout);
        if (pos != string::npos) {
            std::cout << line << std::endl;
        }
        else {
            linetest = removeSpaces(linetest);
            pos = linetest.find(miltimeout);
            if (pos != string::npos)
                std::cout << line << std::endl;
        }
    }
    file.close();   // Close the file
}

string toUpper(const string& s){
    string result = s;
    for(char& c : result){
        c = toupper(c);
    }
    return result;
}

string removeSpaces(const string& s) {
    std::string str = s;
    std::string result;
    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

string trimSpaces(const string& s) {
    std::string result;
    size_t start = 0;
    while (start < s.size() && s[start] == ' ') {
        ++start;
    }
    size_t end = s.size();
    while (end > start && s[end - 1] == ' ') {
        --end;
    }
    result = s.substr(start, end - start);

    return result;
}

int findDelimitPos(const std::string& str, char ch, int n) {
    int count = 0;
    for (size_t pos = 0; pos < str.length(); ++pos) {
        if (str[pos] == ch) {
            ++count;
            if (count == n) {
                return pos;
            }
        }
    }
    return -1; // Return -1 if the nth instance is not found
}

void deleteRowByTitle(string stringtomatch) {
    std::ifstream file("agenda.txt");
    std::ofstream tempFile("temp.txt");  // Creates new temp file to store appointments
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }

    // Match input string to delete. If no match is found the row is copied to temp file to replace original file
    while (std::getline(file, line)) {    // Read lines until end of file
        int pos = toUpper(line).find(toUpper(stringtomatch));
        if (pos == string::npos && line != "") {
            // Line to delete is found. Call delete.
            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();

    // Replace original file with the temporary file
    std::remove("agenda.txt");
    std::rename("temp.txt", "agenda.txt");
}

void deleteRowByTime(string miltimeout) {
    std::ifstream file("agenda.txt");
    std::ofstream tempFile("temp.txt");  // Creates new temp file to store appointments
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }

    while (std::getline(file, line)) {    // Read lines until end of file
        string linetest = line;

        linetest = toUpper(linetest);
        int pos = linetest.find(miltimeout);
        if (pos == string::npos && linetest != "") {
            linetest = removeSpaces(linetest);
            pos = linetest.find(miltimeout);
            if (pos == string::npos && linetest != "") {
                    tempFile << line << std::endl;
            }
        }
    }
    file.close();
    tempFile.close();

    // Replace original file with the temporary file
    std::remove("agenda.txt");
    std::rename("temp.txt", "agenda.txt");
}

// NOT USED
void findTitle(string titlestring) {
    std::ifstream file("agenda.txt");   // Open the file
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }

    std::string line;
    while (std::getline(file, line)) {    // Read lines until end of file
        int pos = line.find(titlestring);
        if (pos != string::npos)
            // Line to delete is found. Call delete.
            std::cout << line << std::endl;
    }
    file.close();   // Close the file
}