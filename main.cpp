#include <iostream>
#include <windows.h>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "randDouble.hpp"
#include <iomanip>

using namespace std;

//=============================================================================================================================
//Task 1. Insert sorted (and its template)
//=============================================================================================================================

bool insert_sorted(vector<int>& _vector, int _new_value)
{
    if (_new_value < _vector[0])
    {
        _vector.insert(_vector.begin(), _new_value);
        return true;
    }
    else
        if (_new_value > _vector[_vector.size() - 1])
        {
            _vector.push_back(_new_value);
            return true;
        }
        else
        {
            auto it = lower_bound(_vector.begin(), _vector.end(), _new_value);
            if (it != _vector.end())
            {
                _vector.insert(it, _new_value);
                return true;
            }
            else
                return false; //Не знаю как до такого может дойти, но на всякий
        }
}

template <class Container, class T = class Container::value_type> 
bool insert_sorted(Container& _container, T _new_value)
{
    if (_new_value < *(min_element(_container.begin(), _container.end())))
    {
        _container.insert(_container.begin(), _new_value);
        return true;
    }
    else
        if (_new_value > *(_container.end() - 1))
        {
            _container.insert(_container.end() - 1, _new_value);
            return true;
        }
        else
        {
            auto it = lower_bound(_container.begin(), _container.end(), _new_value);
            if (it != _container.end())
            {
                _container.insert(it, _new_value);
                return true;
            }
            else
                return false;
        }
}



int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    //=============================================================================================================================
    //Task 1. Insert sorted (and its template)
    //=============================================================================================================================

    {
        vector<int> vec1;
        vec1.reserve(20);
        vec1.resize(20);
        generate(vec1.begin(), vec1.end(), []() {return rand() % 99; });
        sort(vec1.begin(), vec1.end());
        for (auto const& _vec : vec1)
        {
            cout << _vec << " ";
        }
        cout << endl;
        insert_sorted(vec1, 100);
        insert_sorted(vec1, 1);
        insert_sorted(vec1, 34);
        for (auto const& _vec : vec1)
        {
            cout << _vec << " ";
        }
        cout << endl;

        deque<double> deq1{ 3.14, 5.31, 5.25, 8.23 };
        sort(deq1.begin(), deq1.end());
        insert_sorted<deque<double>, double>(deq1, 5.01);
        for (auto const& deq : deq1)
        {
            cout << deq << " ";
        }
        cout << endl;
    }

    //=============================================================================================================================
    //Task 2. Analog vs digital
    //=============================================================================================================================
    cout << endl;
    {
        vector<double> analogS(100);
        generate(analogS.begin(), analogS.end(), []() {return getRandomNum(); });
        vector<int> digitalS(analogS.begin(), analogS.end());
        for (auto const& aElem : analogS)
            cout << aElem << " ";
        cout << endl << endl;
        for (auto const& dElem : digitalS)
            cout << dElem << " ";
        cout << endl;
        vector<double> disruption(100);
        transform(analogS.begin(), analogS.end(), digitalS.begin(), disruption.begin(), [](double _analog, int _digital) {
            return pow((_analog - static_cast<double>(_digital)), 2); });
        double result = accumulate(disruption.begin(), disruption.end(), 0.0);
        cout << "Ошибка цифрового сигнала равна: " << setprecision(7) << result << endl;
    }

    return 0;
}
