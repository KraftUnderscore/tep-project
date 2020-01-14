#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"

int main()
{
	CMscnProblem t;
	//t.vSetFactoriesCount(2);
	//t.vSetSuppliersCount(1);
	//t.vSetWarehousesCount(3);
	//t.vSetShopsCount(4);
	//t.vSaveProblemToFile("C:\\Users\\Sebastian\\Desktop\\teptest1.txt");
	int i_result;
	i_result = t.vLoadProblemFromFile("C:\\Users\\Sebastian\\Desktop\\teppro2.txt");
	std::cout <<"wczytanie problemu: "<< i_result<<"\n";
	double* pd_solution = NULL;
	i_result = t.vLoadSolutionFromFile("C:\\Users\\Sebastian\\Desktop\\tepsol2.txt", &pd_solution);
	std::cout << "wczytanie solution: " << i_result<<"\n";
	std::cout << "wynik: "<<t.dGetQuality(pd_solution, &i_result)<<"\n";
	std::cout << "rozwiazanie: " << i_result<<"\n";
	std::cout << "spelnia: " << t.bConstraintsSatisified(pd_solution, &i_result) << "\n";
	std::cout << "rozwiazanie: " << i_result << "\n";
	delete pd_solution;
}