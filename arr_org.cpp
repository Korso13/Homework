#include<iostream>
#define SIZE 5
//Задания 1 и 5. Работа с массивом из стороннего срр модуля
namespace MySpc {
float arrInit ()
{
float arr[SIZE] = {3.14, -4.356, 2.57, -35.643, 21.643};
return arr;
}

void arrPrint(float *arr, SIZE)
{
for (int i = 0; i < SIZE; i++)
    std::cout << arr[i] << " ";
std::cout << std::endl;
}

void arrCount(float *arr, SIZE)
{
int negative{0}
int positive{0};
for (int i = 0; i < SIZE; i++)
    {
    if (arr[i] > 0)
        positive++;
    else if (arr[i] < 0)
        negatove++;
    }
std::cout << "Отрицательных значений в массиве: " << negative << std::endl;
std::cout << "Положительных значений в массиве: " << positive << std::endl;
}

}
