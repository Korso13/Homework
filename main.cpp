#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include "Timer.hpp"
#include <string>


//=============================================================================================================================
//Task 1. Ptr swap
//=============================================================================================================================

template <class P1, class P2>
void Swap(P1& ptr1, P2& ptr2)
{
    auto temp = ptr1;
    ptr1 = reinterpret_cast<P1>(ptr2);
    ptr2 = reinterpret_cast<P2>(temp);
}

//=============================================================================================================================
//Task 2. SortPointers
//=============================================================================================================================

template <class P>
void SortPointers(std::vector<P>& ptrVector)
{
    sort(ptrVector.begin(), ptrVector.end(), [](const P& obj1, const P& obj2) {return *(obj1) < *(obj2); });
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    //=============================================================================================================================
    //Task 1. Ptr swap tests
    //=============================================================================================================================

    {
        int a{ 5 };
        double b{ 3.14 };
        std::string str{ "Testing" };
        std::string str2{ "Testing 2" };
        int* ptr1 = &a;
        double* ptr2 = &b;
        std::string* ptr3 = &str;
        std::string* ptr4 = &str2;

        auto printPtr = [&]() {std::cout << "a: " << a << " " << "ptr1: " << ptr1 << std::endl << "str: " << str << " " << "ptr3: " << ptr3 << std::endl << "b: " << b << " " << "ptr2: " << ptr2 << std::endl << "str2: " << str2 << " " << "ptr4: " << ptr4 << std::endl << std::endl;; };
        printPtr();
        Swap<int*, std::string*>(ptr1, ptr3);
        Swap<double*, std::string*>(ptr2, ptr4);
        printPtr();


    }


    //=============================================================================================================================
    //Task 2. SortPointers tests
    //=============================================================================================================================


    {
        std::vector<int*> vector;
        auto printPtrVector = [](const std::vector<int*>& vector) {
            for (auto const& element : vector)
            {
                std::cout << *(element) << " ";
            }
            std::cout << std::endl << std::endl;
        };

        for (size_t i = 0; i < 20; i++)
        {
            vector.push_back(new int(rand() % 100));
        }

        printPtrVector(vector);
        SortPointers(vector);
        printPtrVector(vector);

    }

    //=============================================================================================================================
    //Task 3. Counting vowels in War and Peace
    //=============================================================================================================================

    {
        std::ifstream file("War and peace.txt");
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0);
        std::string s(size, ' ');
        file.read(&s[0], size);

        //std::string vowels{ "EYUOAeyuioaÀÁÄÒÓÖÙÚÜÈÉËÌÍÏàáäèéëíìïòóöùúü" }; // methods using find miss all extra characters ;(
        std::string vowels{ "EYUOAeyuioa" };

        Timer timer("count_if and find");
        std::cout << "Кол-во гласных: " << count_if(s.begin(), s.end(), [vowels](const char& ch) {
            if (vowels.find(ch) != std::string::npos)
                return true;
            else
                return false;
            }) << std::endl;
        timer.print();
        std::cout << std::endl;
        
        timer.start("count_if and 'for' loop");
        int count{ 0 };
        for (const auto elem : vowels)
        {
            count = count + count_if(s.begin(), s.end(), [elem](const char& ch){if (elem == ch)
                return true;
            else
                return false; });
        }
        std::cout << "Кол-во гласных: " << count << std::endl;
        timer.print();
        std::cout << std::endl;

        timer.start("'for' loop and find");
        count = 0;
        for (const auto elem : s)
        {
            if (vowels.find(elem) != std::string::npos)
                count++;
        }
        std::cout << "Кол-во гласных: " << count << std::endl;
        timer.print();
        std::cout << std::endl;

        timer.start("double 'for' loop");
        count = 0;
        for (const auto elem_book : s)
        {
            for (const auto elem_vowel : vowels)
                if (elem_vowel == elem_book)
                    count++;
        }
        std::cout << "Кол-во гласных: " << count << std::endl;
        timer.print();
        std::cout << std::endl;

        /*
        Результаты:
        Для малого фрагмента:
        count_if and find: 	0.6787 0.674 0.678
        count_if and 'for' loop:  0.7292 0.699 0.695
        'for' loop and find: 	0.6675 0.6647 0.6663
        double 'for' loop: 		0.6716 0.6445 0.6359

        Для всей книги:
        count_if and find: 	90.2957  89.2917  89.4096
        count_if and 'for' loop:  149.513  147.153  147.068
        'for' loop and find: 	78.1582  79.2594  77.6809
        double 'for' loop: 		117.918  118.031  117.32

        Выводы:
        Методы count_if and find и 'for' loop and find - самые быстрые, но не работают "из коробки" с нестандартными символами типа "àáäèéëíìïòóöùúü"
        Методы count_if and 'for' loop и double 'for' loop - заметно медленее на больших фрагментах, но зато ловят все символы :)
        */

    }
    

    return 0;
}
