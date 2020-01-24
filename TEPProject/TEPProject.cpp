#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"
#include "CRandomMod.h"

int main()
{
	CMscnProblem t;
	t.iSetSuppliersCount(4);
	t.iSetFactoriesCount(3);
	t.iSetWarehousesCount(5);
	t.iSetShopsCount(2);
	int result = t.iGenerateInstance(123456789);
	std::cout << "generate: " << result << "\n";
	CRandomMod c_solver(10000);
	c_solver.vSetSeed(123456789);
	double* pd_solution = c_solver.pdSolve(&t);
	std::cout<<"NAJLEPSZA: "<<t.dGetQuality(pd_solution, NULL);
	delete pd_solution;
}