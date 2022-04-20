#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//=============================================================================================
//Задание 1. Динамический одномерный массив
//=============================================================================================
int sqr(int a, size_t i) //функция для возведения в степень
{
    int res{ 1 };
    if (i == 0)
        return res;
    else
        for (int j = 0; j < i; j++)
        {
            res = res * a;
        }
    return res;
}
void fill_print(size_t s1, int* arr1) //функция заполнения массива и вывода на печать.
{
    for (size_t i = 0; i < s1; i++)
    {
        arr1[i] = 1 * sqr(2, i); //функция возведения в степень i. 
        cout << arr1[i] << " ";
    }
}
//=============================================================================================
//Задание 2. Динамический двухмерный массив
//=============================================================================================
int** init() //Инициализация двухмерного динамического массива
{
    int** arr2 = new (std::nothrow) int* [4];
    if (arr2 != nullptr)
    {
        for (size_t i = 0; i < 4; i++)
        {
            arr2[i] = new (std::nothrow) int[4];
            if (arr2[i] != nullptr)
                continue;
            else
            {
                break;
                return 0;
            }
        }
        return arr2;
    }
    else
        return 0;
}

void fill_print2(int **arr2) //заполнение и печать
{
    srand(time(0));
    for (size_t i = 0; i < 4; i++) 
    {
        for (size_t j = 0; j < 4; j++)
        {
            arr2[i][j] = (rand() % 100);
            cout << arr2[i][j] << " ";
        }
        cout << endl;
    }
}

void del1(int** arr2)  //Удаление
{
    for (size_t i = 0; i < 4; i++)
    {
        delete[] arr2[i];
    }
    delete[] arr2;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    //=============================================================================================
    //Задание 1. Динамический одномерный массив
    //=============================================================================================

    size_t s1{ 0 };
    cout << "Введите размер массива: ";
    cin >> s1;
    int* arr1 = new (std::nothrow) int[s1];
    if (arr1 != nullptr)
    {
        fill_print(s1, arr1);
        delete[] arr1;
    }
    cout << endl;
    cout << endl;

    //=============================================================================================
    //Задание 2. Динамический двухмерный массив
    //=============================================================================================

    int** arr2 = init(); //инициализация массива
    fill_print2(arr2); //заполнение и печать
    del1(arr2);  //Удаление

    //=============================================================================================
    //Задание 3. Создание 2х txt файлов
    //=============================================================================================

    string filename1;
    string filename2;
   
    cout << "введите имя файла 1: ";
    cin >> filename1;
    if (cin.fail())
    {
        cout << "Некорректный ввод!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
    }
    filename1 += ".txt";
    ofstream fo(filename1);
    if (fo.is_open())
    {
        fo << "Look at my file, " << endl;
        fo << "Look at my file, " << endl;
        fo << "Look at my file, " << endl;
        fo.close();
    }
    
    cout << "введите имя файла 2: ";
    cin >> filename2;
    if (cin.fail())
    {
        cout << "Некорректный ввод!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
    }
    filename2 += ".txt";
    fo.open(filename2);
    if (fo.is_open())
    {
        fo << "my file is amazing!" << endl;
        fo << "my file is amazing!" << endl;
        fo << "my file is amazing!" << endl;
        fo.close();
    }
    //=============================================================================================
    //Задание 4. Склейка файлов
    //=============================================================================================
    cout << "введите имя файла 1: ";
    cin >> filename1;
    if (cin.fail())
    {
        cout << "Некорректный ввод!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
    }
    filename1 += ".txt";

    cout << "введите имя файла 2: ";
    cin >> filename2;
    if (cin.fail())
    {
        cout << "Некорректный ввод!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
    }
    filename2 += ".txt";

    string filename3;
    cout << "Как назовём файл склейки? ";
    cin >> filename3;
    if (cin.fail())
    {
        cout << "Некорректный ввод!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
    }
    filename3 += ".txt";
    
    string str;
    ofstream fo2(filename3); //собственно склейка
    if (fo2.is_open())
    {
        ifstream fi1(filename1);
        if (fi1.is_open())
        {
            for (size_t i = 0; i < 3; i++)
            {
                getline(fi1, str);
                fo2 << str << endl;
            }
            fi1.close();
        }
        fi1.open(filename2);
        if (fi1.is_open())
        {
            for (size_t i = 0; i < 3; i++)
            {
                getline(fi1, str);
                fo2 << str << endl;
            }
            fi1.close();
        }
        fo2.close();
    }

    //=============================================================================================
    //Задание 5. Поиск слова в файле
    //=============================================================================================

    return 0;
}
