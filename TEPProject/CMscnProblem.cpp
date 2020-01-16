#include "pch.h"
#include "CMscnProblem.h"
#include <iostream>
#include <sstream>
#pragma warning(disable : 4996) //fopen warning

CMscnProblem::CMscnProblem() 
{
	i_supp_count = 0;
	i_fact_count = 0;
	i_ware_count = 0;
	i_shop_count =0;

	pd_supp_caps = NULL;
	pd_fact_caps = NULL;
	pd_ware_caps = NULL;
	pd_shop_caps = NULL;

	pd_supp_to_fact_costs = NULL;
	pd_fact_to_ware_costs = NULL;
	pd_ware_to_shop_costs = NULL;

	pd_supp_use_costs = NULL;
	pd_fact_use_costs = NULL;
	pd_ware_use_costs = NULL;

	pd_shop_revenues = NULL;

	pd_supp_to_fact_goods_min_max = NULL;
	pd_fact_to_ware_goods_min_max = NULL;
	pd_ware__to_shop_goods_min_max = NULL;

	pd_supp_to_fact_goods_min = NULL;
	pd_fact_to_ware_goods_min = NULL;
	pd_ware_to_shop_goods_min = NULL;

	pd_supp_to_fact_goods_max = NULL;
	pd_fact_to_ware_goods_max = NULL;
	pd_ware_to_shop_goods_max = NULL;

	pd_supp_to_fact_goods = NULL;
	pd_fact_to_ware_goods = NULL;
	pd_ware_to_shop_goods = NULL;
};

CMscnProblem::~CMscnProblem()
{
	delete pd_supp_caps;
	delete pd_fact_caps;
	delete pd_ware_caps;
	delete pd_shop_caps;
	delete pd_supp_use_costs;
	delete pd_fact_use_costs;
	delete pd_ware_use_costs;
	delete pd_shop_revenues;
	v_delete_matrix(pd_supp_to_fact_costs, i_supp_count);
	v_delete_matrix(pd_fact_to_ware_costs, i_fact_count);
	v_delete_matrix(pd_ware_to_shop_costs, i_ware_count);
	v_delete_matrix(pd_supp_to_fact_goods_min_max, i_supp_count);
	v_delete_matrix(pd_fact_to_ware_goods_min_max, i_fact_count);
	v_delete_matrix(pd_ware__to_shop_goods_min_max, i_ware_count);
	v_delete_matrix(pd_supp_to_fact_goods_min, i_supp_count);
	v_delete_matrix(pd_fact_to_ware_goods_min, i_fact_count);
	v_delete_matrix(pd_ware_to_shop_goods_min, i_ware_count);
	v_delete_matrix(pd_supp_to_fact_goods_max, i_supp_count);
	v_delete_matrix(pd_fact_to_ware_goods_max, i_fact_count);
	v_delete_matrix(pd_ware_to_shop_goods_max, i_ware_count);
	v_delete_matrix(pd_supp_to_fact_goods, i_supp_count);
	v_delete_matrix(pd_fact_to_ware_goods, i_fact_count);
	v_delete_matrix(pd_ware_to_shop_goods, i_ware_count);
}

int CMscnProblem::iSetSuppliersCount(int iCount)
{
	if (iCount < COUNT_MIN) return COUNT_LESS_THAN_MIN;
	i_supp_count = iCount;

	v_array_matrix_creator(&pd_supp_caps, &pd_supp_use_costs, &pd_supp_to_fact_costs, &pd_supp_to_fact_goods, &pd_supp_to_fact_goods_min_max, &pd_supp_to_fact_goods_min, &pd_supp_to_fact_goods_max, i_supp_count, i_fact_count);
	return SUCCESS;
}

int CMscnProblem::iSetFactoriesCount(int iCount)
{
	if (iCount < COUNT_MIN) return COUNT_LESS_THAN_MIN;
	i_fact_count = iCount;

	v_array_matrix_creator(&pd_fact_caps, &pd_fact_use_costs, &pd_fact_to_ware_costs, &pd_fact_to_ware_goods, &pd_fact_to_ware_goods_min_max, &pd_fact_to_ware_goods_min, &pd_fact_to_ware_goods_max, i_fact_count, i_ware_count);
	iSetSuppliersCount(i_supp_count);
	return SUCCESS;
}

int CMscnProblem::iSetWarehousesCount(int iCount)
{
	if (iCount < COUNT_MIN) return COUNT_LESS_THAN_MIN;
	i_ware_count = iCount;

	v_array_matrix_creator(&pd_ware_caps, &pd_ware_use_costs, &pd_ware_to_shop_costs, &pd_ware_to_shop_goods, &pd_ware__to_shop_goods_min_max, &pd_ware_to_shop_goods_min, &pd_ware_to_shop_goods_max, i_ware_count, i_shop_count);
	iSetFactoriesCount(i_fact_count);
	return SUCCESS;
}

int CMscnProblem::iSetShopsCount(int iCount)
{
	if (iCount < COUNT_MIN) return COUNT_LESS_THAN_MIN;
	i_shop_count = iCount;

	v_array_matrix_creator(&pd_shop_caps, &pd_shop_revenues, NULL, NULL, NULL, NULL, NULL, i_shop_count, 0);
	iSetWarehousesCount(i_ware_count);
	return SUCCESS;
}

int CMscnProblem::iSetSuppCap(double dCap, int iIndex)
{
	return i_array_setter(dCap, iIndex, pd_supp_caps, i_supp_count);
}

int CMscnProblem::iSetFactCap(double dCap, int iIndex)
{
	return i_array_setter(dCap, iIndex, pd_fact_caps, i_fact_count);
}

int CMscnProblem::iSetWareCap(double dCap, int iIndex)
{
	return i_array_setter(dCap, iIndex, pd_ware_caps, i_ware_count);
}

int CMscnProblem::iSetShopCap(double dCap, int iIndex)
{
	return i_array_setter(dCap, iIndex, pd_shop_caps, i_shop_count);
}

int CMscnProblem::iSetSuppToFactCost(double dCost, int iUpperIndex, int iLowerIndex)
{
	return i_matrix_setter(dCost, pd_supp_to_fact_costs, iUpperIndex, iLowerIndex, i_supp_count, i_fact_count);
}

int CMscnProblem::iSetFactToWareCost(double dCost, int iUpperIndex, int iLowerIndex)
{
	return i_matrix_setter(dCost, pd_fact_to_ware_costs, iUpperIndex, iLowerIndex, i_fact_count, i_ware_count);
}

int CMscnProblem::iSetWareToShopCost(double dCost, int iUpperIndex, int iLowerIndex)
{
	return i_matrix_setter(dCost, pd_ware_to_shop_costs, iUpperIndex, iLowerIndex, i_ware_count, i_shop_count);
}

bool CMscnProblem::bConstraintsSatisified(double *pdSolution, int* iError)	
{
	int i_result = i_load_solution(pdSolution);
	if (i_result != SUCCESS)
	{
		if(iError!=NULL)
			*iError = i_result;
		return false;
	}

	for (int ii = 0; ii < i_fact_count; ii++)
	{
		double dSuppGoods = 0.0;
		for (int ij = 0; ij < i_supp_count; ij++)
			dSuppGoods += pd_supp_to_fact_goods[ij][ii];

		double dFactGoods = 0.0;
		for (int ij = 0; ij < i_ware_count; ij++)
		{
			dFactGoods += pd_fact_to_ware_goods[ii][ij];
			if (dFactGoods > dSuppGoods) return false;
		}
	}

	for (int ii = 0; ii < i_ware_count; ii++)
	{
		double dFactGoods = 0.0;
		for (int ij = 0; ij < i_fact_count; ij++)
			dFactGoods += pd_supp_to_fact_goods[ij][ii];

		double dWareGoods = 0.0;
		for (int ij = 0; ij < i_shop_count; ij++)
		{
			dWareGoods += pd_fact_to_ware_goods[ii][ij];
			if (dWareGoods > dFactGoods) return false;
		}
	}

	if (iError != NULL)
		*iError = SUCCESS;
	bool b1 = b_capacity_check(pd_supp_to_fact_goods, pd_supp_caps, i_supp_count, i_fact_count);
	bool b2 = b_capacity_check(pd_fact_to_ware_goods, pd_fact_caps, i_fact_count, i_ware_count);
	bool b3 = b_capacity_check(pd_ware_to_shop_goods, pd_ware_caps, i_ware_count, i_shop_count);
	bool b4 = b_capacity_check(pd_ware_to_shop_goods, pd_shop_caps, i_ware_count, i_shop_count);
	return b1 && b2 && b3 && b4;

}

double CMscnProblem::dGetQuality(double *pdSolution, int* iError)
{
	int i_result = i_load_solution(pdSolution);
	if (i_result != SUCCESS)
	{
		if (iError != NULL)
			*iError = i_result;
		return 0.0;
	}

	if (iError != NULL)
		*iError = SUCCESS;
	double d_shop_rev = d_calculate_shops_revenue();
	double d_usages_costs = d_calculate_usages_costs();
	double d_prod_trans_costs = d_calculate_upp_to_low_costs();
	return d_shop_rev - d_usages_costs - d_prod_trans_costs;
}

int CMscnProblem::iLoadProblemFromFile(std::string sFileName)
{
	FILE* pf_problem = fopen(sFileName.c_str(), "r");
	if (pf_problem == NULL)return FAILED_OPENING_FILE;
	
	int i_read_value, i_result;
	char c_dump;
	
	fscanf(pf_problem, "%c%i%c", &c_dump, &i_read_value, &c_dump);
	i_result = iSetSuppliersCount(i_read_value);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	std::cout << "read int : " << i_read_value << "\n";
	fscanf(pf_problem, "%c%i%c", &c_dump, &i_read_value, &c_dump);
	i_result = iSetFactoriesCount(i_read_value);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}	
	std::cout << "read int : " << i_read_value << "\n";
	fscanf(pf_problem, "%c%i%c", &c_dump, &i_read_value, &c_dump);
	i_result = iSetWarehousesCount(i_read_value);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}	
	std::cout << "read int : " << i_read_value << "\n";
	fscanf(pf_problem, "%c%i%c", &c_dump, &i_read_value, &c_dump);
	i_result = iSetShopsCount(i_read_value);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	std::cout << "read int : " << i_read_value << "\n";

	i_result = i_get_array_from_file(pf_problem, pd_supp_caps, i_supp_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, pd_fact_caps, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, pd_ware_caps, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, pd_shop_caps, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_matrix_from_file(pf_problem, pd_supp_to_fact_costs, i_supp_count, i_fact_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_matrix_from_file(pf_problem, pd_fact_to_ware_costs, i_fact_count, i_ware_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_matrix_from_file(pf_problem, pd_ware_to_shop_costs, i_ware_count, i_shop_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, pd_supp_use_costs, i_supp_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, pd_fact_use_costs, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, pd_ware_use_costs, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, pd_shop_revenues, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_matrix_from_file(pf_problem, pd_supp_to_fact_goods_min_max, i_supp_count, 2 * i_fact_count, SKIP_10_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_matrix_from_file(pf_problem, pd_fact_to_ware_goods_min_max, i_fact_count, 2 * i_ware_count, SKIP_10_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_matrix_from_file(pf_problem, pd_ware__to_shop_goods_min_max, i_ware_count, 2 * i_shop_count, SKIP_10_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	//FIX ME PLEASE :CCCCC
	//converting from 2*iUpp*iLow to two matrices iUp*iLow
	for (int ii = 0; ii < i_supp_count; ii++)
	{
		for (int ij = 0; ij < 2 * i_fact_count; ij++)
		{
			if (ij % 2 == 0) pd_supp_to_fact_goods_min[ii][ij] = pd_supp_to_fact_goods_min_max[ii][ij];
			else pd_supp_to_fact_goods_max[ii][ij] = pd_supp_to_fact_goods_min_max[ii][ij];
		}
	}

	for (int ii = 0; ii < i_fact_count; ii++)
	{
		for (int ij = 0; ij < 2 * i_ware_count; ij ++)
		{
			if (ii % 2 == 0)pd_fact_to_ware_goods_min[ii][ij] = pd_fact_to_ware_goods_min_max[ii][ij];
			else pd_fact_to_ware_goods_max[ii][ij] = pd_fact_to_ware_goods_min_max[ii][ij];
		}
	}

	for (int ii = 0; ii < i_ware_count; ii++)
	{
		for (int ij = 0; ij < 2 * i_shop_count; ij ++)
		{
			if (ii % 2 == 0)pd_ware_to_shop_goods_min[ii][ij] = pd_ware__to_shop_goods_min_max[ii][ij];
			else pd_ware_to_shop_goods_max[ii][ij] = pd_ware__to_shop_goods_min_max[ii][ij];
		}
	}
	fclose(pf_problem);
	return SUCCESS;
}

int CMscnProblem::iLoadSolutionFromFile(std::string sFileName, double **pdSolution)
{
	if (*pdSolution != NULL) delete *pdSolution;

	FILE* pf_problem = fopen(sFileName.c_str(), "r");
	if (pf_problem == NULL)return FAILED_OPENING_FILE;

	int i_result;
	char c_dump;
	int i_supp_count_read, i_fact_count_read, i_ware_count_read, i_shop_count_read;

	fscanf(pf_problem, "%c%i%c", &c_dump, &i_supp_count_read, &c_dump);
	fscanf(pf_problem, "%c%i%c", &c_dump, &i_fact_count_read, &c_dump);
	fscanf(pf_problem, "%c%i%c", &c_dump, &i_ware_count_read, &c_dump);
	fscanf(pf_problem, "%c%i%c", &c_dump, &i_shop_count_read, &c_dump);

	if (i_supp_count_read != i_supp_count || i_fact_count_read != i_fact_count || i_ware_count_read != i_ware_count || i_shop_count_read != i_shop_count) return SOLUTION_COUNTS_NOT_EQ_PROBLEM_COUNTS; //ERROR

	double** pd_supp_to_fact_goods_read = pd_create_matrix(i_supp_count_read, i_fact_count_read);
	double** pd_fact_to_ware_goods_read = pd_create_matrix(i_fact_count_read, i_ware_count_read);
	double** pd_ware_to_shop_goods_read = pd_create_matrix(i_ware_count_read, i_shop_count_read);

	i_result = i_get_matrix_from_file(pf_problem, pd_supp_to_fact_goods_read, i_supp_count, i_fact_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	i_result = i_get_matrix_from_file(pf_problem, pd_fact_to_ware_goods_read, i_fact_count, i_ware_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	i_result = i_get_matrix_from_file(pf_problem, pd_ware_to_shop_goods_read, i_ware_count, i_shop_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	double* pd_solution = new double[i_supp_count_read*i_fact_count_read + i_fact_count_read * i_ware_count_read + i_ware_count_read * i_shop_count_read];
	int i_offset = 0;
	for (int ii = 0; ii < i_supp_count_read; ii++)
		for (int ij = 0; ij < i_fact_count_read; ij++)
			pd_solution[ii*i_fact_count_read + ij + i_offset] = pd_supp_to_fact_goods_read[ii][ij];
	i_offset += i_supp_count_read * i_fact_count_read;
	for (int ii = 0; ii < i_fact_count_read; ii++)
		for (int ij = 0; ij < i_ware_count_read; ij++)
			pd_solution[ii*i_ware_count_read + ij + i_offset] = pd_fact_to_ware_goods_read[ii][ij];
	i_offset += i_fact_count_read * i_ware_count_read;
	for (int ii = 0; ii < i_ware_count_read; ii++)
		for (int ij = 0; ij < i_shop_count_read; ij++)
			pd_solution[ii*i_shop_count_read + ij + i_offset] = pd_ware_to_shop_goods_read[ii][ij];

	*pdSolution = pd_solution;
	fclose(pf_problem);
	return SUCCESS;
}

int CMscnProblem::iSaveProblemToFile(std::string sFileName)
{
	if (i_supp_count < COUNT_MIN || i_fact_count < COUNT_MIN || i_ware_count < COUNT_MIN || i_shop_count < COUNT_MIN) return COUNT_LESS_THAN_MIN;

	FILE* pf_problem = fopen(sFileName.c_str(), "w");
	if (pf_problem == NULL)return FAILED_OPENING_FILE;

	fprintf(pf_problem, "D %d", i_supp_count);
	fprintf(pf_problem, "\nF %d", i_fact_count);
	fprintf(pf_problem, "\nM %d", i_ware_count);
	fprintf(pf_problem, "\nS %d", i_shop_count);

	int i_result;

	fprintf(pf_problem, "\nsd\n");
	i_result = i_add_pd_array_to_file(pf_problem, pd_supp_caps, i_supp_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nsf\n");
	i_result = i_add_pd_array_to_file(pf_problem, pd_fact_caps, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nsm\n");
	i_result = i_add_pd_array_to_file(pf_problem, pd_ware_caps, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nss\n");
	i_result = i_add_pd_array_to_file(pf_problem, pd_shop_caps, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\ncd\n");
	i_result = i_add_pd_matrix_to_file(pf_problem, pd_supp_to_fact_costs, i_supp_count, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\ncf\n");
	i_result = i_add_pd_matrix_to_file(pf_problem, pd_fact_to_ware_costs, i_fact_count, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\ncm\n");
	i_result = i_add_pd_matrix_to_file(pf_problem, pd_ware_to_shop_costs, i_ware_count, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nud\n");
	i_result = i_add_pd_array_to_file(pf_problem, pd_supp_use_costs, i_supp_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nuf\n");
	i_result = i_add_pd_array_to_file(pf_problem, pd_fact_use_costs, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\num\n");
	i_result = i_add_pd_array_to_file(pf_problem, pd_ware_use_costs, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\np\n");
	i_result = i_add_pd_array_to_file(pf_problem, pd_shop_revenues, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxdminmax\n");
	i_result = i_add_pd_matrix_to_file(pf_problem, pd_supp_to_fact_goods_min_max, i_supp_count, i_fact_count * 2);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxfminmax\n");
	i_result = i_add_pd_matrix_to_file(pf_problem, pd_fact_to_ware_goods_min_max, i_fact_count, i_ware_count * 2);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxmminmax\n");
	i_result = i_add_pd_matrix_to_file(pf_problem, pd_ware__to_shop_goods_min_max, i_ware_count, i_shop_count * 2);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fclose(pf_problem);
	return SUCCESS;
}

int CMscnProblem::iSaveSolutionToFile(std::string sFileName)
{
	if (i_supp_count < COUNT_MIN || i_fact_count < COUNT_MIN || i_ware_count < COUNT_MIN || i_shop_count < COUNT_MIN) return COUNT_LESS_THAN_MIN;

	FILE* pf_problem = fopen(sFileName.c_str(), "w");
	if (pf_problem == NULL)return FAILED_OPENING_FILE;

	fprintf(pf_problem, "D %d", i_supp_count);
	fprintf(pf_problem, "\nF %d", i_fact_count);
	fprintf(pf_problem, "\nM %d", i_ware_count);
	fprintf(pf_problem, "\nS %d", i_shop_count);

	int i_result;

	fprintf(pf_problem, "\nxd\n");
	i_result = i_add_pd_matrix_to_file(pf_problem, pd_supp_to_fact_goods, i_supp_count, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxf\n");
	i_result = i_add_pd_matrix_to_file(pf_problem, pd_fact_to_ware_goods, i_fact_count, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxm\n");
	i_result = i_add_pd_matrix_to_file(pf_problem, pd_ware_to_shop_goods, i_ware_count, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fclose(pf_problem);
	return SUCCESS;
}

int CMscnProblem::i_load_solution(double *pdSolution)
{
	if (pdSolution == NULL) return NULL_SOLUTION;
	if (i_supp_count < COUNT_MIN || i_fact_count < COUNT_MIN || i_ware_count < COUNT_MIN || i_shop_count < COUNT_MIN) return COUNT_LESS_THAN_MIN;
	int i_result;
	int i_solution_offset = 0;
	i_result = i_load_part_of_solution(pdSolution, pd_supp_to_fact_goods, pd_supp_to_fact_goods_min, pd_supp_to_fact_goods_max, i_solution_offset, i_supp_count, i_fact_count);
	if (i_result != SUCCESS) return i_result;
	i_solution_offset += i_supp_count * i_fact_count - 1;
	i_result = i_load_part_of_solution(pdSolution, pd_fact_to_ware_goods, pd_fact_to_ware_goods_min, pd_fact_to_ware_goods_max, i_solution_offset, i_fact_count, i_ware_count);
	if (i_result != SUCCESS) return i_result;
	i_solution_offset += i_fact_count * i_ware_count;
	i_result = i_load_part_of_solution(pdSolution, pd_ware_to_shop_goods, pd_ware_to_shop_goods_min, pd_ware_to_shop_goods_max, i_solution_offset, i_ware_count, i_shop_count);
	return i_result;
}

int CMscnProblem::i_load_part_of_solution(double *pdSolution, double** pdMatrix, double** pdUpperToLowerMin, double** pdUpperToLowerMax, int iSolutionOffset, int iUpperCount, int iLowerCount)
{
	for (int ii = 0; ii < iUpperCount; ii++)
		for (int ij = 0; ij < iLowerCount; ij++)
		{
			double d_value = pdSolution[ii*iLowerCount + ij + iSolutionOffset];
			if (d_value < pdUpperToLowerMin[ii][ij]) return VALUE_LESS_THAN_MIN;
			if (d_value > pdUpperToLowerMax[ii][ij]) return VALUE_GREATER_THAN_MAX;
			pdMatrix[ii][ij] = d_value;
		}
	return SUCCESS;
}

double** CMscnProblem::pd_create_matrix(int iSizeX, int iSizeY)
{
	double** pd_result = new double*[iSizeX];
	for (int ii = 0; ii < iSizeX; ii++)
		pd_result[ii] = new double[iSizeY];
	return pd_result;
}

void CMscnProblem::v_delete_matrix(double** dMatrix, int iSizeX)
{
	if (dMatrix == NULL) return;
	for (int ii = 0; ii < iSizeX; ii++)
		delete dMatrix[ii];
	delete dMatrix;
}

bool CMscnProblem::b_capacity_check(double** pdProducedGoods, double* pdCapacities, int iUpperCount, int iLowerCount)
{
	for (int ii = 0; ii < iUpperCount; ii++)
	{
		double d_goods = 0.0;
		for (int ij = 0; ij < iLowerCount; ij++)
		{
			d_goods += pdProducedGoods[ii][ij];
			if (d_goods > pdCapacities[ii])return false;
		}
	}
	return true;		
}

double CMscnProblem::d_calculate_shops_revenue()
{
	double d_result = 0.0;
	for (int ii = 0; ii < i_ware_count; ii++)
		for (int ij = 0; ij < i_shop_count; ij++)
			d_result += pd_shop_revenues[ij] * pd_ware_to_shop_goods[ii][ij];

	return d_result;
}

double CMscnProblem::d_calculate_usages_costs()
{
	double d_result = 0.0;
	d_result += d_calculate_usage_cost(pd_supp_to_fact_goods, pd_supp_use_costs, i_supp_count, i_fact_count);
	d_result += d_calculate_usage_cost(pd_fact_to_ware_goods, pd_fact_use_costs, i_fact_count, i_ware_count);
	d_result += d_calculate_usage_cost(pd_ware_to_shop_goods, pd_ware_use_costs, i_ware_count, i_shop_count);
	return d_result;
}

double CMscnProblem::d_calculate_usage_cost(double** pdUpperToLowerGoods, double* pdUsageCosts, int iUpperCount, int iLowerCount)
{
	double d_result = 0.0;
	for (int ii = 0; ii < iUpperCount; ii++)
		for (int ij = 0; ij < iLowerCount; ij++)
			if (pdUpperToLowerGoods[ii][ij] > 0)
				d_result += pdUsageCosts[ij] * pdUpperToLowerGoods[ii][ij];

	return d_result;
}

double CMscnProblem::d_calculate_upp_to_low_costs()
{
	double d_result = 0.0;
	d_result += d_calculate_upp_to_low_cost(pd_supp_to_fact_costs, pd_supp_to_fact_goods, i_supp_count, i_fact_count);
	d_result += d_calculate_upp_to_low_cost(pd_fact_to_ware_costs, pd_fact_to_ware_goods, i_fact_count, i_ware_count);
	d_result += d_calculate_upp_to_low_cost(pd_ware_to_shop_costs, pd_ware_to_shop_goods, i_ware_count, i_shop_count);
	return d_result;
}

double CMscnProblem::d_calculate_upp_to_low_cost(double** pdUpperToLowerCosts, double** pdUpperToLowerGoods, int iUpperCount, int iLowerCount)
{
	double d_result = 0.0;
	for (int ii = 0; ii < iUpperCount; ii++)
		for (int ij = 0; ij < iLowerCount; ij++)
			d_result += pdUpperToLowerGoods[ii][ij] * pdUpperToLowerCosts[ii][ij];

	return d_result;
}

int CMscnProblem::i_add_pd_array_to_file(FILE* fFile, double *pdArray, int iArrayLength)
{
	if (iArrayLength < 0)return INDEX_OUT_OF_RANGE;
	if (pdArray == NULL) return NULL_ARRAY;
	else
		for (int ii = 0; ii < iArrayLength; ii++)
			fprintf(fFile, "%d ", pdArray[ii]);
	return SUCCESS;
}

int CMscnProblem::i_add_pd_matrix_to_file(FILE *fFile, double** pdMatrix, int iSizeX, int iSizeY)
{
	if (iSizeX < 0 || iSizeY < 0)return INDEX_OUT_OF_RANGE;
	if (pdMatrix == NULL) return NULL_MATRIX;
	else
		for (int ii = 0; ii < iSizeX; ii++)
		{
			for (int ij = 0; ij < iSizeY; ij++)
				fprintf(fFile, "%d ", pdMatrix[ii][ij]);
			
			fprintf(fFile, "\n");
		}
	return SUCCESS;
}

int CMscnProblem::i_get_array_from_file(FILE *pfFile, double *pdArray, int iArrayLength) 
{
	double d_read_value;
	int i_result;
	fseek(pfFile, 4, SEEK_CUR);
	std::cout << "\nreading array:\n";
	for (int ii = 0; ii < iArrayLength; ii++)
	{
		fscanf(pfFile, "%lf", &d_read_value);
		std::cout << d_read_value << " ";
		i_result = i_array_setter(d_read_value, ii, pdArray, iArrayLength);
		if (i_result != SUCCESS) return i_result;
	}
	return SUCCESS;
}

int CMscnProblem::i_get_matrix_from_file(FILE *pfFile, double** pdMatrix, int iSizeX, int iSizeY, int iFileOffset)
{
	double d_read_value;
	int i_result;
	fseek(pfFile, iFileOffset, SEEK_CUR);
	std::cout << "\nreading matrix:\n";
	for (int ii = 0; ii < iSizeX; ii++)
	{
		for (int ij = 0; ij < iSizeY; ij++)
		{
			fscanf(pfFile, "%lf", &d_read_value);
			std::cout << d_read_value << " ";
			i_result = i_matrix_setter(d_read_value, pdMatrix, ii, ij, iSizeX, iSizeY);
			if (i_result != SUCCESS) return i_result;
		}
		std::cout << "\n";
	}
	return SUCCESS;
}

double* CMscnProblem::pd_convert_matrix_to_array(double** pdMatrix, int iSizeX, int iSizeY)
{
	double* pd_array = new double[iSizeX*iSizeY];
	for (int ii = 0; ii < iSizeX; ii++) 
		for (int ij = 0; ij < iSizeY; ij++)
			pd_array[ii*iSizeY + ij] = pdMatrix[ii][ij];
	return pd_array;
}

void CMscnProblem::v_array_matrix_creator(double** pdCapacity, double** pdUseCosts, double*** pdUpperToLowerCost, double*** pdUpperToLowerItems, double*** pdUpperToLowerMinMax, double*** pdUpperToLowerMin, double*** pdUpperToLowerMax, int iUpperCount, int iLowerCount)
{
	if(*pdCapacity != NULL)
		delete *pdCapacity;
	*pdCapacity = new double[iUpperCount];

	if(*pdUseCosts!=NULL)
		delete *pdUseCosts;
	*pdUseCosts = new double[iUpperCount];
	if (pdUpperToLowerCost == NULL || pdUpperToLowerItems == NULL || pdUpperToLowerMin == NULL || pdUpperToLowerMax == NULL) return;
	v_delete_matrix(*pdUpperToLowerCost, iUpperCount);
	v_delete_matrix(*pdUpperToLowerItems, iUpperCount);
	v_delete_matrix(*pdUpperToLowerMinMax, iUpperCount);
	v_delete_matrix(*pdUpperToLowerMin, iUpperCount);
	v_delete_matrix(*pdUpperToLowerMax, iUpperCount);

	if (iLowerCount > 0)
	{
		*pdUpperToLowerCost = pd_create_matrix(iUpperCount, iLowerCount);
		*pdUpperToLowerItems = pd_create_matrix(iUpperCount, iLowerCount);
		*pdUpperToLowerMinMax = pd_create_matrix(iUpperCount, iLowerCount*2);
		*pdUpperToLowerMin = pd_create_matrix(iUpperCount, iLowerCount);
		*pdUpperToLowerMax = pd_create_matrix(iUpperCount, iLowerCount);
	}//else iLowerCount hasn't been set yet, so no matrices can be created
}

int CMscnProblem::i_array_setter(double dValue, int iIndex, double* pdArray, int iArrayLength)
{
	if (iIndex < 0) return INDEX_OUT_OF_RANGE;
	if (iIndex >= iArrayLength) return INDEX_OUT_OF_RANGE;
	if (dValue < 0.0)return VALUE_LESS_THAN_MIN;
	pdArray[iIndex] = dValue;
	return SUCCESS;
}

int CMscnProblem::i_matrix_setter(double dValue, double** pdMatrix, int iUpperIndex, int iLowerIndex, int iUpperCount, int iLowerCount)
{
	if (iUpperIndex < 0 || iLowerIndex < 0)return INDEX_OUT_OF_RANGE;
	if (iUpperIndex >= iUpperCount) return INDEX_OUT_OF_RANGE;
	if (iLowerIndex >= iLowerCount)return INDEX_OUT_OF_RANGE;
	if (dValue < 0.0) return VALUE_LESS_THAN_MIN;
	pdMatrix[iUpperIndex][iLowerIndex] = dValue;
	return SUCCESS;
}