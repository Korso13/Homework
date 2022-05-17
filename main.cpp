#include <iostream>
#include <cmath>
#include <cstdint>

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


//============================================================================================================
//Task 2. class RGBA
//============================================================================================================

class RGBA
{
private:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;
public:
    RGBA(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255) :
        m_red(red),
        m_green(green),
        m_blue(blue),
        m_alpha(alpha)
    {}

     void print()
     {
         cout << "Значения красного, зелёного, синего и прозрачности: " << static_cast <int> (m_red) << "/" << static_cast <int> (m_green) << "/" << static_cast <int> (m_blue) << "/" << static_cast <int> (m_alpha) << endl; //static_cast to enable integer value output instead of char
     }
};

//============================================================================================================
//Task 3. Stack
//============================================================================================================

class Stack
{
private:
    int st_arr[10]{0};
    size_t st_size = 0;

public:
    void reset()
    {
        for (size_t i = 0; i < st_size; i++)
        {
            st_arr[i] = 0;
        }
        st_size = 0;
    }

    bool push(int val)
    {
        if (st_size == 10)
            return false;
        else
        {
            st_arr[st_size] = val;
            st_size++;
            return true;
        }
    }

    int pop()
    {
        if (st_size == 0)
        {
            cout << "Стек пуст!" << endl;
            return 0;
        }
        else
        {
            st_size--;
            return st_arr[st_size];
        }
    }

    void print()
    {
        cout << "( ";
        for (size_t i = 0; i < st_size; i++)
        {
            cout << st_arr[i] << " ";
        }
        cout << " )" << endl;;
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");

    {
        Power test;
        test.set();
        test.calculate();
    }

    {
        RGBA colour;
        colour.print();

        unsigned short int red;
        unsigned short int green;
        unsigned short int blue;
        unsigned short int alpha;
        cout << "enter red, green, blue, alpha values: ";
        cin >> red;
        cin >> green;
        cin >> blue;
        cin >> alpha; 
        RGBA colour2(red, green, blue, alpha);
        colour2.print();
    }

    {
        Stack stack;
        stack.reset();
        stack.print();

        stack.push(3);
        stack.push(7);
        stack.push(5);
        stack.print();

        stack.pop();
        stack.print();

        stack.pop();
        stack.pop();
        stack.print();
    }

    return 0;
}
