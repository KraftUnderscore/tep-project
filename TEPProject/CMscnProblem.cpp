#include "pch.h"
#include "CMscnProblem.h"
#include <iostream>
#include <sstream>
#pragma warning(disable : 4996) //fopen warning

CMscnProblem::CMscnProblem() 
{
	i_suppliers_count = 0;
	i_factories_count = 0;
	i_warehouses_count = 0;
	i_shops_count =0;

	pd_suppliers_capacities = NULL;
	pd_factories_capacities = NULL;
	pd_warehouses_capacities = NULL;
	pd_shops_capacities = NULL;

	pd_supp_to_fact_costs = NULL;
	pd_fact_to_ware_costs = NULL;
	pd_ware_to_shop_costs = NULL;

	pd_supp_use_costs = NULL;
	pd_fact_use_costs = NULL;
	pd_ware_use_costs = NULL;

	pd_shop_revenues = NULL;

	pd_supp_prod_min_max = NULL;
	pd_fact_prod_min_max = NULL;
	pd_ware_prod_min_max = NULL;

	pd_supp_to_fact_item_counts = NULL;
	pd_fact_to_ware_item_counts = NULL;
	pd_ware_to_shop_item_counts = NULL;
};

CMscnProblem::~CMscnProblem()
{
	delete pd_suppliers_capacities;
	delete pd_factories_capacities;
	delete pd_warehouses_capacities;
	delete pd_shops_capacities;
	delete pd_supp_use_costs;
	delete pd_fact_use_costs;
	delete pd_ware_use_costs;
	delete pd_shop_revenues;
	v_delete_matrix(pd_supp_to_fact_costs, i_suppliers_count);
	v_delete_matrix(pd_fact_to_ware_costs, i_factories_count);
	v_delete_matrix(pd_ware_to_shop_costs, i_warehouses_count);
	v_delete_matrix(pd_supp_prod_min_max, i_suppliers_count);
	v_delete_matrix(pd_fact_prod_min_max, i_factories_count);
	v_delete_matrix(pd_ware_prod_min_max, i_warehouses_count);
	v_delete_matrix(pd_supp_to_fact_item_counts, i_suppliers_count);
	v_delete_matrix(pd_fact_to_ware_item_counts, i_factories_count);
	v_delete_matrix(pd_ware_to_shop_item_counts, i_warehouses_count);
}

int CMscnProblem::vSetSuppliersCount(int iCount)
{
	if (iCount < 1) return ERROR_VALUE_LESS_EQ_ZERO;
	i_suppliers_count = iCount;

	v_recreate_setter_arr_matrix(pd_suppliers_capacities, pd_supp_use_costs, pd_supp_to_fact_costs, pd_supp_to_fact_item_counts, pd_supp_prod_min_max, i_suppliers_count, i_factories_count);
	return SUCCESS;
}

int CMscnProblem::vSetFactoriesCount(int iCount)
{
	if (iCount < 1) return ERROR_VALUE_LESS_EQ_ZERO;
	i_factories_count = iCount;

	v_recreate_setter_arr_matrix(pd_factories_capacities, pd_fact_use_costs, pd_fact_to_ware_costs, pd_fact_to_ware_item_counts, pd_fact_prod_min_max, i_factories_count, i_warehouses_count);
	vSetSuppliersCount(i_suppliers_count);
	return SUCCESS;
}

int CMscnProblem::vSetWarehousesCount(int iCount)
{
	if (iCount < 1) return ERROR_VALUE_LESS_EQ_ZERO;
	i_warehouses_count = iCount;

	v_recreate_setter_arr_matrix(pd_warehouses_capacities, pd_ware_use_costs, pd_ware_to_shop_costs, pd_ware_to_shop_item_counts, pd_ware_prod_min_max, i_warehouses_count, i_shops_count);
	vSetFactoriesCount(i_factories_count);
	return SUCCESS;
}

int CMscnProblem::vSetShopsCount(int iCount)
{
	if (iCount < 1) return ERROR_VALUE_LESS_EQ_ZERO;
	i_shops_count = iCount;

	v_recreate_setter_arr_matrix(pd_shops_capacities, pd_shop_revenues, NULL, NULL, NULL, i_shops_count, 0);
	vSetWarehousesCount(i_warehouses_count);
	return SUCCESS;
}
//might make helper function here
int CMscnProblem::vSetSuppCap(double dCap, int iSupplierIndex)
{
	if (iSupplierIndex < 0) return ERROR_VALUE_LESS_ZERO;
	if (dCap <= 0.0)return ERROR_VALUE_LESS_EQ_ZERO;
	if (iSupplierIndex >= i_suppliers_count) return ERROR_INDEX_OUT_OF_RANGE;
	pd_suppliers_capacities[iSupplierIndex] = dCap;
}

int CMscnProblem::vSetFactCap(double dCap, int iFactoryIndex)
{
	if (iFactoryIndex < 0) return ERROR_VALUE_LESS_ZERO;
	if (dCap <= 0.0)return ERROR_VALUE_LESS_EQ_ZERO;
	if (iFactoryIndex >= i_factories_count) return ERROR_INDEX_OUT_OF_RANGE;
	pd_factories_capacities[iFactoryIndex] = dCap;
}

int CMscnProblem::vSetWareCap(double dCap, int iWarehouseIndex)
{
	if (iWarehouseIndex < 0) return ERROR_VALUE_LESS_ZERO;
	if (dCap <= 0.0)return ERROR_VALUE_LESS_EQ_ZERO;
	if (iWarehouseIndex >= i_warehouses_count) return ERROR_INDEX_OUT_OF_RANGE;
	pd_warehouses_capacities[iWarehouseIndex] = dCap;
}

int CMscnProblem::vSetShopCap(double dCap, int iShopIndex)
{
	if (iShopIndex < 0) return ERROR_VALUE_LESS_ZERO;
	if (dCap <= 0.0)return ERROR_VALUE_LESS_EQ_ZERO;
	if (iShopIndex >= i_shops_count) return ERROR_INDEX_OUT_OF_RANGE;
	pd_shops_capacities[iShopIndex] = dCap;
}
//helper here too, much repetition, not very wow
int CMscnProblem::vSetSuppToFactCost(double dCost, int iSupplierIndex, int iFactoryIndex)
{
	if (iSupplierIndex < 0 || iFactoryIndex < 0)return ERROR_VALUE_LESS_ZERO;
	if (iSupplierIndex >= i_suppliers_count) return ERROR_INDEX_OUT_OF_RANGE;
	if (iFactoryIndex >= i_factories_count)return ERROR_INDEX_OUT_OF_RANGE;
	if (dCost <= 0.0) return ERROR_VALUE_LESS_EQ_ZERO;
	pd_supp_to_fact_costs[iSupplierIndex][iFactoryIndex] = dCost;
}

int CMscnProblem::vSetFactToWareCost(double dCost, int iFactoryIndex, int iWarehouseIndex)
{
	if (iFactoryIndex < 0 || iWarehouseIndex < 0)return ERROR_VALUE_LESS_ZERO;
	if (iFactoryIndex >= i_factories_count) return ERROR_INDEX_OUT_OF_RANGE;
	if (iWarehouseIndex >= i_warehouses_count)return ERROR_INDEX_OUT_OF_RANGE;
	if (dCost <= 0.0) return ERROR_VALUE_LESS_EQ_ZERO;
	pd_fact_to_ware_costs[iFactoryIndex][iWarehouseIndex] = dCost;
}

int CMscnProblem::vSetWareToShopCost(double dCost, int iWarehouseIndex, int iShopIndex)
{
	if (iWarehouseIndex < 0 || iShopIndex < 0)return ERROR_VALUE_LESS_ZERO;
	if (iWarehouseIndex >= i_warehouses_count) return ERROR_INDEX_OUT_OF_RANGE;
	if (iShopIndex >= i_shops_count)return ERROR_INDEX_OUT_OF_RANGE;
	if (dCost <= 0.0) return ERROR_VALUE_LESS_EQ_ZERO;
	pd_ware_to_shop_costs[iWarehouseIndex][iShopIndex] = dCost;
}

//helper to optimize code
bool CMscnProblem::bConstraintsSatisified(double *pdSolution, int* iError)	
{
	int i_load_result = v_load_solution(pdSolution);
	if (i_load_result != SUCCESS)
	{
		if(iError!=NULL)
			*iError = i_load_result;
		return false;
	}

	for (int ii = 0; ii < i_factories_count; ii++)
	{
		double dSuppGoods = 0.0;
		for (int ij = 0; ij < i_suppliers_count; ij++)
			dSuppGoods += pd_supp_to_fact_item_counts[ij][ii];

		double dFactGoods = 0.0;
		for (int ij = 0; ij < i_warehouses_count; ij++)
		{
			dFactGoods += pd_fact_to_ware_item_counts[ii][ij];
			if (dFactGoods > dSuppGoods) return false;
		}
	}

	for (int ii = 0; ii < i_warehouses_count; ii++)
	{
		double dFactGoods = 0.0;
		for (int ij = 0; ij < i_factories_count; ij++)
			dFactGoods += pd_supp_to_fact_item_counts[ij][ii];

		double dWareGoods = 0.0;
		for (int ij = 0; ij < i_shops_count; ij++)
		{
			dWareGoods += pd_fact_to_ware_item_counts[ii][ij];
			if (dWareGoods > dFactGoods) return false;
		}
	}

	if (iError != NULL)
		*iError = SUCCESS;

	return b_capacity_check(pd_supp_to_fact_item_counts, pd_suppliers_capacities, i_suppliers_count, i_factories_count) &&
		b_capacity_check(pd_fact_to_ware_item_counts, pd_factories_capacities, i_factories_count, i_warehouses_count) &&
		b_capacity_check(pd_ware_to_shop_item_counts, pd_warehouses_capacities, i_warehouses_count, i_shops_count) &&
		b_capacity_check(pd_ware_to_shop_item_counts, pd_shops_capacities, i_warehouses_count, i_shops_count);

}

double CMscnProblem::dGetQuality(double *pdSolution, int* iError)
{
	int i_result = v_load_solution(pdSolution);
	if (i_result != SUCCESS)
	{
		if (iError != NULL)
			*iError = i_result;
		return 0.0;
	}

	if (iError != NULL)
		*iError = SUCCESS;

	return d_calculate_shops_revenue() - d_calculate_usages_costs() - d_calculate_prod_trans_costs();
}

//NEEDS IMPLEMENTATION SOMEHOW ALSO ERRORS(v_add_to_file!!!)
int CMscnProblem::vLoadProblemFromFile(std::string sFileName)
{
	FILE* pf_problem = fopen(sFileName.c_str(), "r");
	if (pf_problem == NULL)return ERROR_FAILED_OPENING_FILE; //ERROR
	
	fclose(pf_problem);
	return SUCCESS;
}

int CMscnProblem::vSaveProblemToFile(std::string sFileName)
{
	FILE* pf_problem = fopen(sFileName.c_str(), "w");
	if (pf_problem == NULL)return ERROR_FAILED_OPENING_FILE;

	fprintf(pf_problem, "D %d", i_suppliers_count);
	fprintf(pf_problem, "\nF %d", i_factories_count);
	fprintf(pf_problem, "\nM %d", i_warehouses_count);
	fprintf(pf_problem, "\nS %d", i_shops_count);

	fprintf(pf_problem, "\nsd\n");
	v_add_pd_array_to_file(pf_problem, pd_suppliers_capacities, i_suppliers_count);

	fprintf(pf_problem, "\nsf\n");
	v_add_pd_array_to_file(pf_problem, pd_factories_capacities, i_factories_count);

	fprintf(pf_problem, "\nsm\n");
	v_add_pd_array_to_file(pf_problem, pd_warehouses_capacities, i_warehouses_count);

	fprintf(pf_problem, "\nss\n");
	v_add_pd_array_to_file(pf_problem, pd_shops_capacities, i_shops_count);

	fprintf(pf_problem, "\ncd\n");
	v_add_pd_matrix_to_file(pf_problem, pd_supp_to_fact_costs, i_suppliers_count, i_factories_count);

	fprintf(pf_problem, "\ncf\n");
	v_add_pd_matrix_to_file(pf_problem, pd_fact_to_ware_costs, i_factories_count, i_warehouses_count);

	fprintf(pf_problem, "\ncm\n");
	v_add_pd_matrix_to_file(pf_problem, pd_ware_to_shop_costs, i_warehouses_count, i_shops_count);

	fprintf(pf_problem, "\nud\n");
	v_add_pd_array_to_file(pf_problem, pd_supp_use_costs, i_suppliers_count);

	fprintf(pf_problem, "\nuf\n");
	v_add_pd_array_to_file(pf_problem, pd_fact_use_costs, i_factories_count);

	fprintf(pf_problem, "\num\n");
	v_add_pd_array_to_file(pf_problem, pd_ware_use_costs, i_warehouses_count);

	fprintf(pf_problem, "\np\n");
	v_add_pd_array_to_file(pf_problem, pd_shop_revenues, i_shops_count);

	fprintf(pf_problem, "\nxdminmax\n");
	v_add_pd_matrix_to_file(pf_problem, pd_supp_prod_min_max, i_suppliers_count, i_factories_count * 2);

	fprintf(pf_problem, "\nxfminmax\n");
	v_add_pd_matrix_to_file(pf_problem, pd_fact_prod_min_max, i_factories_count, i_warehouses_count * 2);

	fprintf(pf_problem, "\nxmminmax\n");
	v_add_pd_matrix_to_file(pf_problem, pd_ware_prod_min_max, i_warehouses_count, i_shops_count * 2);

	fclose(pf_problem);
	return SUCCESS;
}

int CMscnProblem::vSaveSolutionToFile(std::string sFileName)
{
	FILE* pf_problem = fopen(sFileName.c_str(), "w");
	if (pf_problem == NULL)return ERROR_FAILED_OPENING_FILE;

	fprintf(pf_problem, "D %d", i_suppliers_count);
	fprintf(pf_problem, "\nF %d", i_factories_count);
	fprintf(pf_problem, "\nM %d", i_warehouses_count);
	fprintf(pf_problem, "\nS %d", i_shops_count);

	fprintf(pf_problem, "\nxd\n");
	v_add_pd_matrix_to_file(pf_problem, pd_supp_to_fact_item_counts, i_suppliers_count, i_factories_count);

	fprintf(pf_problem, "\nxf\n");
	v_add_pd_matrix_to_file(pf_problem, pd_fact_to_ware_item_counts, i_factories_count, i_warehouses_count);

	fprintf(pf_problem, "\nxm\n");
	v_add_pd_matrix_to_file(pf_problem, pd_ware_to_shop_item_counts, i_warehouses_count, i_shops_count);

	fclose(pf_problem);
	return SUCCESS;
}

int CMscnProblem::v_load_solution(double *pdSolution)
{
	if (pdSolution == NULL) return NULL_SOLUTION;
	if (i_suppliers_count <= 0 || i_factories_count <= 0 || i_warehouses_count <= 0 || i_shops_count <= 0) return ERROR_VALUE_LESS_EQ_ZERO;
	int i_result;
	int i_offset = 0;
	i_result = v_load_part_of_solution(pdSolution, pd_supp_to_fact_item_counts, pd_supp_prod_min_max, i_offset, i_suppliers_count, i_factories_count);
	if (i_result != SUCCESS) return i_result;
	i_offset += i_suppliers_count * i_factories_count - 1;
	v_load_part_of_solution(pdSolution, pd_fact_to_ware_item_counts, pd_fact_prod_min_max, i_offset, i_factories_count, i_warehouses_count);
	if (i_result != SUCCESS) return i_result;
	i_offset += i_factories_count * i_warehouses_count;
	v_load_part_of_solution(pdSolution, pd_ware_to_shop_item_counts, pd_ware_prod_min_max, i_offset, i_warehouses_count, i_shops_count);
	return i_result;
}

int CMscnProblem::v_load_part_of_solution(double *pdSolution, double** pdMatrix, double** pdUpperToLowerMinMax, int iOffsetValue, int iFstLoopCond, int iSndLoopCond)
{
	for (int ii = 0; ii < iFstLoopCond; ii++)
		for (int ij = 0; ij < iSndLoopCond; ij++)
		{
			double d_value = pdSolution[ii*iSndLoopCond + ij + iOffsetValue];
			if (d_value < pdUpperToLowerMinMax[ii][ij]) return ERROR_VALUE_LESS_THAN_MIN;
			if (d_value > pdUpperToLowerMinMax[ii][ij + 1]) return ERROR_VALUE_GREATER_THAN_MAX;
			pdMatrix[ii][ij] = d_value;
		}

	return SUCCESS;
}

double** CMscnProblem::v_create_matrix(int iSizeX, int iSizeY)
{
	double** d_result = new double*[iSizeX];
	for (int ii = 0; ii < iSizeX; ii++)
		d_result[ii] = new double[iSizeY];
	return d_result;
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
		double dGoods = 0.0;
		for (int ij = 0; ij < iLowerCount; ij++)
		{
			dGoods += pdProducedGoods[ii][ij];
			if (dGoods > pdCapacities[iUpperCount])return false;
		}
	}
	return true;		
}

double CMscnProblem::d_calculate_shops_revenue()
{
	double d_result = 0.0;
	for (int im = 0; im < i_warehouses_count; im++)
		for (int is = 0; is < i_shops_count; is++)
			d_result += pd_shop_revenues[is] * pd_ware_to_shop_item_counts[im][is];

	return d_result;
}

double CMscnProblem::d_calculate_usages_costs()
{
	double d_result = 0.0;
	d_result += d_calculate_usage_cost(pd_supp_to_fact_item_counts, pd_supp_use_costs, i_suppliers_count, i_factories_count);
	d_result += d_calculate_usage_cost(pd_fact_to_ware_item_counts, pd_fact_use_costs, i_factories_count, i_warehouses_count);
	d_result += d_calculate_usage_cost(pd_ware_to_shop_item_counts, pd_ware_use_costs, i_warehouses_count, i_shops_count);
	return d_result;
}

double CMscnProblem::d_calculate_usage_cost(double** pdMatrix, double* pdArray, int iFstLoopCond, int iSndLoopCond)
{
	double d_result = 0.0;
	for (int iFst = 0; iFst < iFstLoopCond; iFst++)
		for (int iSnd = 0; iSnd < iSndLoopCond; iSnd++)
			if (pdMatrix[iFst][iSnd] > 0)
				d_result += pdArray[iSnd] * pdMatrix[iFst][iSnd];

	return d_result;
}

double CMscnProblem::d_calculate_prod_trans_costs()
{
	double d_result = 0.0;
	d_result += d_calculate_prod_trans_cost(pd_supp_to_fact_costs, pd_supp_to_fact_item_counts, i_suppliers_count, i_factories_count);
	d_result += d_calculate_prod_trans_cost(pd_fact_to_ware_costs, pd_fact_to_ware_item_counts, i_factories_count, i_warehouses_count);
	d_result += d_calculate_prod_trans_cost(pd_ware_to_shop_costs, pd_ware_to_shop_item_counts, i_warehouses_count, i_shops_count);
	return d_result;
}

double CMscnProblem::d_calculate_prod_trans_cost(double** pdFstMatrix, double** pdSndMatrix, int iFstLoopCond, int iSndLoopCond)
{
	double d_result = 0.0;
	for (int iFst = 0; iFst < iFstLoopCond; iFst++)
		for (int iSnd = 0; iSnd < iSndLoopCond; iSnd++)
			d_result += pdSndMatrix[iFst][iSnd] * pdFstMatrix[iFst][iSnd];

	return d_result;
}

void CMscnProblem::v_add_pd_array_to_file(FILE* fFile, double *pdArray, int iArrayLength)
{
	if (pdArray == NULL)fprintf(fFile, "NULL");
	else
		for (int ii = 0; ii < iArrayLength; ii++)
			fprintf(fFile, "%d ", pdArray[ii]);
}

void CMscnProblem::v_add_pd_matrix_to_file(FILE *fFile, double** pdMatrix, int iSizeX, int iSizeY)
{
	if (pdMatrix == NULL)fprintf(fFile, "NULL");
	else
		for (int ii = 0; ii < iSizeX; ii++)
		{
			for (int ij = 0; ij < iSizeY; ij++)
				fprintf(fFile, "%d ", pdMatrix[ii][ij]);
			
			fprintf(fFile, "\n");
		}
}

double CMscnProblem::d_convert_string_to_double(std::string sNumber)
{
	double d_number;
	if (!(std::istringstream(sNumber) >> d_number)) d_number = 0.0;	//ERROR zamiast 0.0
	return d_number;
}

void CMscnProblem::v_recreate_setter_arr_matrix(double* pdCapacity, double* pdUseCosts, double** pdUpperToLowerCost, double** pdUpperToLowerMinMax, double** pdUpperToLowerItems, int iUpperCount, int iLowerCount)
{
	if(pdCapacity != NULL)
		delete pdCapacity;
	pdCapacity = new double[iUpperCount];

	if(pdUseCosts!=NULL)
		delete pdUseCosts;
	pdUseCosts = new double[iUpperCount];

	v_delete_matrix(pdUpperToLowerCost, iUpperCount);
	v_delete_matrix(pdUpperToLowerItems, iUpperCount);
	v_delete_matrix(pdUpperToLowerMinMax, iUpperCount);

	if (iLowerCount > 0)
	{
		pdUpperToLowerCost = v_create_matrix(iUpperCount, iLowerCount);
		pdUpperToLowerItems = v_create_matrix(iUpperCount, iLowerCount);
		pdUpperToLowerMinMax = v_create_matrix(iUpperCount, iLowerCount * 2);
	}//else iLowerCount hasn't been set yet.
}