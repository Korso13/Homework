#include <iostream>
#include <windows.h>
#include <vector>
#include <mutex>
#include <thread>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;
once_flag callflag;

//=============================================================================================================================
//Task 1. thread-safe cout wrapper
//=============================================================================================================================

class pcout
{
private:
    map<thread::id, string> PrintQueue;
public:
    pcout() {}

    template<class T>
    friend pcout& operator<<(pcout& _pcout, T _text);

    void print()
    {
        mutex _Mutex;
        lock_guard<mutex> lg{ _Mutex };
        auto it = PrintQueue.find(this_thread::get_id());
        cout << it->second;
        PrintQueue.erase(it);
    }

    ~pcout() {}
};

template<class T>
pcout& operator<<(pcout& _pcout, T _text)
{
    mutex _Mutex;
    lock_guard<mutex> lg{ _Mutex };
    auto th_id = this_thread::get_id();
    stringstream input;
    input << _text;
    if (_pcout.PrintQueue.find(th_id) != _pcout.PrintQueue.end())
        _pcout.PrintQueue.find(th_id)->second += input.str();
    else
        _pcout.PrintQueue.insert({ th_id, input.str() });
    input.clear();
    return _pcout;
}

void TestPrint(pcout p_cout, int i)
{
    p_cout << "This is the " << i << " thread" << "\n";
    p_cout << "Thread " << i << " prints fine!" << "\n";
    p_cout.print();
    return;
}

//=============================================================================================================================
//Task 2. Multi-threaded prime number search progress
//=============================================================================================================================

void PrimeNumSearcher(size_t _i, size_t& _prime, bool& _ready_flag)
{
    mutex prime_mutex;
    if (_i == 1)
    {
        lock_guard prime_guard(prime_mutex);
        _prime = 2;
        return;
    }
    else if (_i == 0)
        return;

    size_t counter{ 2 }, current_num{ 3 };
    bool prime_check{ true };
    do
    {
        prime_check = true;
        for (size_t i = 2; i < current_num; i++) //checking if current_num is prime
        {
            if (current_num % i == 0)
            {
                current_num++;
                prime_check = false;
                break;
            }
        }
        if (prime_check == false)  //current_num - 1 not a prime number
            continue;
        else //another prime number found
        {
            lock_guard<mutex> prime_guard(prime_mutex);
            _prime = current_num;
            current_num++;
            counter++;
        }
    } while ((counter-1) != _i);
    _ready_flag = true;
    return;
}

//=============================================================================================================================
//Task 3. 
//=============================================================================================================================

void owner(vector<size_t>& _valuables, mutex& owner_valuables)
{
    unique_lock owner_lock(owner_valuables);
    owner_lock.unlock();
    while (_valuables.size() != 0)
    {
        size_t new_thing{ 0 }; 
        do
        {
            new_thing = rand() % 100;
        } while (new_thing == 0);
        owner_lock.lock();
        _valuables.push_back(new_thing);
        cout << "Remaining valuables: ";
        for (const auto& val : _valuables)
            cout << val << " ";
        cout << '\n';
        owner_lock.unlock();
        this_thread::sleep_for(1s);
    }
    return;
}

void thief(vector<size_t>& _valuables, mutex& owner_valuables)
{
    unique_lock thief_lock(owner_valuables);
    thief_lock.unlock();
    while (_valuables.size() != 0)
    {
        if (!thief_lock.try_lock())
        {
            this_thread::sleep_for(500ms);
            continue;
        }
        auto it = max_element(_valuables.begin(), _valuables.end());
        if (*it != 0)
        {
            _valuables.erase(it);
            _valuables.shrink_to_fit();
        }
        cout << "Remaining valuables: ";
        for (const auto& val : _valuables)
            cout << val << " ";
        cout << '\n';
        thief_lock.unlock();
        this_thread::sleep_for(500ms); //check ms plus need to unlock guard somehow
    }
    return;
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    //=============================================================================================================================
    //Task 1. thread-safe cout wrapper
    //=============================================================================================================================
    {
        pcout p_cout;
        vector<thread> threads;
        threads.push_back(thread(TestPrint, p_cout, 1));
        threads.push_back(thread(TestPrint, p_cout, 2));
        threads.push_back(thread(TestPrint, p_cout, 3));
        for (auto& th : threads)
        {
            th.detach();
        }
        this_thread::sleep_for(1s);
    }

    //=============================================================================================================================
    //Task 2. Multi-threaded prime number search progress
    //=============================================================================================================================
    {
        size_t prime_number{ 0 };
        bool ready_flag{ false };
        thread prime_search_thread(PrimeNumSearcher, 10000, ref(prime_number), ref(ready_flag));

        while (ready_flag != true)
        {
            cout << prime_number << '\n';
            this_thread::sleep_for(1s);
        }
        prime_search_thread.detach();
        cout << "The requested prime number is: " << prime_number << '\n';
    }

    //=============================================================================================================================
    //Task 3. 
    //=============================================================================================================================
    cout << endl;
    {
        vector<size_t> valuables;
        valuables.resize(10);
        generate(valuables.begin(), valuables.end(), []() {size_t temp; do
        {
            temp = rand() % 100;
        } while (temp == 0);
        return temp; });
        
        mutex owner_valuables;
        thread owner_th(owner, ref(valuables), ref(owner_valuables));
        thread thief_th(thief, ref(valuables), ref(owner_valuables));
        owner_th.join();
        thief_th.join();
        while (valuables.size() != 0)
        {
            continue;
        }
        cout << "Thief stole all goods!";
    }

    return 0;
}
