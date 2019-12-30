#include "pch.h"
#include "CMscnProblem.h"
#include <iostream>
#include <sstream>
#pragma warning(disable : 4996) //fopen warning

CMscnProblem::CMscnProblem() 
{
	//set default values
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
//INITIALIZE MATRICES HERE!!!
void CMscnProblem::vSetSuppliersCount(int iCount)
{
	//if(iCount<1)//ERROR
	i_suppliers_count = iCount;
}

void CMscnProblem::vSetFactoriesCount(int iCount)
{
	//if (iCount < 1)//ERROR
	i_factories_count = iCount;
}

void CMscnProblem::vSetWarehousesCount(int iCount)
{
	//if (iCount < 1)//ERROR
	i_warehouses_count = iCount;
}

void CMscnProblem::vSetShopsCount(int iCount)
{
	//if (iCount < 1)//ERROR
	i_shops_count = iCount;
}

bool CMscnProblem::bConstraintsSatisified(double *pdSolution)
{
	return false;
}

double CMscnProblem::dGetQuality(double *pdSolution)
{
	return d_calculate_shops_revenue() - d_calculate_usages_costs() - d_calculate_prod_trans_costs();
}

void CMscnProblem::vSaveProblemToFile(std::string cFileName)
{
	FILE* pf_problem = fopen(cFileName.c_str(), "w");
	if (pf_problem == NULL)return; //ERROR

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
}

void CMscnProblem::v_load_solution(double *pdSolution)
{
	int i_offset = 0;
	v_load_part_of_solution(pdSolution, pd_supp_to_fact_item_counts, i_offset, i_suppliers_count, i_factories_count);
	i_offset += i_suppliers_count * i_factories_count - 1;
	v_load_part_of_solution(pdSolution, pd_fact_to_ware_item_counts, i_offset, i_factories_count, i_warehouses_count);
	i_offset += i_factories_count * i_warehouses_count;
	v_load_part_of_solution(pdSolution, pd_ware_to_shop_item_counts, i_offset, i_warehouses_count, i_shops_count);
}

void CMscnProblem::v_load_part_of_solution(double *pdSolution, double** pdMatrix, int iOffsetValue, int iFstLoopCond, int iSndLoopCond)
{
	for (int ii = 0; ii < iFstLoopCond; ii++)
		for (int ij = 0; ij < iSndLoopCond; ij++)
			pdMatrix[ii][ij] = pdSolution[ii*iSndLoopCond + ij + iOffsetValue];
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

std::string CMscnProblem::s_convert_double_to_string(double dNumber)
{
	std::ostringstream o_convert;
	o_convert << dNumber;
	return o_convert.str();
}