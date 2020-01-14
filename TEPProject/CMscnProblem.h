#include <iostream>
#pragma once

#define SUCCESS 1000000
#define ERROR_VALUE_LESS_ZERO 1000001
#define ERROR_VALUE_LESS_EQ_ZERO 1000002
#define ERROR_INDEX_OUT_OF_RANGE 1000003
#define ERROR_FAILED_OPENING_FILE 1000004
#define ERROR_VALUE_LESS_THAN_MIN 1000005
#define ERROR_VALUE_GREATER_THAN_MAX 1000006
#define NULL_SOLUTION 1000007

class CMscnProblem
{
public:
	CMscnProblem();
	~CMscnProblem();

	int vSetSuppliersCount(int iCount);
	int vSetFactoriesCount(int iCount);
	int vSetWarehousesCount(int iCount);
	int vSetShopsCount(int iCount);

	int vSetSuppCap(double dCap, int iSupplierIndex);
	int vSetFactCap(double dCap, int iFactoryIndex);
	int vSetWareCap(double dCap, int iWarehouseIndex);
	int vSetShopCap(double dCap, int iShopIndex);

	int vSetSuppToFactCost(double dCost, int iSupplierIndex, int iFactoryIndex);
	int vSetFactToWareCost(double dCost, int iFactoryIndex, int iWarehouseIndex);
	int vSetWareToShopCost(double dCost, int iWarehouseIndex, int iShopIndex);

	bool bConstraintsSatisified(double *pdSolution, int* iError);

	double dGetQuality(double *pdSolution, int* iError);

	//zapis i odczyt
	int vLoadProblemFromFile(std::string sFileName);
	int vLoadSolutionFromFile(std::string sFileName, double** pdSolution);
	int vSaveProblemToFile(std::string sFileName);
	int vSaveSolutionToFile(std::string sFileName);

private:
	//liczba dostawcow, fabryk, magazynow, sklepow
	int i_suppliers_count;	//D
	int i_factories_count;	//F
	int i_warehouses_count;	//M
	int i_shops_count;		//S

	//moce produkcyjne dostawcow, fabryk, pojemnosc magazynow, zapotrzebowania sklepow
	double* pd_suppliers_capacities;	//sd
	double* pd_factories_capacities;	//sf
	double* pd_warehouses_capacities;	//sm
	double* pd_shops_capacities;		//ss

	//koszty wytworzenia(badz przechowania) i transportu
	double** pd_supp_to_fact_costs;	//cd
	double** pd_fact_to_ware_costs;	//cf
	double** pd_ware_to_shop_costs;	//cm

	//jednorazowy koszt korzystania z uslug dostawcy, fabryki, magazynu
	double* pd_supp_use_costs;	//ud
	double* pd_fact_use_costs;	//uf
	double* pd_ware_use_costs;	//um

	//przychody sklepow
	double* pd_shop_revenues;	//p

	//DOPISAC, ZE SUPP TO FACT, FACT TO WARE, WARE TO SHOP
	//zakresy dopusczalnych wartosci
	double** pd_supp_prod_min_max;	//xdminmax
	double** pd_fact_prod_min_max;	//xfminmax
	double** pd_ware_prod_min_max;	//xmminmax

	//rzeczywista ilosc produktu wytwarzana i transportowana dalej w lancuchu
	double** pd_supp_to_fact_item_counts;	//xd
	double** pd_fact_to_ware_item_counts;	//xf
	double** pd_ware_to_shop_item_counts;	//xm

	//funkcje parsujace pdSolution
	int v_load_solution(double *pdSolution);
	int v_load_part_of_solution(double *pdSolution, double** pdMatrix, double** pdUpperToLowerMinMax, int iOffsetValue, int iFstLoopCond, int iSndLoopCond);

	//operacje na macierzach
	double** v_create_matrix(int iSizeX, int iSizeY);
	void v_delete_matrix(double** dMatrix, int iSizeX);

	//funkcje pomocnicze do: bool bConstraintsSatisified(double *pdSolution, int* iError);
	bool b_capacity_check(double** pdProducedGoods, double* pdCapacities, int iUpperCount, int iLowerCount);

	//funkcje pomocnicze do: double dGetQuality(double *pdSolution, int* iError);
	double d_calculate_shops_revenue();	//P
	double d_calculate_usages_costs();	//Ku
	double d_calculate_usage_cost(double** pdMatrix, double* pdArray, int iFstLoopCond, int iSndLoopCond);
	double d_calculate_prod_trans_costs();	//Kt
	double d_calculate_prod_trans_cost(double** pdFstMatrix, double** pdSndMatrix, int iFstLoopCond, int iSndLoopCond);

	//funkcje pomocnicze do zapisu/ odczytu
	void v_add_pd_array_to_file(FILE* fFile, double* pdArray, int iArrayLength);
	void v_add_pd_matrix_to_file(FILE *fFile, double** pdMatrix, int iSizeX, int iSizeY);
	int v_load_array_from_file(FILE *pfFile, double *pdArray, int iArrayLength);
	int i_load_matrix_from_file(FILE *pfFile, double** pdMatrix, int iSizeX, int iSizeY, int iOffset);
	double* pd_matrix_to_array(double** pdMatrix, int iSizeX, int iSizeY);

	//funkcja pomocnicza do setterow
	void v_recreate_setter_arr_matrix(double** pdCapacity, double** pdUseCosts, double*** pdUpperToLowerCost, double*** pdUpperToLowerItems, double*** pdUpperToLowerMinMax, int iUpperCount, int iLowerCount);
	int v_cap_setter(double dCap, int iIndex, double* pdArray, int iArrayLength);
	int v_cost_setter(double dCost, double** pdMatrix, int iUpperIndex, int iLowerIndex, int iUpperCount, int iLowerCount);
};