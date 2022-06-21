#pragma once
#include <chrono>
#include <iostream>

class Timer
{
private:
  using clock_t = std::chrono::high_resolution_clock;
  using second_t = std::chrono::duration<double, std::ratio<1> >;

  std::string m_name; //имя таймера
  std::chrono::time_point<clock_t> m_beg; //время старта таймера
  double elapsed() const; //возвращает кол-во прошедших микросекунд (10−6с)

public:
  Timer() : m_beg(clock_t::now()) { } //конструктор без имени таймера
  Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }

  void start(std::string name); //метод для перезапуска таймера
  void print() const; //вывод времени в миллисекундах 10−3с
  double getElapsedTime() const; //Возврат прошедшего времени в миллисекундах 10−3с
};