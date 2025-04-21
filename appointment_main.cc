/**
 *   @file: appointment_main.cc
 *   @author: Matthew Lewis
 *   @date: 4/17/2025
 *   @brief: This program uses seprate compilation to combine multiple files to prompt the user with a year, month, day, time, duration and asks for a name of the name of the appointment.
 */

/*
 *  1. Open and write appointment at end of file
 *  2. Open and  delete matching title
 *  3. Open and delete matching starting military time
 *  4. Open and print matching military time
 *  5. Open and print current daily schedule ordered by military time
 *
 * Will need a menu 1 = Add new Appt, 2 = Print Daily Schedule, 3 = Print Appts at Time, 4 = Delete Title, 5 = Delete Time
 */


#include "appointment.h"
#include <iostream>
using namespace std;


int main(int argc, char const *argv[]) {
    //test your class here
    Appointment a1;

    string title, timeStr;
    int menuitem, year, month, day, duration;

    cout << "Enter Selecttion (1) Add Appt   (2) Print Daily Sched   (3) Print By Time   (4) Delete Appt By Title   (5) Delete By Time : ";
    cin >> menuitem;

    switch (menuitem) {
        case 1: /* add appointment here */; break;
        case 2: /* print daily here */; break;
        case 3: /* print by time here */; break;
        case 4: /* delete by title  here */; break;
        case 5: /* delete by time here */; break;
    }

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

    return 0;
}

