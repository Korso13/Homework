#include <iostream>
#include "stdint.h" // in8_t = char; int16_t = short int; int32_t = long (int); int64_t = long long;

using namespace std;

//Задание 1. Печать одномерного массива через функцию с передачей аргументов
void DoublePrinter(const size_t Size, double *arr)
{ 
    int i;
    for (i = 0; i < Size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//Задание 2. Подмена значений в массиве
void replacer(const size_t size, int16_t* arr)
{
    int i;
    for (i = 0; i < size; i++)
        arr[i] = !arr[i];
}

//Задание 3. Функция заполнения массива
void arrInit(const size_t size_i, int16_t* arr)
{
    arr[0] = 1;
    for (int i = 1; i < size_i; i++)
        arr[i] = arr[i - 1] + 3;
}

//Задание 4. Смещение массива
void arrShift(const int s, int* arr1, int n)
{
    if (n == 0)
        return;
    if (abs(n) > s)   //усечение n когда оно больше размера массива
        n = n % s;
    const int shift = (n > 0) ? abs(n) : (s - abs(n)); //Определяем направление смещения
    int i;
    int *arr2 = new int[s]; //Не хотел хардкодить размер массива, а передать константу чтобы не ругался компилятор не выходило. Подсмотрел решение в сети 
    
    //Начало перестановок
    int k = 0;
    for (i = shift; i < s; i++)
    {
        arr2[i] = arr1[k];
        k++;
    }
    k = (n < 0) ? abs(n) : (s - abs(n)); //поправка по направлению смещения. Если смещение влево, отступ для записи отсчитываем слева. Если смещение вправо - то с правого края
    for (i = 0; i < shift; i++)
    {
        arr2[i] = arr1[k];
        k++;
    }
    //накатываем смещённый массив на изначальный
    for (i = 0; i < s; i++)
        arr1[i] = arr2[i];
    return;
}

//Задание 5. Проверка массива на сбалансированность
int sum(const int i, const int s, int* arr);  //прототипируем функцию описанную ниже но нужную уже сейчас
bool balanceCheck(const size_t s, int32_t *arr)
{
    for (int i = 0; i < (s - 1); i++)
    {
        if (sum(0, (i + 1), arr) == sum((i + 1), s, arr))
            return true;
    }
    return false;
}

int sum(const int i, const int s, int* arr)
{
    int result = 0;
    for (int j = i; j < s; j++)
        result = result + arr[j];
    return result;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    //Задание 1. Печать одномерного массива через функцию с передачей аргументов
    const size_t SIZE = 5;
    double arr1[SIZE] = { 3.14, 5.15, 6.23, 2.43, 1.24 };
    DoublePrinter(SIZE, arr1);

    //Задание 2. Подмена значений в массиве
    const size_t SIZE2 = 10;
    int16_t arr2[SIZE2] = { 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 };
    int i;
    for (i = 0; i < SIZE2; i++)
        cout << arr2[i] << " ";
    std::cout << endl;

    replacer(SIZE2, arr2);

    for (i = 0; i < SIZE2; i++)
        cout << arr2[i] << " ";
    cout << endl;

    //Задание 3. Функция заполнения массива
    const size_t SIZE3 = 8;
    int16_t arr3[SIZE3]{ 0 };
    arrInit(SIZE3, arr3);
    for (i = 0; i < SIZE3; i++)
        cout << arr3[i] << " ";
    cout << endl;

    //Задание 4. Смещение массива
    const int SIZE4 = 9;
    int shf = 15; //Величина смещения. Положительные значения смещают массив циклически вправо. Отрицательные - влево
    int arr4[SIZE4] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    for (i = 0; i < SIZE4; i++) //до
        cout << arr4[i] << " ";
    cout << endl;

    arrShift(SIZE4, arr4, shf);
    
    for (i = 0; i < SIZE4; i++) //после
        cout << arr4[i] << " ";
    cout << endl;

    //Задание 5. Проверка массива на сбалансированность
    cout << "Задание 5:" << endl;   //УДАЛИТЬ!!!
    const size_t SIZE5 = 6;
    int32_t arr5[SIZE5] = { 1, 2, 7, 1, 1, 8 }; //true
    for (i = 0; i < SIZE5; i++) 
        cout << arr5[i] << " ";
    cout << "---> " << boolalpha << balanceCheck(SIZE5, arr5) << endl;
    cout << endl;

    const size_t SIZE6 = 8;
    int32_t arr6[SIZE6] = { 12, 2, 1, 1, 8, 2, 3, 1 }; //true
    for (i = 0; i < SIZE6; i++)
        cout << arr6[i] << " ";
    cout << "---> " << boolalpha << balanceCheck(SIZE6, arr6) << endl;
    cout << endl;

    const size_t SIZE7 = 6;
    int32_t arr7[SIZE7] = { 1, 2, 3, 1, 2, 8 }; //false
    for (i = 0; i < SIZE7; i++)
        cout << arr7[i] << " ";
    cout << "---> " << boolalpha << balanceCheck(SIZE7, arr7) << endl;
    cout << endl;
    return 0;
}
