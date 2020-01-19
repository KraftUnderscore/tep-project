#pragma once
#include "CRandom.h"
#include "CMscnProblem.h"
class CRandomSearch
{
public:
	CRandomSearch() { iSetMaxCount(RANDOM_SEARCH_DEFAULT_COUNT); }
	CRandomSearch(int iMaxCount) { iSetMaxCount(iMaxCount); }
	~CRandomSearch();
	int iSetMaxCount(int iMaxCount);
	double* pdSolve(CMscnProblem* c_problem);
private:
	CRandom c_rand;
	int i_max_count;
	int i_count;
	double* pd_current_best_solution;
	double d_current_best_quality;
};