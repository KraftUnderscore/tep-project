#include "pch.h"
#include "CRandom.h"

CRandom::CRandom()
{
	vSetSeed(DEFAULT_SEED);
}

CRandom::CRandom(int iSeed)
{
	vSetSeed(iSeed);
}

void CRandom::vSetSeed(int iSeed)
{
	i_seed = iSeed;
	m_engine.seed(i_seed);
}

int CRandom::iSetIntRange(int iMin, int iMax)
{
	if (iMax < iMin) return MAX_LESS_THAN_MIN;
	if (iMin > iMax)return MIN_GREATER_THAN_MAX;
	u_int_generator = std::uniform_int_distribution<int>(iMin, iMax);
	return SUCCESS;
}

int CRandom::iSetDoubleRange(double dMin, double dMax)
{
	if (dMax < dMin) return MAX_LESS_THAN_MIN;
	if (dMin > dMax)return MIN_GREATER_THAN_MAX;
	u_double_generator = std::uniform_real_distribution<double>(dMin, dMax);
	return SUCCESS;
}

int CRandom::iGetInt()
{
	return u_int_generator(m_engine);
}

double CRandom::dGetDouble()
{
	return u_double_generator(m_engine);
}

void CRandom::vRandomizeSeed()
{
	int i_prev_min = u_int_generator.min();
	int i_prev_max = u_int_generator.max();

	iSetIntRange(0, INT_MAX);
	i_seed = iGetInt();
	iSetIntRange(i_prev_min, i_prev_max);

	vSetSeed(i_seed);
}