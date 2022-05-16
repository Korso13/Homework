#include <iostream>
#include <cmath>

using namespace std;
//============================================================================================================
//Task 1. class Power
//============================================================================================================
class Power
{
    private:
    double _num1;
    double _num2;

    public:
    Power () : _num1(1), _num2(1) {}

    void set()
    {
        cout << "Введите первое вещественное число: ";
        cin >> _num1;
        cout << "Введите второе вещественное число: ";
        cin >> _num2;
        cout << endl;
    }

    void calculate()
    {
        cout << "Результат возведение первого числа в степень второго: " << pow(_num1, _num2) << endl;         
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");


    return 0;
}
