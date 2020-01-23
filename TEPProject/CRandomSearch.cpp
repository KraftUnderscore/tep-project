#include "pch.h"
#include "CRandomSearch.h"

CRandomSearch::~CRandomSearch()
{
	if (pd_current_best_solution != NULL)	
		delete pd_current_best_solution;
}

int CRandomSearch::iSetMaxCount(int iMaxCount)
{
	if (iMaxCount <= 0)
	{
		i_max_count = RANDOM_SEARCH_DEFAULT_COUNT;
		return VALUE_LESS_THAN_MIN;
	}
	i_max_count = iMaxCount;
	return SUCCESS;
}

double* CRandomSearch::pdSolve(CMscnProblem* c_problem)
{
	int i_solution_size = c_problem->iGetSuppliersCount() * c_problem->iGetFactoriesCount() + c_problem->iGetFactoriesCount() * c_problem->iGetWarehousesCount() + c_problem->iGetWarehousesCount() * c_problem->iGetShopsCount();
	i_count = 0;

	if (pd_current_best_solution != NULL)
		delete pd_current_best_solution;

	pd_current_best_solution = NULL;
	d_current_best_quality = -DBL_MAX;
	int i_error;

	while (i_count < i_max_count)
	{
		double* pd_solution = new double[i_solution_size];
		for (int ii = 0; ii < i_solution_size; ii++)
		{
			c_rand.iSetDoubleRange(c_problem->dGetMin(ii, i_error), c_problem->dGetMax(ii, i_error));
			pd_solution[ii] = c_rand.dGetDouble();
		}
		if (c_problem->bConstraintsSatisified(pd_solution, &i_error))
		{
			double d_quality = c_problem->dGetQuality(pd_solution, NULL);
			std::cout << i_count << " => Quality = " << d_quality << " / Current best = " << d_current_best_quality << "\n";	//do usuniecia, ale fajnie w konsoli wyglada
			if (d_quality > d_current_best_quality)
			{
				d_current_best_quality = d_quality;
				if (pd_current_best_solution != NULL)
					delete pd_current_best_solution;

				pd_current_best_solution = pd_solution;
				pd_solution = NULL;
			}
		}
		else
		{
			delete pd_solution;
		}
		if (i_error != SUCCESS)return NULL;
		i_count++;
	}
	return pd_current_best_solution;
}