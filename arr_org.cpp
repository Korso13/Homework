#include<iostream>
#define SIZE 5

//Задания 1 и 5. Работа с массивом из стороннего срр модуля
namespace MySpc 
{
    void arrInit (float *arr)
    {
        arr[0] = 3.14;
        arr[1] = -1.36;
        arr[2] = 2.57;
        arr[3] = -2.63;
        arr[4] = 1.63;
    }

    void arrPrint(float *arr)
    {
        for (int i = 0; i < SIZE; i++)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
    }

    void arrCount(float *arr)
    {
        int negative{ 0 };
        int positive{0};
        for (int i = 0; i < SIZE; i++)
        {
            if (arr[i] > 0)
                positive++;
            else if (arr[i] < 0)
                negative++;
        }
        std::cout << "Отрицательных значений в массиве: " << negative << std::endl;
        std::cout << "Положительных значений в массиве: " << positive << std::endl;
    }

}
