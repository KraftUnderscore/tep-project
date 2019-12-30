#include "pch.h"
#include "CMscnProblem.h"
#include <iostream>

CMscnProblem::CMscnProblem() 
{

};

void CMscnProblem::vSetSuppliersCount(int iCount)
{
	i_suppliers_count = iCount;
}

void CMscnProblem::vSetFactoriesCount(int iCount)
{
	i_factories_count = iCount;
}

void CMscnProblem::vSetWarehousesCount(int iCount)
{
	i_warehouses_count = iCount;
}

void CMscnProblem::vSetShopsCount(int iCount)
{
	i_shops_count = iCount;
}

bool CMscnProblem::bConstraintsSatisified(double *pdSolution)
{

}

double CMscnProblem::dGetQuality(double *pdSolution)
{
	return d_calculate_shops_revenue() - d_calculate_usages_costs() - d_calculate_prod_trans_costs();
}

void CMscnProblem::v_load_solution(double *pdSolution)
{
	v_load_part_of_solution(pdSolution, pd_supp_to_fact_item_counts, i_suppliers_count, i_factories_count);
	v_load_part_of_solution(pdSolution, pd_fact_to_ware_item_counts, i_factories_count, i_warehouses_count);
	v_load_part_of_solution(pdSolution, pd_ware_to_shop_item_counts, i_warehouses_count, i_shops_count);
}
void CMscnProblem::v_load_part_of_solution(double *pdSolution, double** pdMatrix, int iFstLoopCond, int iSndLoopCond)
{
	if (pdMatrix != NULL) v_delete_matrix(pdMatrix, iFstLoopCond);
	pdMatrix = v_create_matrix(iFstLoopCond, iSndLoopCond);

	for (int ii = 0; ii < iFstLoopCond; ii++)
		for (int ij = 0; ij < iSndLoopCond; ij++)
			pdMatrix[ii][ij] = pdSolution[ii*iSndLoopCond + ij];
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
	for (int ii = 0; ii < iSizeX; ii++)
		delete dMatrix[ii];
	delete dMatrix;
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
