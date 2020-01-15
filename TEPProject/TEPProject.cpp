#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"

int main()
{
	CMscnProblem t;
<<<<<<< HEAD
	int i_result=-1;
	i_result = t.vLoadProblemFromFile("C:\\Users\\Sebastian\\Desktop\\teppro2.txt");
=======
	//t.vSetFactoriesCount(2);
	//t.vSetSuppliersCount(1);
	//t.vSetWarehousesCount(3);
	//t.vSetShopsCount(4);
	//t.vSaveProblemToFile("C:\\Users\\Sebastian\\Desktop\\teptest1.txt");
	int i_result;
	i_result = t.vLoadProblemFromFile("C:\\Users\\spiet\\Desktop\\tepp1.txt");
>>>>>>> 772e1a157b2a69cfb400210a55dad9b1c9c25ca9
	std::cout <<"wczytanie problemu: "<< i_result<<"\n";
	double* pd_solution = NULL;
	i_result = t.vLoadSolutionFromFile("C:\\Users\\spiet\\Desktop\\teps1.txt", &pd_solution);
	std::cout << "wczytanie solution: " << i_result<<"\n";
	std::cout << "wynik: "<<t.dGetQuality(pd_solution, &i_result)<<"\n";
	std::cout << "rozwiazanie: " << i_result<<"\n";
	std::cout << "spelnia: " << t.bConstraintsSatisified(pd_solution, &i_result) << "\n";
	std::cout << "rozwiazanie: " << i_result << "\n";
	delete pd_solution;
}