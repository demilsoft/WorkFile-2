/**
 *   @file: appointment_main.cc
 *   @author: Matthew Lewis
 *   @date: 4/23/2025
 *   @brief: This program uses seprate compilation to combine multiple files to prompt the user with a year, month, day, time, duration and
 *   asks for a name of the name of the appointment. We added functionality to create, view and delete stored appointments.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "appointment.h"


// Function Declarations
void addAppt();
void printDaily();
void findTime(string miltimeout);
string toUpper(const string& s);
string removeSpaces(const string& s);
string trimSpaces(const string& s);
int findDelimitPos(const std::string& str, char ch, int n);
void deleteRowByTime(string miltimeout);
void deleteRowByTitle(string stringtomatch);

using namespace std;

int main(int argc, char const *argv[]) {

    // Check for correct number of arguments
    if (argc == 2) {
        // Get Command Argument
        string arg1 = argv[1];
        // Include Appointment Class
        Appointment a1;
        int miltimein;
        string titlename, miltimeout;

        /* Check for valid input arguments */
        if (arg1 == "-a") {
            /* -a   add appointment */;
            addAppt();
        } else if (arg1 == "-ps") {
            printDaily();
        } else if (arg1 == "-p") {
            /* -p   search military time */;
            cout << "Enter military time to search: " << endl;
            cin >> miltimein;
            miltimeout = a1.militaryToStandard(miltimein);
            findTime(miltimeout);
        } else if (arg1 == "-dt") {
            /* -dt   delete by title */;
            cout << "Enter title to search: " << endl;
            cin >> titlename;
            deleteRowByTitle(titlename);
        } else if (arg1 == "-dm") {
            /* -dm   delete by military time */;
            cout << "Enter military time to search: " << endl;
            cin >> miltimein;
            miltimeout = a1.militaryToStandard(miltimein);
            deleteRowByTime(miltimeout);
        } else {
            cout << "You entered an invalid argument." << endl;
        }
    }
    else {
        cout << "You entered an invalid number of arguments." << endl;
    }
    return 0;
}

void addAppt() {
    Appointment a1;

    string title, timeStr, inputline;
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

    cout << "\nAdding Your Appointment:" << endl;
    cout << a1.getTitle() << " on " << a1.getDate() << " at " << a1.getStandardTime() << ", duration: " << a1.getDuration() << " mins\n";

    inputline = a1.getTitle() + '|' + std::to_string(a1.getYear()) + '|' + std::to_string(a1.getMonth()) + '|' + std::to_string(a1.getDay()) + '|' + a1.getStandardTime() + '|' + std::to_string(a1.getDuration());
    //cout << inputline << endl;

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
            if (line != "") { // Clears out empty lines from file
                // Check Duplicate Title Here
                // Call Function to check and return true/false
                // If false, reset and do not add new record. Print to screen duplicate name
                int endpos = 0;
                string linetitle;
                endpos = findDelimitPos(line, '|', 1);
                linetitle = line.substr(0, endpos);
                // Test if title are equal in class
                Appointment currtitle ( trimSpaces(toUpper(linetitle)), 0);
                Appointment newtitle (trimSpaces(toUpper(title)), 0);
                if (currtitle == newtitle)
                    cout<<"Using == overloading operator found Appointment Title Match. Appointment was added."<<endl;

                //tempFile << trimSpaces(toUpper(line)) << std::endl; //add existing lines to new file and formats text
                tempFile << trimSpaces(line) << std::endl; //add existing lines to new file and formats text
            }
        }
        // Write new line at end of file
        //tempFile << trimSpaces(toUpper(inputline)) << std::endl;
        tempFile << trimSpaces(inputline) << std::endl;

    file.close();
    tempFile.close();

    // Replace original file with the temporary file
    std::remove("agenda_old.txt");
    std::rename("agenda.txt", "agenda_old.txt");
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
    else {
        std::string line;

        std::cout << std::setw(35) << "Appointment Title"
                  << std::setw(12) << "Year"
                  << std::setw(12) << "Month"
                  << std::setw(12) << "Day"
                  << std::setw(12) << "Time"
                  << std::setw(15) << "Duration"
                  << std::endl;

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
                            std::vector<std::string> parts;
                            size_t start = 0;

                            for (size_t i = 0; i <= line.length(); ++i) {
                                if (i == line.length() || line[i] == '|') {
                                    std::string part = line.substr(start, i - start);
                                    parts.push_back(part);
                                    start = i + 1;
                                }
                            }
                            parts[4] = to_string(a1.standardToMilitary(parts[4]));

                            // Pads 0 when only 3 digits
                            if (parts[4].size() == 3) {
                                parts[4] = "0" + parts[4];
                            }

                            //std::sort(parts.begin(), parts.end());

                            std::string title = parts[0];
                            int year = std::stoi(parts[1]);
                            int month = std::stoi(parts[2]);
                            int day = std::stoi(parts[3]);
                            std::string time = parts[4] ;
                            int duration = std::stoi(parts[5]);

                            std::cout << std::setw(35) << title
                                      << std::setw(12) << std::to_string(year)
                                      << std::setw(12) << std::to_string(month)
                                      << std::setw(12) << std::to_string(day)
                                      << std::setw(12) << time
                                      << std::setw(15) << duration
                                      << std::endl;

                        }
                    }
                 }
             }
        }
        file.close();   // Close the file
    }
}

void findTime(string miltimeout) {
    std::ifstream file("agenda.txt");   // Open the file
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }
    else {
        std::string line;
        while (std::getline(file, line)) {    // Read lines until end of file
            string linetest = line;

            linetest = toUpper(linetest);
            int pos = linetest.find(miltimeout);
            if (pos != string::npos) {
                std::vector<std::string> parts;
                size_t start = 0;

                for (size_t i = 0; i <= line.length(); ++i) {
                    if (i == line.length() || line[i] == '|') {
                        std::string part = line.substr(start, i - start);
                        parts.push_back(part);
                        start = i + 1;
                    }
                }
                std::string title = parts[0];
                int year = std::stoi(parts[1]);
                int month = std::stoi(parts[2]);
                int day = std::stoi(parts[3]);
                std::string time = parts[4];
                int duration = std::stoi(parts[5]);

                cout << "Title: " << title << endl;
                cout << "Year: " << year << endl;
                cout << "Month: " << month << endl;
                cout << "Day: " << day << endl;
                cout << "Time: " << time << endl;
                cout << "Duration: " << duration << " minutes" << endl;
            }
            else {
                linetest = removeSpaces(linetest);
                pos = linetest.find(miltimeout);
                if (pos != string::npos){
                    std::vector<std::string> parts;
                    size_t start = 0;

                    for (size_t i = 0; i <= line.length(); ++i) {
                        if (i == line.length() || line[i] == '|') {
                            std::string part = line.substr(start, i - start);
                            parts.push_back(part);
                            start = i + 1;
                        }
                    }
                    std::string title = parts[0];
                    int year = std::stoi(parts[1]);
                    int month = std::stoi(parts[2]);
                    int day = std::stoi(parts[3]);
                    std::string time = parts[4];
                    int duration = std::stoi(parts[5]);

                    cout << "Title: " << title << endl;
                    cout << "Year: " << year << endl;
                    cout << "Month: " << month << endl;
                    cout << "Day: " << day << endl;
                    cout << "Time: " << time << endl;
                    cout << "Duration: " << duration << " minutes" << endl;
                }
            }
        }
        file.close();   // Close the file
    }
}

void deleteRowByTitle(string stringtomatch) {
    std::ifstream file("agenda.txt");
    std::ofstream tempFile("temp.txt");  // Creates new temp file to store appointments
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }
    else {
        // Match input string to delete. If no match is found the row is copied to temp file to replace original file
        while (std::getline(file, line)) {    // Read lines until end of file
            int pos = toUpper(line).find(toUpper(stringtomatch));
            if (pos == string::npos && line != "") {
                tempFile << line << std::endl;
            }
            else if (pos > -1)
            {
                cout << "\nRow Deleted:   " << toUpper(line) << endl;
            }
        }
        file.close();        tempFile.close();

        // Replace original file with the temporary file
        std::remove("agenda_old.txt");
        std::rename("agenda.txt", "agenda_old.txt");
        std::rename("temp.txt", "agenda.txt");
    }
}

void deleteRowByTime(string miltimeout) {
    std::ifstream file("agenda.txt");
    std::ofstream tempFile("temp.txt");  // Creates new temp file to store appointments
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;   //Return error if cannot open
    }
    else {
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
                else if (pos > 0)
                {
                    cout << "\nRow Deleted:   " << linetest << endl;
                }
            }
            else if (pos > 0)
            {
                cout << "\nRow Deleted:   " << linetest << endl;
            }
        }
        file.close();
        tempFile.close();

        // Replace original file with the temporary file
        std::remove("agenda_old.txt");
        std::rename("agenda.txt", "agenda_old.txt");
        std::rename("temp.txt", "agenda.txt");
    }
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
