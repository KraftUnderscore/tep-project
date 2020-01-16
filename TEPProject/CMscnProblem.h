#include <iostream>
#include "Constants.h"
#include "CTable.h"
#include "CMatrix.h"
#pragma once


class CMscnProblem
{
public:
	CMscnProblem();

	int iSetSuppliersCount(int iCount);
	int iSetFactoriesCount(int iCount);
	int iSetWarehousesCount(int iCount);
	int iSetShopsCount(int iCount);

	int iSetSuppCap(double dCap, int iIndex);
	int iSetFactCap(double dCap, int iIndex);
	int iSetWareCap(double dCap, int iIndex);
	int iSetShopCap(double dCap, int iIndex);

	int iSetSuppToFactCost(double dCost, int iUpperIndex, int iLowerIndex);
	int iSetFactToWareCost(double dCost, int iUpperIndex, int iLowerIndex);
	int iSetWareToShopCost(double dCost, int iUpperIndex, int iLowerIndex);

	int iSetSuppUseCost(double dCost, int iIndex);
	int iSetFactUseCost(double dCost, int iIndex);
	int iSetWareUseCost(double dCost, int iIndex);
	int iSetShopRevenue(double dRev, int iIndex);

	bool bConstraintsSatisified(double *pdSolution, int* iError);

	double dGetMin(int iIndex, int& iError);
	double dGetMax(int iIndex, int& iError);

	double dGetQuality(double *pdSolution, int* iError);

	//zapis i odczyt
	int iLoadProblemFromFile(std::string sFileName);
	int iLoadSolutionFromFile(std::string sFileName, double** pdSolution);
	int iSaveProblemToFile(std::string sFileName);
	int iSaveSolutionToFile(std::string sFileName);

private:
	//liczba dostawcow, fabryk, magazynow, sklepow
	int i_supp_count;	//D
	int i_fact_count;	//F
	int i_ware_count;	//M
	int i_shop_count;	//S

	//moce produkcyjne dostawcow, fabryk, pojemnosc magazynow, zapotrzebowania sklepow
	CTable c_supp_caps;	//sd
	CTable c_fact_caps;	//sf
	CTable c_ware_caps;	//sm
	CTable c_shop_caps;	//ss

	//koszty wytworzenia(badz przechowania) i transportu
	CMatrix c_supp_to_fact_costs;	//cd
	CMatrix c_fact_to_ware_costs;	//cf
	CMatrix c_ware_to_shop_costs;	//cm

	//jednorazowy koszt korzystania z uslug dostawcy, fabryki, magazynu
	CTable c_supp_use_costs;	//ud
	CTable c_fact_use_costs;	//uf
	CTable c_ware_use_costs;	//um

	//przychody sklepow
	CTable c_shop_revenues;	//p

	//zakresy dopusczalnych wartosci
	CMatrix c_supp_to_fact_goods_min;//xdminmax
	CMatrix c_supp_to_fact_goods_max;
	CMatrix c_fact_to_ware_goods_min;//xfminmax
	CMatrix c_fact_to_ware_goods_max;
	CMatrix c_ware_to_shop_goods_min;//xmminmax
	CMatrix c_ware_to_shop_goods_max;

	//rzeczywista ilosc produktu wytwarzana i transportowana dalej w lancuchu
	CMatrix c_supp_to_fact_goods;	//xd
	CMatrix c_fact_to_ware_goods;	//xf
	CMatrix c_ware_to_shop_goods;	//xm

	//funkcje parsujace pdSolution
	int i_load_solution(double *pdSolution);
	int i_load_part_of_solution(double *pdSolution, CMatrix* pcUpperToLowerGoods, int iSolutionOffset, int iUpperCount, int iLowerCount);

	//funkcje pomocnicze do: bool bConstraintsSatisified(double *pdSolution, int* iError);
	bool b_capacity_check(CMatrix* pcProducedGoods, CTable* pcCapacities, int iUpperCount, int iLowerCount);
	bool b_shop_cap_check(CMatrix* pcProducedGoods, CTable* pcCapacities, int iUpperCount, int iLowerCount);
	
	bool b_check_min_max(double *pdSolution);
	int b_check_part_min_max(double *pdSolution, CMatrix* pcUpperToLowerGoods, CMatrix* pcUpperToLowerMin, CMatrix* pcUpperToLowerMax, int iSolutionOffset, int iUpperCount, int iLowerCount);

	//funkcje pomocnicze do: double dGetQuality(double *pdSolution, int* iError);
	double d_calculate_shops_revenue();	//P
	double d_calculate_usages_costs();	//Ku
	double d_calculate_usage_cost(CMatrix* pcUpperToLowerGoods, CTable* pcUsageCosts, int iUpperCount, int iLowerCount);
	double d_calculate_upp_to_low_costs();	//Kt
	double d_calculate_upp_to_low_cost(CMatrix* pcUpperToLowerCosts, CMatrix* pcUpperToLowerGoods, int iUpperCount, int iLowerCount);

	//funkcje pomocnicze do zapisu/ odczytu
	int i_add_pc_array_to_file(FILE* pfFile, CTable* pcArray, int iArrayLength);
	int i_add_pc_matrix_to_file(FILE* pfFile, CMatrix* pcMatrix, int iSizeX, int iSizeY);
	int i_add_min_max_matrix_to_file(FILE *pfFile, CMatrix* pcMinMatrix, CMatrix* pcMaxMatrix, int iSizeX, int iSizeY);
	int i_get_array_from_file(FILE *pfFile, CTable* pcArray, int iArrayLength);
	int i_get_matrix_from_file(FILE *pfFile, CMatrix* pcMatrix, int iSizeX, int iSizeY, int iFileOffset);
	int i_get_min_max_matrix_from_file(FILE *pfFile, CMatrix* pcMinMatrix, CMatrix* pcMaxMatrix, int iSizeX, int iSizeY, int iFileOffset);
};