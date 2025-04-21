#include "appointment.h"
#include <sstream>
#include <iomanip>
#include <cctype>

Appointment::Appointment(){
    title = "N/A";
    year = 1;
    month = 1;
    day = 1;
    time = 0;
    duration = 1;
}
Appointment::Appointment(string appData){
    size_t start = 0;
    while (start < appData.size() && appData[start] == ' ') {
        ++start;
    }
    size_t end = appData.size();
    while (end > start && appData[end - 1] == ' ') {
        --end;
    }
    appData = appData.substr(start, end - start);
    size_t pos = 0;
    for (int i = 0; i < 5; ++i) {
        size_t next = appData.find('|', pos);
        string part = appData.substr(pos, next - pos);
        part.erase(0, part.find_first_not_of(" \t"));
        part.erase(part.find_last_not_of(" \t") + 1);

        switch(i) {
            case 0: title = part; break;
            case 1: year = stoi(part); break;
            case 2: month = stoi(part); break;
            case 3: day = stoi(part); break;
            case 4: time = standardToMilitary(part); break;
        }
        pos = next + 1;
    }
    duration = stoi(appData.substr(pos));
}

string Appointment::getTitle() {
    return title;
}
int Appointment::getYear(){
    return year;
}
int Appointment::getMonth(){
    return month;
}
int Appointment::getDay(){
    return day;
}
int Appointment::getTime() {
    return time;
}
int Appointment::getDuration(){
    return duration;
}
string Appointment::getDate(){
    ostringstream oss;
    oss << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << day;
    return oss.str();
}
string Appointment::getStandardTime(){
    return militaryToStandard(time);
}
void Appointment::setTitle(string newTitle){
    title = newTitle;
}
void Appointment::setYear(int newYear){
    if(newYear > 0) {
        year = newYear;
    }
}
void Appointment::setMonth(int newMonth){
    if(newMonth >= 1 && newMonth <= 12){
        month = newMonth;
    }
}
void Appointment::setDay(int newDay){
    if(newDay >= 1 && newDay <= 31){
        day = newDay;
    }
}
void Appointment::setTime(int newTime){
    if(newTime >= 0 && newTime <= 2359){
        time = newTime;
    }
}
void Appointment::setDuration(int newDuration){
    if(newDuration > 0){
        duration = newDuration;
    }
}
void Appointment::setDate(int newYear, int newMonth, int newDay){
    setYear(newYear);
    setMonth(newMonth);
    setDay(newDay);
}

string Appointment::militaryToStandard(int time){
    int hour = time / 100;
    int minute = time % 100;
    string period = (hour >= 12) ? "PM" : "AM";
    if (hour > 12) hour -= 12;
    if (hour == 0) hour = 12;

    ostringstream outstring;
    outstring << hour << ":" << setw(2) << setfill('0') << minute << period;
    return outstring.str();
}

int Appointment::standardToMilitary(string time) {
    size_t colon = time.find(":");
    int hour = stoi(time.substr(0, colon));
    int minute = stoi(time.substr(colon + 1, 2));
    string period;
    for (size_t i = 0; i < time.size() - 1; ++i) {
        char c = time[i];
        if ((c == 'A' || c == 'a' || c == 'P' || c == 'p') &&
            (time[i + 1] == 'M' || time[i + 1] == 'm')) {
            period = time.substr(i, 2);
            break;
        }
        if (period == "PM" || period == "pm") {
            if (hour != 12) hour += 12;
        } else if (hour == 12) hour = 0;

        return hour * 100 + minute;
    }
}