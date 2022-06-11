#include <iostream>
#include <memory>
#include <ctime>

int convertMonthInt(const std::string& month)
{
    if (month == "January")
        return 1;
    if (month == "February")
        return 2;
    if (month == "March")
        return 3;
    if (month == "April")
        return 4;
    if (month == "May")
        return 5;
    if (month == "June")
        return 6;
    if (month == "July")
        return 7;
    if (month == "August")
        return 8;
    if (month == "September")
        return 9;
    if (month == "October")
        return 10;
    if (month == "November")
        return 11;
    if (month == "December")
        return 12;
    else
        return 0;
}

std::string convertMonthInt(const int& month)
{
    switch (month)
    {
    case(0):
        return "January";
    case(1):
        return "February";
    case(2):
        return "March";
    case(3):
        return "April";
    case(4):
        return "May";
    case(5):
        return "June";
    case(6):
        return "July";
    case(7):
        return "August";
    case(8):
        return "September";
    case(9):
        return "October";
    case(10):
        return "November";
    case(11):
        return "December";
    default:
        return "UNDEFINED";
    }
}

//=============================================================================================================================
//Task 1. Date and today smart pointers
//=============================================================================================================================

class Date
{
private:
    int m_day{0};
    std::string m_month{"UNDEFINED"};
    int m_year{0};
public:
    Date(int day, std::string month, int year) : m_day(day), m_month(month), m_year(year) {};
    Date() {};
    ~Date() {};
    void setDay(int day) { m_day = day; };
    void setMonth(std::string month) { m_month = month; };
    void setYear(int year) { m_year = year; };
    void setDate(int day, std::string month, int year) { setDay(day); setMonth(month); setYear(year); };

    int getDay() const { return m_day; };
    std::string getMonth() const { return m_month; };
    int getYear() const { return m_year; };

    friend std::ostream& operator<<(std::ostream& out, const Date& date);

    void operator=(Date date2)
    {
        this->setDate(date2.getDay(), date2.getMonth(), date2.getYear());
    }
};

std::ostream& operator<<(std::ostream& out, const Date& date) 
{
    out << date.getDay() << " " << date.getMonth() << " " << date.getYear();
    return out;
};


//=============================================================================================================================
//Task 2. date1 and date 2 smart pointers
//=============================================================================================================================

std::shared_ptr<Date> compareDates(std::shared_ptr<Date> date1, std::shared_ptr<Date> date2)
{
    if (date1->getYear() > date2->getYear())
        return date1;
    else if (date1->getYear() != date2->getYear())
        return date2;

    int m1 = convertMonthInt(date1->getMonth());
    int m2 = convertMonthInt(date2->getMonth());
    if (m1 > m2)
        return date1;
    else if (m1 != m2)
        return date2;

    if (date1->getDay() > date2->getDay())
        return date1;
    else if (date1->getDay() != date2->getDay())
        return date2;
    return nullptr;
}

void swapDates(std::shared_ptr<Date> date1, std::shared_ptr<Date> date2)
{
    std::shared_ptr<Date> temp(new Date(date1->getDay(), date1->getMonth(), date1->getYear()));
    *date1 = *date2;
    *date2 = *temp;
    return;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    //Getting date data for task 1
    time_t now = time(0);
    tm* lct = localtime(&now);
    std::string month = convertMonthInt(lct->tm_mon);

    //=============================================================================================================================
    //Task 1. Date and today smart pointers
    //=============================================================================================================================

    std::shared_ptr<Date> today(new Date);
    std::shared_ptr<Date> date(new Date);
    today->setDay(lct->tm_mday);
    today->setMonth(month);
    today->setYear((1900 + lct->tm_year));

    std::cout << *today << std::endl;
    date = today;
    today.reset();

    if (date.get() == nullptr)
        std::cout << "date smart pointer is null" << std::endl;
    else
        std::cout << "date smart pointer is not null" << std::endl;

    if (today.get() == nullptr)
        std::cout << "today smart pointer is null" << std::endl;
    else
        std::cout << "today smart pointer is not null" << std::endl;
        
    std::cout << "Task 2" << std::endl;
    auto date1 = std::make_shared<Date>(1, "January", 2021);
    auto date2 = std::make_shared<Date>(13, "November", 2021);

    std::cout << "The latest date of two is: " << *(compareDates(date1, date2)) << std::endl;

    std::cout << "Date 1 before swap: " << *date1 << std::endl;
    std::cout << "Date 2 before swap: " << *date2 << std::endl;
    swapDates(date1, date2);
    std::cout << "Date 1 after swap: " << *date1 << std::endl;
    std::cout << "Date 2 after swap: " << *date2 << std::endl;
    return 0;
}
