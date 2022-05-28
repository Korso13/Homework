#include <iostream>
#include <cassert> // для assert()
#include <vector>

class ArrayInt
{
private:
  int m_length;
  int* m_data;

public:
  ArrayInt(): m_length(0), m_data(nullptr) { }

  ArrayInt(int length):
  m_length(length)
  {
    assert(length >= 0);

    if (length > 0) 
    {
      m_data = new int[length];
    } 
    else 
    {
      m_data = nullptr;
    }
  }

  ~ArrayInt()
  {
    delete[] m_data;
  }

  void erase()
  {
    delete[] m_data;

    // Здесь нам нужно указать m_data значение nullptr, чтобы на выходе не было висячего указателя
    m_data = nullptr;
    m_length = 0;
  }

  int getLength() const { return m_length; }

  int& operator[](int index)
  {
    assert(index >= 0 && index < m_length);
    return m_data[index];
  }

// Функция resize изменяет размер массива. Все существующие элементы сохраняются. Процесс медленный
  void resize(int newLength)
  {
    // Если массив уже нужной длины — return
    if (newLength == m_length) {
      return;
    }

    // Если нужно сделать массив пустым — делаем это и затем return
    if (newLength <= 0) {
      erase();
      return;
    }

    // Теперь знаем, что newLength >0
    // Выделяем новый массив
    int *data = new int[newLength];

    // Затем нужно разобраться с количеством копируемых элементов в новый массив
    // Нужно скопировать столько элементов, сколько их есть в меньшем из массивов
    if (m_length > 0) {
      int elementsToCopy = (newLength > m_length) ? m_length : newLength;

      // Поочередно копируем элементы
      for (int index=0; index < elementsToCopy ; ++index) {
        data[index] = m_data[index];
      }
    }

    // Удаляем старый массив, так как он нам уже не нужен
    delete[] m_data;

    // И используем вместо старого массива новый! Обратите внимание, m_data указывает
    // на тот же адрес, на который указывает наш новый динамически выделенный массив. Поскольку
    // данные были динамически выделенные — они не будут уничтожены, когда выйдут из области видимости
    m_data = data;
    m_length = newLength;
  }

  void insertBefore(int value, int index)
  {
    // Проверка корректности передаваемого индекса
    assert(index >= 0 && index <= m_length);

    // Создаем новый массив на один элемент больше старого массива
    int* data = new int[m_length+1];

    // Копируем все элементы до index-а
    for (int before=0; before < index; ++before) {
      data[before] = m_data[before];
    }

    // Вставляем новый элемент в новый массив
    data [index] = value;

    // Копируем все значения после вставляемого элемента
    for (int after=index; after < m_length; ++after) {
      data[after+1] = m_data[after];
    }

    // Удаляем старый массив и используем вместо него новый 
    delete[] m_data;
    m_data = data;
    ++m_length;
  }

  void push_back(int value) { insertBefore(value, m_length); }

  //=====================================================================================================
  //Task 1. Add new methods to container class
  //=====================================================================================================

  void pop_back() //поскольку в задании сказано "для удаления", возврата у функции нет
  {
      int* data = new int[m_length - 1];
      for (size_t i = 0; i < (m_length - 1); i++)
      {
          data[i] = m_data[i];
      }
      --m_length;
      delete[] m_data;
      m_data = data;
  }

  void pop_front()
  {
      int* data = new int[m_length - 1];
      for (size_t i = 1; i < m_length; i++)
      {
          data[i-1] = m_data[i];
      }
      --m_length;
      delete[] m_data;
      m_data = data;
  }

  void sort() //взял сортировку пузырьком из прошлого курса по С++
  {
      bool trg = false;
      int swp;
      do
      {
          trg = false;   
          for (int i = 1; i < m_length; i++)
          {
              if (m_data[i] < m_data[i - 1])
              {
                  swp = m_data[i];
                  m_data[i] = m_data[i - 1];
                  m_data[i - 1] = swp;
                  trg = true;
              }
          }
      } while (trg != false);
  }

  void print()
  {
      for (size_t i = 0; i < m_length; i++)
      {
          std::cout << m_data[i] << " ";
      }
      std::cout << std::endl;
  }
};

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    //=====================================================================================================
    //Task 1. Add new methods to container class
    //=====================================================================================================

    {
        ArrayInt arrayInt;
        arrayInt.push_back(100);
        arrayInt.push_back(0);
        arrayInt.push_back(1);
        arrayInt.push_back(10);
        arrayInt.print();
        arrayInt.sort();
        arrayInt.print();
        arrayInt.pop_back();
        arrayInt.print();
        arrayInt.pop_front();
        arrayInt.print();
    }
    //=====================================================================================================
    //Task 2. Determine amount of unique vector values
    //=====================================================================================================
    std::cout << "Task 2" << std::endl;

    {
        std::vector<int> vec1;
        vec1.push_back(1); //
        vec1.push_back(10); //
        vec1.push_back(24); //
        vec1.push_back(10); //
        vec1.push_back(55);
        vec1.push_back(124); //
        vec1.push_back(1); //
        vec1.push_back(86);
        vec1.push_back(124); //
        vec1.push_back(76);
        vec1.push_back(24); //
        vec1.push_back(56); //total 12. should be 8 unique. Let's check it

        std::vector<int> vU;
        bool match{ false };
        for (size_t i = 0; i < vec1.size(); i++)
        {
            match = false;
            for (size_t k = 0; k < vU.size(); k++)
            {
                if (vec1[i] == vU[k])
                {
                    match = true;
                    break;
                }
            }
            if (match == false)
                vU.push_back(vec1[i]);
        }
        std::cout << "Кол - во уникальных элементов вектора: " << vU.size() << std::endl;
    }

    return 0;
}
