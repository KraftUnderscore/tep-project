#pragma once
#include "CRandom.h"
#include "CMscnProblem.h"
class CRandomMod
{
public:
	CRandomMod() { iSetMaxCount(RANDOM_SEARCH_DEFAULT_COUNT); }
	CRandomMod(int iMaxCount) { iSetMaxCount(iMaxCount); }
	~CRandomMod();
	int iSetMaxCount(int iMaxCount);
	double* pdSolve(CMscnProblem* c_problem);
	void vSetSeed(int iSeed) { c_rand.vSetSeed(iSeed); }
	int iGetSeed() { return c_rand.iGetSeed(); }
private:
	CRandom c_rand;
	int i_max_count;
	int i_count;
	double* pd_current_best_solution;
	double d_current_best_quality;
};