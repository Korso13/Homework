#pragma once
#include "randDouble.hpp"
#include <random>
#include <chrono>
using namespace std;

double getRandomNum()
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_real_distribution<double> dis(0.00, 99.99);
	return dis(generator);
}
