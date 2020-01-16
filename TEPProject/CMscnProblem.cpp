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
	i_shop_count = 0;
};

int CMscnProblem::iSetSuppliersCount(int iCount)
{
	if (iCount < COUNT_MIN) return COUNT_LESS_THAN_MIN;
	int i_result;
	i_supp_count = iCount;
	i_result = pd_supp_caps.iSetSize(iCount);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_supp_use_costs.iSetSize(iCount);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_supp_to_fact_costs.iSetSize(i_supp_count, i_fact_count);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_supp_to_fact_goods.iSetSize(i_supp_count, i_fact_count);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_supp_to_fact_goods_min.iSetSize(i_supp_count, i_fact_count);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_supp_to_fact_goods_max.iSetSize(i_supp_count, i_fact_count);
	if (i_result != SUCCESS)return i_result;
	return SUCCESS;
}

int CMscnProblem::iSetFactoriesCount(int iCount)
{
	if (iCount < COUNT_MIN) return COUNT_LESS_THAN_MIN;
	int i_result;
	i_fact_count = iCount;
	i_result = pd_fact_caps.iSetSize(iCount);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_fact_use_costs.iSetSize(iCount);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_fact_to_ware_costs.iSetSize(i_fact_count, i_ware_count);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_fact_to_ware_goods.iSetSize(i_fact_count, i_ware_count);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_fact_to_ware_goods_min.iSetSize(i_fact_count, i_ware_count);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_fact_to_ware_goods_max.iSetSize(i_fact_count, i_ware_count);
	if (i_result != SUCCESS)return i_result;
	return SUCCESS;
}

int CMscnProblem::iSetWarehousesCount(int iCount)
{
	if (iCount < COUNT_MIN) return COUNT_LESS_THAN_MIN;
	int i_result;
	i_ware_count = iCount;
	i_result = pd_ware_caps.iSetSize(iCount);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_ware_use_costs.iSetSize(iCount);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_ware_to_shop_costs.iSetSize(i_ware_count, i_shop_count);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_ware_to_shop_goods.iSetSize(i_ware_count, i_shop_count);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_ware_to_shop_goods_min.iSetSize(i_ware_count, i_shop_count);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_ware_to_shop_goods_max.iSetSize(i_ware_count, i_shop_count);
	if (i_result != SUCCESS)return i_result;
	return SUCCESS;
}

int CMscnProblem::iSetShopsCount(int iCount)
{
	if (iCount < COUNT_MIN) return COUNT_LESS_THAN_MIN;
	int i_result;
	i_shop_count = iCount;
	i_result = pd_shop_caps.iSetSize(iCount);
	if (i_result != SUCCESS)return i_result;
	i_result = pd_shop_revenues.iSetSize(iCount);
	return i_result;
}

int CMscnProblem::iSetSuppCap(double dCap, int iIndex)
{
	if (dCap < 0.0)return NEGATIVE_CAPACITY;
	return pd_supp_caps.iSetValue(dCap, iIndex);
}

int CMscnProblem::iSetFactCap(double dCap, int iIndex)
{
	if (dCap < 0.0)return NEGATIVE_CAPACITY;
	return pd_fact_caps.iSetValue(dCap, iIndex);
}

int CMscnProblem::iSetWareCap(double dCap, int iIndex)
{
	if (dCap < 0.0)return NEGATIVE_CAPACITY;
	return pd_ware_caps.iSetValue(dCap, iIndex);
}

int CMscnProblem::iSetShopCap(double dCap, int iIndex)
{
	if (dCap < 0.0)return NEGATIVE_CAPACITY;
	return pd_shop_caps.iSetValue(dCap, iIndex);
}

int CMscnProblem::iSetSuppToFactCost(double dCost, int iUpperIndex, int iLowerIndex)
{
	return pd_supp_to_fact_costs.iSetValue(dCost, iUpperIndex, iLowerIndex);
}

int CMscnProblem::iSetFactToWareCost(double dCost, int iUpperIndex, int iLowerIndex)
{
	return pd_fact_to_ware_costs.iSetValue(dCost, iUpperIndex, iLowerIndex);
}

int CMscnProblem::iSetWareToShopCost(double dCost, int iUpperIndex, int iLowerIndex)
{
	return pd_ware_to_shop_costs.iSetValue(dCost, iUpperIndex, iLowerIndex);
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
			dSuppGoods += pd_supp_to_fact_goods.dGetValue(ii, ij, i_result);

		double dFactGoods = 0.0;
		for (int ij = 0; ij < i_ware_count; ij++)
		{
			dFactGoods += pd_fact_to_ware_goods.dGetValue(ii, ij, i_result);
			if (dFactGoods > dSuppGoods) return false;
		}
	}
	if (i_result != SUCCESS)
	{
		if (iError != NULL)
			*iError = i_result;
		return false;
	}
	for (int ii = 0; ii < i_ware_count; ii++)
	{
		double dFactGoods = 0.0;
		for (int ij = 0; ij < i_fact_count; ij++)
			dFactGoods += pd_supp_to_fact_goods.dGetValue(ii, ij, i_result);

		double dWareGoods = 0.0;
		for (int ij = 0; ij < i_shop_count; ij++)
		{
			dWareGoods += pd_fact_to_ware_goods.dGetValue(ii, ij, i_result);
			if (dWareGoods > dFactGoods) return false;
		}
	}
	if (i_result != SUCCESS)
	{
		if (iError != NULL)
			*iError = i_result;
		return false;
	}
	if (iError != NULL)
		*iError = SUCCESS;

	bool b1 = b_capacity_check(&pd_supp_to_fact_goods, &pd_supp_caps, i_supp_count, i_fact_count);
	bool b2 = b_capacity_check(&pd_fact_to_ware_goods, &pd_fact_caps, i_fact_count, i_ware_count);
	bool b3 = b_capacity_check(&pd_ware_to_shop_goods, &pd_ware_caps, i_ware_count, i_shop_count);
	bool b4 = b_capacity_check(&pd_ware_to_shop_goods, &pd_shop_caps, i_ware_count, i_shop_count);
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

	i_result = i_get_array_from_file(pf_problem, &pd_supp_caps, i_supp_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, &pd_fact_caps, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, &pd_ware_caps, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, &pd_shop_caps, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_matrix_from_file(pf_problem, &pd_supp_to_fact_costs, i_supp_count, i_fact_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_matrix_from_file(pf_problem, &pd_fact_to_ware_costs, i_fact_count, i_ware_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_matrix_from_file(pf_problem, &pd_ware_to_shop_costs, i_ware_count, i_shop_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, &pd_supp_use_costs, i_supp_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, &pd_fact_use_costs, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, &pd_ware_use_costs, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	i_result = i_get_array_from_file(pf_problem, &pd_shop_revenues, i_shop_count);
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

	i_result = i_get_matrix_from_file(pf_problem, &pd_supp_to_fact_goods, i_supp_count, i_fact_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	i_result = i_get_matrix_from_file(pf_problem, &pd_fact_to_ware_goods, i_fact_count, i_ware_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	i_result = i_get_matrix_from_file(pf_problem, &pd_ware_to_shop_goods, i_ware_count, i_shop_count, SKIP_4_CHAR);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}

	double* pd_solution = new double[i_supp_count_read*i_fact_count_read + i_fact_count_read * i_ware_count_read + i_ware_count_read * i_shop_count_read];
	int i_offset = 0;
	for (int ii = 0; ii < i_supp_count_read; ii++)
		for (int ij = 0; ij < i_fact_count_read; ij++)
			pd_solution[ii*i_fact_count_read + ij + i_offset] = pd_supp_to_fact_goods.dGetValue(ii, ij, i_result);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	i_offset += i_supp_count_read * i_fact_count_read;
	for (int ii = 0; ii < i_fact_count_read; ii++)
		for (int ij = 0; ij < i_ware_count_read; ij++)
			pd_solution[ii*i_ware_count_read + ij + i_offset] = pd_fact_to_ware_goods.dGetValue(ii, ij, i_result);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	i_offset += i_fact_count_read * i_ware_count_read;
	for (int ii = 0; ii < i_ware_count_read; ii++)
		for (int ij = 0; ij < i_shop_count_read; ij++)
			pd_solution[ii*i_shop_count_read + ij + i_offset] = pd_ware_to_shop_goods.dGetValue(ii, ij, i_result);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
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
	i_result = i_add_pc_array_to_file(pf_problem, &pd_supp_caps, i_supp_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nsf\n");
	i_result = i_add_pc_array_to_file(pf_problem, &pd_fact_caps, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nsm\n");
	i_result = i_add_pc_array_to_file(pf_problem, &pd_ware_caps, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nss\n");
	i_result = i_add_pc_array_to_file(pf_problem, &pd_shop_caps, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\ncd\n");
	i_result = i_add_pc_matrix_to_file(pf_problem, &pd_supp_to_fact_costs, i_supp_count, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\ncf\n");
	i_result = i_add_pc_matrix_to_file(pf_problem, &pd_fact_to_ware_costs, i_fact_count, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\ncm\n");
	i_result = i_add_pc_matrix_to_file(pf_problem, &pd_ware_to_shop_costs, i_ware_count, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nud\n");
	i_result = i_add_pc_array_to_file(pf_problem, &pd_supp_use_costs, i_supp_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nuf\n");
	i_result = i_add_pc_array_to_file(pf_problem, &pd_fact_use_costs, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\num\n");
	i_result = i_add_pc_array_to_file(pf_problem, &pd_ware_use_costs, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\np\n");
	i_result = i_add_pc_array_to_file(pf_problem, &pd_shop_revenues, i_shop_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxdminmax\n");
	i_result = i_add_pc_matrix_to_file(pf_problem, &pd_supp_to_fact_goods_min_max, i_supp_count, i_fact_count * 2);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxfminmax\n");
	i_result = i_add_pc_matrix_to_file(pf_problem, &pd_fact_to_ware_goods_min_max, i_fact_count, i_ware_count * 2);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxmminmax\n");
	i_result = i_add_pc_matrix_to_file(pf_problem, &pd_ware__to_shop_goods_min_max, i_ware_count, i_shop_count * 2);
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
	i_result = i_add_pc_matrix_to_file(pf_problem, &pd_supp_to_fact_goods, i_supp_count, i_fact_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxf\n");
	i_result = i_add_pc_matrix_to_file(pf_problem, &pd_fact_to_ware_goods, i_fact_count, i_ware_count);
	if (i_result != SUCCESS)
	{
		fclose(pf_problem);
		return i_result;
	}
	fprintf(pf_problem, "\nxm\n");
	i_result = i_add_pc_matrix_to_file(pf_problem, &pd_ware_to_shop_goods, i_ware_count, i_shop_count);
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
	i_result = i_load_part_of_solution(pdSolution, &pd_supp_to_fact_goods, &pd_supp_to_fact_goods_min, &pd_supp_to_fact_goods_max, i_solution_offset, i_supp_count, i_fact_count);
	if (i_result != SUCCESS) return i_result;
	i_solution_offset += i_supp_count * i_fact_count - 1;
	i_result = i_load_part_of_solution(pdSolution, &pd_fact_to_ware_goods, &pd_fact_to_ware_goods_min, &pd_fact_to_ware_goods_max, i_solution_offset, i_fact_count, i_ware_count);
	if (i_result != SUCCESS) return i_result;
	i_solution_offset += i_fact_count * i_ware_count;
	i_result = i_load_part_of_solution(pdSolution, &pd_ware_to_shop_goods, &pd_ware_to_shop_goods_min, &pd_ware_to_shop_goods_max, i_solution_offset, i_ware_count, i_shop_count);
	return i_result;
}

int CMscnProblem::i_load_part_of_solution(double *pdSolution, CMatrix* pcUpperToLowerGoods, CMatrix* pcUpperToLowerMin, CMatrix* pcUpperToLowerMax, int iSolutionOffset, int iUpperCount, int iLowerCount)
{
	int i_result;
	for (int ii = 0; ii < iUpperCount; ii++)
		for (int ij = 0; ij < iLowerCount; ij++)
		{
			double d_value = pdSolution[ii*iLowerCount + ij + iSolutionOffset];
			if (d_value < pcUpperToLowerMin->dGetValue(ii, ij, i_result)) return VALUE_LESS_THAN_MIN;
			if (d_value > pcUpperToLowerMax->dGetValue(ii, ij, i_result)) return VALUE_GREATER_THAN_MAX;
			if (i_result != SUCCESS)return i_result;
			pcUpperToLowerGoods->iSetValue(d_value, ii, ij);
			if (i_result != SUCCESS)return i_result;
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

bool CMscnProblem::b_capacity_check(CMatrix* pcProducedGoods, CTable* pcCapacities, int iUpperCount, int iLowerCount)
{
	int i_result;
	for (int ii = 0; ii < iUpperCount; ii++)
	{
		double d_goods = 0.0;
		for (int ij = 0; ij < iLowerCount; ij++)
		{
			d_goods += pcProducedGoods->dGetValue(ii, ij, i_result);
			if (d_goods > pcCapacities->dGetValue(ii, i_result))return false;
		}
	}
	return true;		
}

double CMscnProblem::d_calculate_shops_revenue()
{
	double d_result = 0.0;
	int i_result;
	for (int ii = 0; ii < i_ware_count; ii++)
		for (int ij = 0; ij < i_shop_count; ij++)
			d_result += pd_shop_revenues.dGetValue(ij, i_result)  * pd_ware_to_shop_goods.dGetValue(ii, ij, i_result);

	return d_result;
}

double CMscnProblem::d_calculate_usages_costs()
{
	double d_result = 0.0;
	d_result += d_calculate_usage_cost(&pd_supp_to_fact_goods, &pd_supp_use_costs, i_supp_count, i_fact_count);
	d_result += d_calculate_usage_cost(&pd_fact_to_ware_goods, &pd_fact_use_costs, i_fact_count, i_ware_count);
	d_result += d_calculate_usage_cost(&pd_ware_to_shop_goods, &pd_ware_use_costs, i_ware_count, i_shop_count);
	return d_result;
}

double CMscnProblem::d_calculate_usage_cost(CMatrix* pcUpperToLowerGoods, CTable* pcUsageCosts, int iUpperCount, int iLowerCount)
{
	double d_result = 0.0;
	int i_result;
	for (int ii = 0; ii < iUpperCount; ii++)
		for (int ij = 0; ij < iLowerCount; ij++)
			if (pcUpperToLowerGoods->dGetValue(ii, ij, i_result) > 0)
				d_result += pcUsageCosts->dGetValue(ij, i_result) * pcUpperToLowerGoods->dGetValue(ii, ij, i_result);

	return d_result;
}

double CMscnProblem::d_calculate_upp_to_low_costs()
{
	double d_result = 0.0;
	d_result += d_calculate_upp_to_low_cost(&pd_supp_to_fact_costs, &pd_supp_to_fact_goods, i_supp_count, i_fact_count);
	d_result += d_calculate_upp_to_low_cost(&pd_fact_to_ware_costs, &pd_fact_to_ware_goods, i_fact_count, i_ware_count);
	d_result += d_calculate_upp_to_low_cost(&pd_ware_to_shop_costs, &pd_ware_to_shop_goods, i_ware_count, i_shop_count);
	return d_result;
}

double CMscnProblem::d_calculate_upp_to_low_cost(CMatrix* pcUpperToLowerCosts, CMatrix* pcUpperToLowerGoods, int iUpperCount, int iLowerCount)
{
	double d_result = 0.0;
	int i_result;
	for (int ii = 0; ii < iUpperCount; ii++)
		for (int ij = 0; ij < iLowerCount; ij++)
			d_result += pcUpperToLowerGoods->dGetValue(ii, ij, i_result) * pcUpperToLowerCosts->dGetValue(ii, ij, i_result);

	return d_result;
}

int CMscnProblem::i_add_pc_array_to_file(FILE* fFile, CTable* pcArray, int iArrayLength)
{
	int i_result;
	for (int ii = 0; ii < iArrayLength; ii++)
	{
		int i_val = pcArray->dGetValue(ii, i_result);
		if (i_result != SUCCESS)return i_result;
		fprintf(fFile, "%d ", i_val);
	}
	return SUCCESS;
}

int CMscnProblem::i_add_pc_matrix_to_file(FILE *fFile, CMatrix* pcMatrix, int iSizeX, int iSizeY)
{
	int i_result;
	double d_val;
	for (int ii = 0; ii < iSizeX; ii++)
	{
		for (int ij = 0; ij < iSizeY; ij++)
		{
			d_val = pcMatrix->dGetValue(ii, ij, i_result);
			if (i_result != SUCCESS)return i_result;
			fprintf(fFile, "%d ", d_val);
		}
		fprintf(fFile, "\n");
	}
	return SUCCESS;
}

int CMscnProblem::i_get_array_from_file(FILE *pfFile, CTable* pcArray, int iArrayLength) 
{
	double d_read_value;
	int i_result;
	fseek(pfFile, 4, SEEK_CUR);
	std::cout << "\nreading array:\n";
	for (int ii = 0; ii < iArrayLength; ii++)
	{
		fscanf(pfFile, "%lf", &d_read_value);
		std::cout << d_read_value << " ";
		i_result = pcArray->iSetValue(d_read_value, ii);
		if (i_result != SUCCESS) return i_result;
	}
	return SUCCESS;
}

int CMscnProblem::i_get_matrix_from_file(FILE *pfFile, CMatrix* pcMatrix, int iSizeX, int iSizeY, int iFileOffset)
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
			i_result = pcMatrix->iSetValue(d_read_value, ii, ij);
			if (i_result != SUCCESS) return i_result;
		}
		std::cout << "\n";
	}
	return SUCCESS;
}