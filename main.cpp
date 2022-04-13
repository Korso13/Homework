#include <iostream>
#include "stdint.h" // in8_t = char; int16_t = short int; int32_t = long (int); int64_t = long long;

void task1()  // Задание 1. Сумма числе между 10 и 20
{
    int a, b;
    std::cout << "Введите целое число: ";
    std::cin >> a;
    std::cout << std::endl;
    std::cout << "А теперь введите ещё одно: ";
    std::cin >> b;
    std::cout << "Сумма чисел лежит в промежутке между 10 и 20?" << std::endl;
    if ((a + b) >= 10 && (a + b) <= 20)
    {
        std::cout << "True!" << std::endl;
    }
    else
        std::cout << " False!" << std::endl;
}

void task2()  // Задание 2. Сумма чисел равна 10 или каждое число равно 10
{
    const int c{ 7 };
    const int d{ 3 };
    int sum_cd = c + d;
    switch (sum_cd)
    {
    case 10:
        std::cout << "true" << std::endl;
    break;
    default: if (c == 10 && d == 10)
                std::cout << "true" << std::endl;
             else
                std::cout << "false" << std::endl;
    }
}

void task3() //Задание 3. Вывести нечётные числа от 1 до 50.
{
    int i;
    for(i = 1; i <= 50; i++)
    {
        if((i % 2) != 0)
            std::cout << i << std::endl;
    }
}

void task4() //Проверка на простые числа
{
    int16_t e;
    do //Проверим ввод корректного числа
    {
        std::cout << "Введите целое число больше 1: ";
        std::cin >> e;
        if (e > 1)
            break;
        else
            std::cout << "Некорректное число!" << std::endl;
    } while (e < 2);
    std::cout << std::endl;
    size_t i{0};
    for (i = 2; i <= e; )
     {
        if ((e % i) != 0)
        {
            i++;
        }
        else
            if (i == e)
            {
                std::cout << "Введённое число - простое!" << std::endl;
                break;
            }
            else
            {
                std::cout << "Введённое число - НЕ является простым!" << std::endl;
                std::cout << "Делитель: " << i << std::endl;
                break;
            }
     }       
}

void task5() //Задание 5. Определитель високосного года
{
    int16_t year;
    do //Проверим ввод корректного числа
    {
        std::cout << "Введите год между 1 и 3000: ";
        std::cin >> year;
        if (year >= 1 && year <= 3000)
            break;
        else
            std::cout << "Некорректный год!" << std::endl;
    } while (year < 1 || year > 3000);
    
    std::cout << std::endl;

    if ((year % 400) == 0) //Проверяем сразу исключение 400 года
    {
        std::cout << year << " год является високосным!" << std::endl;
    }
    else
        if ((year % 4) == 0) //Проверяем високосный ли год
        {
            if ((year % 100) == 0) //Проверяем не является ли год сотым. Исключение 400 года уже проверено!
                std::cout << year << " год НЕ является високосным!" << std::endl;
            else
                std::cout << year << " год является високосным!" << std::endl;
        }
        else
            std::cout << year << " год НЕ является високосным!" << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
   //task1();
   //task2();
   //task3();
   //task4();
    task5();
    return 0;
}
