#include <string>
using namespace std;

class Appointment {
private:
    string title;
    int year, month, day, time, duration;

public:
    Appointment();
    Appointment(string appData);

    // Class Overload Function to compare titles
    Appointment(string newTitle, int var){
        title = newTitle;
        }
        bool operator == (const Appointment &c){
            if (title == c.title)
                return true;
            return false;
        }

    string getTitle();
    int getYear();
    int getMonth();
    int getDay();
    int getTime();
    int getDuration();
    string getDate();
    string getStandardTime();

    void setTitle(string newTitle);
    void setYear(int newYear);
    void setMonth(int newMonth);
    void setDay(int newDay);
    void setTime(int newTime);
    void setDuration(int newDuration);
    void setDate(int newYear, int newMonth, int newDay);

    static string militaryToStandard(int time);
    static int standardToMilitary(string time);
};
