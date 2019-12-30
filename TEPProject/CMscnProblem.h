#pragma once

class CMscnProblem
{
public:
	CMscnProblem();

	void vSetSuppliersCount(int iCount);
	void vSetFactoriesCount(int iCount);
	void vSetWarehousesCount(int iCount);
	void vSetShopsCount(int iCount);

	bool bConstraintsSatisified(double *pdSolution);

	double dGetQuality(double *pdSolution);

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

	//zakresy dopusczalnych wartosci
	double* pd_supp_prod_min_max;	//xdminmax
	double* pd_fact_prod_min_max;	//xfminmax
	double* pd_ware_prod_min_max;	//xmminmax

	//rzeczywista ilosc produktu wytwarzana i transportowana dalej w lancuchu
	double** pd_supp_to_fact_item_counts;	//xd
	double** pd_fact_to_ware_item_counts;	//xf
	double** pd_ware_to_shop_item_counts;	//xm

	void v_load_solution(double *pdSolution);
	void v_load_part_of_solution(double *pdSolution, double** pdMatrix, int iFstLoopCond, int iSndLoopCond);
	double** v_create_matrix(int iSizeX, int iSizeY);
	void v_delete_matrix(double** dMatrix, int iSizeX);

	//funkcje pomocnicze do: double dGetQuality(double *pdSolution);
	double d_calculate_shops_revenue();	//P
	double d_calculate_usages_costs();	//Ku
	double d_calculate_usage_cost(double** pdMatrix, double* pdArray, int iFstLoopCond, int iSndLoopCond);
	double d_calculate_prod_trans_costs();	//Kt
	double d_calculate_prod_trans_cost(double** pdFstMatrix, double** pdSndMatrix, int iFstLoopCond, int iSndLoopCond);
};