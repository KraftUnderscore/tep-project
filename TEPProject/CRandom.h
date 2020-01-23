#pragma once
#include "Constants.h"
#include <random>

class CRandom
{
public:
	CRandom();
	CRandom(int iSeed);
	void vSetSeed(int iSeed);
	int iSetIntRange(int iMin, int iMax);
	int iSetDoubleRange(double dMin, double dMax);
	int iGetSeed() { return i_seed; }
	int iGetInt();
	double dGetDouble();
private:
	int i_seed;
	std::uniform_int_distribution<int> u_int_generator;
	std::uniform_real_distribution<double> u_double_generator;
	std::mt19937_64 m_engine;
};