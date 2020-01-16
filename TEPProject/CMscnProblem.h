#include <iostream>
#pragma once

#define COUNT_MIN 1
#define SKIP_4_CHAR 4
#define SKIP_10_CHAR 10

#define SUCCESS 100
#define COUNT_LESS_THAN_MIN 101
#define NULL_SOLUTION 102
#define VALUE_LESS_THAN_MIN 103
#define VALUE_GREATER_THAN_MAX 104
#define FAILED_OPENING_FILE 105
#define INDEX_OUT_OF_RANGE 106
#define SOLUTION_COUNTS_NOT_EQ_PROBLEM_COUNTS 107
#define NULL_ARRAY 108
#define NULL_MATRIX 109

class CMscnProblem
{
public:
	CMscnProblem();
	~CMscnProblem();

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

	bool bConstraintsSatisified(double *pdSolution, int* iError);

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
	double* pd_supp_caps;	//sd
	double* pd_fact_caps;	//sf
	double* pd_ware_caps;	//sm
	double* pd_shop_caps;	//ss

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
	double** pd_supp_to_fact_goods_min_max;	//xdminmax
	double** pd_fact_to_ware_goods_min_max;	//xfminmax
	double** pd_ware__to_shop_goods_min_max;//xmminmax

	double** pd_supp_to_fact_goods_min;//xdminmax
	double** pd_supp_to_fact_goods_max;
	double** pd_fact_to_ware_goods_min;//xfminmax
	double** pd_fact_to_ware_goods_max;
	double** pd_ware_to_shop_goods_min;//xmminmax
	double** pd_ware_to_shop_goods_max;

	//rzeczywista ilosc produktu wytwarzana i transportowana dalej w lancuchu
	double** pd_supp_to_fact_goods;	//xd
	double** pd_fact_to_ware_goods;	//xf
	double** pd_ware_to_shop_goods;	//xm

	//funkcje parsujace pdSolution
	int i_load_solution(double *pdSolution);
	int i_load_part_of_solution(double *pdSolution, double** pdMatrix, double** pdUpperToLowerMin, double** pdUpperToLowerMax, int iSolutionOffset, int iUpperCount, int iLowerCount);

	//operacje na macierzach
	double** pd_create_matrix(int iSizeX, int iSizeY);
	void v_delete_matrix(double** dMatrix, int iSizeX);

	//funkcje pomocnicze do: bool bConstraintsSatisified(double *pdSolution, int* iError);
	bool b_capacity_check(double** pdProducedGoods, double* pdCapacities, int iUpperCount, int iLowerCount);

	//funkcje pomocnicze do: double dGetQuality(double *pdSolution, int* iError);
	double d_calculate_shops_revenue();	//P
	double d_calculate_usages_costs();	//Ku
	double d_calculate_usage_cost(double** pdUpperToLowerGoods, double* pdUsageCosts, int iUpperCount, int iLowerCount);
	double d_calculate_upp_to_low_costs();	//Kt
	double d_calculate_upp_to_low_cost(double** pdUpperToLowerCosts, double** pdUpperToLowerGoods, int iUpperCount, int iLowerCount);

	//funkcje pomocnicze do zapisu/ odczytu
	int i_add_pd_array_to_file(FILE* fFile, double* pdArray, int iArrayLength);
	int i_add_pd_matrix_to_file(FILE *fFile, double** pdMatrix, int iSizeX, int iSizeY);
	int i_get_array_from_file(FILE *pfFile, double *pdArray, int iArrayLength);
	int i_get_matrix_from_file(FILE *pfFile, double** pdMatrix, int iSizeX, int iSizeY, int iFileOffset);
	double* pd_convert_matrix_to_array(double** pdMatrix, int iSizeX, int iSizeY);

	//funkcja pomocnicza do setterow
	void v_array_matrix_creator(double** pdCapacity, double** pdUseCosts, double*** pdUpperToLowerCost, double*** pdUpperToLowerItems, double*** pdUpperToLowerMinMax, double*** pdUpperToLowerMin, double*** pdUpperToLowerMax, int iUpperCount, int iLowerCount);
	int i_array_setter(double dCap, int iIndex, double* pdArray, int iArrayLength);
	int i_matrix_setter(double dCost, double** pdMatrix, int iUpperIndex, int iLowerIndex, int iUpperCount, int iLowerCount);
};