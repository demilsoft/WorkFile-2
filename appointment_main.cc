/**
 *   @file: appointment_main.cc
 *   @author: Matthew Lewis
 *   @date: 4/17/2025
 *   @brief: This program uses seprate compilation to combine multiple files to prompt the user with a year, month, day, time, duration and asks for a name of the name of the appointment.
 */

/*
 *  1. Open and write appointment at end of file
 *  2. Open and delete matching title
 *  3. Open and delete matching starting military time
 *  4. Open and print matching military time
 *  5. Open and print current daily schedule ordered by military time
 *
 * Will need a menu 1 = Add new Appt, 2 = Print Daily Schedule, 3 = Print Appts at Time, 4 = Delete Title, 5 = Delete Time
 */
#include <iostream>
#include <fstream>
#include <string>
#include "appointment.h"

// Function declarations
void add_appt();
void print_daily();
void print_time(string miltimeout);
void find_title(string titlestring);
string toUpper(const string& s);
string removeSpaces(const string& s);
string trimSpaces(const string& s);

using namespace std;

int main(int argc, char const *argv[]) {

    // Class declaration
    Appointment a1;
    int menuitem, miltimein;
    bool quit = false;
    string titlename, miltimeout;

    /* While Loop for Menu Items */
    while (!quit) {
        cout << endl << "Menu: (1) Add Appt (2) Daily Sched  (3) Print By Time  (4) Del Appt By Title  (5) Del By Time  (6) Quit : " << endl;
        cin >> menuitem;

        switch (menuitem) {
            case 1: /* add appointment here */;
                add_appt();
                break;
            case 2: /* print daily here */;
                print_daily();
                break;
            case 3: /* print by time here */
                cout << "Enter military time to search: " << endl;
                cin >> miltimein;
                miltimeout = a1.militaryToStandard(miltimein);
                print_time(miltimeout);
                break;
            case 4: /* delete by title  here */;
                cout << "Enter title to search: " << endl;
                cin >> titlename;
                find_title(titlename);
                break;
            case 5: /* delete by time here */;
                break;
            case 6: /* quit the program */;
                quit = true;
                break;
        }
    }

    return 0;
}

void add_appt() {
    Appointment a1;

    string title, timeStr;
    int year, month, day, duration;

    cout << "Enter appointment title: ";
    getline(cin, title);
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

    cout << "\nYour Appointment:" << endl;
    cout << a1.getTitle() << " on " << a1.getDate() << " at " << a1.getStandardTime() << ", duration: " << a1.getDuration() << " mins\n";
}

void print_daily() {
    std::ifstream file("agenda.txt");   // Open the file
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }

    std::string line;
    while (std::getline(file, line)) {    // Read lines until end of file
        line = trimSpaces(line);
        std::cout << line << std::endl;     // Print each line
    }

    file.close();   // Close the file
}

void find_title(string titlestring) {
    std::ifstream file("agenda.txt");   // Open the file
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }

    std::string line;
    while (std::getline(file, line)) {    // Read lines until end of file
        int pos = line.find(titlestring);
        if (pos != string::npos)
            std::cout << line << std::endl;
    }
    file.close();   // Close the file
}

void print_time(string miltimeout) {
    std::ifstream file("agenda.txt");   // Open the file
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }

    std::string line;
    while (std::getline(file, line)) {    // Read lines until end of file
        string linetest = line;

        linetest = toUpper(linetest);
        int pos = linetest.find(miltimeout);
        if (pos != string::npos)
            std::cout << line << std::endl;
        else
            linetest = removeSpaces(linetest);
            pos = linetest.find(miltimeout);
            if (pos != string::npos)
                std::cout << line << std::endl;
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