#include <iostream>
#include <cassert> // для assert()
#include <vector>
#include <set> //for 2nd task

//from 3rd homework for use in task 3
enum Ranks { two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 10, queen = 10, king = 10, ace = 1 };
enum Suits { spades, clubs, diamonds, hearts };

class Card
{
protected:
    Ranks m_value;
    Suits m_suit;
    bool m_faceUp{ 0 }; //0 - рубашкой кверху, 1 - в открытую
public:
    Card(Ranks value, Suits suit, bool faceUp = 0) : m_value(value), m_suit(suit), m_faceUp(faceUp) {}

    void Flip()
    {
        m_faceUp = !m_faceUp;
    }

    Ranks GetValue() const
    {
        return m_value;
    }
};

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

  void print() const
  {
      for (size_t i = 0; i < m_length; i++)
      {
          std::cout << m_data[i] << " ";
      }
      std::cout << std::endl;
  }
};

//=====================================================================================================
//Task 3. Creating class Hand for BJ
//=====================================================================================================

class Hand
{
protected:
    std::vector<Card*> m_hand;
public:
    Hand() {}
    virtual ~Hand() {}

    void Add(Card* card) 
    {
        m_hand.push_back(card);
    }

    void Clear()
    {
        m_hand.clear();
    }

    int GetValue() const
    {
        int sum{ 0 };
        int aces{ 0 };
        for (size_t i = 0; i < m_hand.size(); i++)
        {
            if (m_hand[i]->GetValue() == ace)
            {
                sum += 11;
                aces++;
            }
            else
                sum += m_hand[i]->GetValue();
        }

        //if total value exceeds 21 we remove extra 10 points per ace reducing it from 11 to 1. This way aces work even if drawn from index 0 and value exceeds 21 later on
        if (sum > 21 && aces > 0) 
            sum = sum - (aces * 10);

        return sum;
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
        vec1.push_back(1);
        vec1.push_back(10);
        vec1.push_back(24);
        vec1.push_back(10);
        vec1.push_back(55);
        vec1.push_back(124);
        vec1.push_back(1);
        vec1.push_back(86);
        vec1.push_back(124);
        vec1.push_back(76);
        vec1.push_back(24);
        vec1.push_back(56); //total 12. should be 8 unique. Let's check it

        std::set<int> uniqueElements;
        for (size_t i = 0; i < vec1.size(); i++)
        {
            uniqueElements.insert(vec1[i]);
        }

        std::cout << "Кол - во уникальных элементов вектора: " << uniqueElements.size() << std::endl;
    }


    //Tests for task 3. Class Hand 
    std::cout << "Task 3" << std::endl;
    {
        Card card1(ace, clubs, 1);
        Card card2(jack, clubs, 1);
        Card card3(seven, clubs, 1);
        Card card4(five, clubs, 1);
        Hand hand1;
        hand1.Add(&card1);
        std::cout << hand1.GetValue() << std::endl; //11
        hand1.Add(&card2);
        std::cout << hand1.GetValue() << std::endl; //21
        hand1.Add(&card4);
        std::cout << hand1.GetValue() << std::endl; //16
        hand1.Add(&card3);
        std::cout << hand1.GetValue() << std::endl; //23
    }

    //old solution for task 2
    /*{
        std::vector<int> vec1;
        vec1.push_back(1);
        vec1.push_back(10);
        vec1.push_back(24);
        vec1.push_back(10);
        vec1.push_back(55);
        vec1.push_back(124);
        vec1.push_back(1);
        vec1.push_back(86);
        vec1.push_back(124);
        vec1.push_back(76);
        vec1.push_back(24);
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
    }*/


    return 0;
}
