#include <iostream>
#include <string>
#include "stdint.h" // in8_t = char; int16_t = short int; int32_t = long (int); int64_t = long long;
extern int a;
extern int b;
extern int c;
extern int d;

int main()
{
    setlocale(LC_ALL, "Russian");
    //Задания 1-4, вычисление с использованием static_cast
    float resl;
    resl = a * (b + (static_cast <float>(c) / d));
    std::cout << "Результат операции: " << resl << std::endl;
    //Задание 2. Тернарный оператор
    int inpt{ 0 };
    std::string outpt;
    int res{0};
    std::cout << "Введите целое число: ";
    std::cin >> inpt;
    res = (inpt < 21) ? (21 - inpt) : ((inpt-21) * 2);
    if (inpt < 21)
    {
        std::cout << "Введённое число меньше 21 на: " << res << std::endl;
    }
    else std::cout << "Введённое число больше или равно 21. Удвоенная разница равна: " << res << std::endl;
    // Задание 3. Трехмерный массив и указатель в центр куба.
    int cube[3][3][3] = { 0 };
    int *cubepnt;
    cubepnt = nullptr; 
    cubepnt = &cube[1][1][1];
    std::cout << "Значение центра куба? ";
    std::cin >> cube[1][1][1];
    std::cout << std::endl; 
    std::cout << "Значение ячейку куба по указателю: " << * cubepnt << std::endl;
    //альтернативное присвоение по указателю
    cubepnt = &cube[1][1][1];
    *cubepnt = 20;
    std::cout << "Значение ячейку куба по указателю: " << *cubepnt << std::endl;
    return 0;
}
