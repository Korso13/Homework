#include <iostream>
#include <fstream>
#include <string>
#include "arr_org.h"

using namespace std;

void cinCheck()
{
 if (cin.fail())
    {
        cout << "Некорректный ввод!" << endl;
        cin.clear();
        cin.ignore(32767, '\n');
    }
}

//=============================================================================================
//Задание 2. Проверка числа через макрокоманду
//=============================================================================================

#define CHECK(a, b) \
if (a >=0 && a < b) \ 
return true \
else if(a > b && a <= 0) \
return true \
else return false;

//=============================================================================================
//Задание 3. Сортировка массива
//=============================================================================================
#define SIZE_ARR 7
#define SwapINT(a, b) \
int c \
c = a \
a = b \
b = c;

 //=============================================================================================
 //Задание 4. Побайтовое выравнивание, структуры и все, все, все
 //=============================================================================================
 #pragma pack(push, 1)
struct employee 
{
 int id{0};
 string mane;
 short int age{0};
 int salary{0};
}
 #pragma pack(pop)

int main()
{
    setlocale(LC_ALL, "Russian");
    //=============================================================================================
    //Задание 1 и 5. Инициализация и работа с массиовм из функций
    //=============================================================================================
MySpc::arrPrint(MySpc::arrInit (), SIZE);
MySpc::arrCount(arr);
std::cout << endl;  
    //=============================================================================================
    //Задание 2. Проверка числа через макрокоманду
    //=============================================================================================
int a, b;
std::cout << "Введите число 1: ";
std::cin >> a;
cinCheck();
std::cout << endl;
std::cout << "Введите число 2: ";
std::cin >> b;
cinCheck();
std::cout << endl;    
std::cout << alphabool << CHECK(a, b) << std::endl;
#undef CHECK  //Не нужны нам запутывающие макросы в коде :)
    //=============================================================================================
    //Задание 3. Сортировка массива
    //=============================================================================================
int = arr1[SIZE_ARR];
std::cout << "Введите " << SIZE_ARR << " чисел: ";
for (int i = 0; i < SIZE_ARR; i++) //Заполняем массив
{
std::cin >> arr1[i];
cinCheck();
std::cout << " ";
}
 
bool trg = false; 
do //Схема из двух циклом для сортировки
{
trg = false;
 for (int i = 1; i < SIZE_ARR; i++)
 {   
  if (arr1[i] < arr1[i-1])
  {
     SwapINT(arr1[i], arr1[i-1])
     trg = true;
  }
}
while (trg != false); 
for (int i = 0; i < SIZE_ARR; i++)
{std::cout << arr1[i] << " ";}
 std::cout << std::endl;
    //=============================================================================================
    //Задание 4. Побайтовое выравнивание, структуры и все, все, все
    //=============================================================================================
 employee * worker1 = new (std::nowthrow) employee;
 employee->id = 1;
 employee->name = Jon Doe;
 employee->age = 32;
 employee->salary = 45'000;
 std::cout << "id: " << employee->id << " ";
 std::cout << "name: " << employee->name << " ";
 std::cout << "age: " << employee->age << " ";
 std::cout << "salary: " << employee->salary << " ";
 std::cout << std::endl;
 std::cout << "Размер структуры worker1 = " << sizeof(worker1);
 std::ofstream fout("output.txt");
  if (fout.is_open())
  {
   fout << "id: " << employee->id << std::endl;
   fout << "name: " << employee->name <<  std::endl;
   fout << "age: " << employee->age <<  std::endl;
   fout << "salary: " << employee->salary <<  std::endl;
   fout.close();
  }
  else
   cerr << "Ошибка создания\открытия файла!" << std::endl;
    return 0;
}
