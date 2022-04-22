#include <iostream>
#include <fstream>
#include <string>
#include "arr_org.h"
#define SIZE 5

void cinCheck()
{
 if (std::cin.fail())
    {
     std::cout << "Некорректный ввод!" << std::endl;
     std::cin.clear();
     std::cin.ignore(32767, '\n');
    }
}

//=============================================================================================
//Задание 2. Проверка числа через макрокоманду
//=============================================================================================

#define CHECK(a, b) ((a >=0 && a < b) || (a > b && a <= 0)) ? true : false


//=============================================================================================
//Задание 3. Сортировка массива
//=============================================================================================
#define SIZE_ARR 7
#define SwapINT(a, b) \
int c; \
c = a; \
a = b; \
b = c;

 //=============================================================================================
 //Задание 4. Побайтовое выравнивание, структуры и все, все, все
 //=============================================================================================
 #pragma pack(push, 1)
struct employee
{
    int id{ 0 };
    std::string name;
    short int age{ 0 };
    int salary{ 0 };
};
 #pragma pack(pop)

//=============================================================================================

int main()
{
    setlocale(LC_ALL, "Russian");
//=============================================================================================
//Задание 1 и 5. Инициализация и работа с массиовм из функций
//=============================================================================================
float arr[SIZE];
MySpc::arrInit(arr);
MySpc::arrPrint(arr);
MySpc::arrCount(arr);
std::cout << std::endl;  
//=============================================================================================
//Задание 2. Проверка числа через макрокоманду
//=============================================================================================
int a, b;
std::cout << "Введите число 1: ";
std::cin >> a;
cinCheck();
std::cout << std::endl;
std::cout << "Введите число 2: ";
std::cin >> b;
cinCheck();
std::cout << std::endl;
std::cout << std::boolalpha << CHECK(a, b);
std::cout << std::endl;
#undef CHECK  //Не нужны нам запутывающие макросы в коде :)
//=============================================================================================
//Задание 3. Сортировка массива
//=============================================================================================
int arr1[SIZE_ARR];
std::cout << std::endl;
std::cout << "Введите " << SIZE_ARR << " чисел: " << std::endl;
for (int i = 0; i < SIZE_ARR; i++) //Заполняем массив
{
    std::cin >> arr1[i];
    cinCheck();
}

bool trg = false; 
do //Схема из двух циклом для сортировки
{
    trg = false;
    for (int i = 1; i < SIZE_ARR; i++)
    {
        if (arr1[i] < arr1[i - 1])
        {
            SwapINT(arr1[i], arr1[i - 1]);
            trg = true;
        }
    }
}
while (trg != false); 
for (int i = 0; i < SIZE_ARR; i++)
{std::cout << arr1[i] << " ";}
 std::cout << std::endl;
//=============================================================================================
//Задание 4. Побайтовое выравнивание, структуры и все, все, все
//=============================================================================================
 employee * worker1 = new (std::nothrow) employee;
 worker1->id = 1;
 worker1->name = "Jon Doe";
 worker1->age = 32;
 worker1->salary = 45'000;
 std::cout << "id: " << worker1->id << std::endl;
 std::cout << "name: " << worker1->name << std::endl;
 std::cout << "age: " << worker1->age << std::endl;
 std::cout << "salary: " << worker1->salary << std::endl;
 std::cout << "Размер структуры worker1 = " << sizeof(worker1);
 std::ofstream fout("output.txt");
  if (fout.is_open())
  {
   fout << "id: " << worker1->id << std::endl;
   fout << "name: " << worker1->name <<  std::endl;
   fout << "age: " << worker1->age <<  std::endl;
   fout << "salary: " << worker1->salary <<  std::endl;
   fout.close();
  }
  else
   std::cerr << "Ошибка создания \ открытия файла!" << std::endl;
    return 0;
}
