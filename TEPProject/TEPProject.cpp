#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"
#include "CRandomSearch.h"

int main()
{
	CMscnProblem t;
	t.iSetSuppliersCount(4);
	t.iSetFactoriesCount(3);
	t.iSetWarehousesCount(5);
	t.iSetShopsCount(2);
	int result = t.iGenerateInstance(123456789);
	std::cout << "generate: " << result << "\n";
	result = t.iSaveProblemToFile("C:\\Users\\Sebastian\\Desktop\\TEST.txt");
	std::cout << "save: " << result << "\n";
	CRandomSearch c_solver(100000);
	c_solver.vSetSeed(123456789);
	double* pd_solution = c_solver.pdSolve(&t);
	std::cout<<"NAJLEPSZA: "<<t.dGetQuality(pd_solution, NULL);
}