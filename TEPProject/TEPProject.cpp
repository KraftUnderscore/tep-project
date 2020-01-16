#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"

int main()
{
	CMscnProblem t;
	int i_result;
	i_result = t.iLoadProblemFromFile("C:\\Users\\Sebastian\\Desktop\\teppro2.txt");
	std::cout <<"wczytanie problemu: "<< i_result<<"\n";
	double* pd_solution = NULL;
	i_result = t.iLoadSolutionFromFile("C:\\Users\\Sebastian\\Desktop\\tepsol2.txt", &pd_solution);
	t.iSaveProblemToFile("C:\\Users\\Sebastian\\Desktop\\prob1.txt");
	t.iSaveSolutionToFile("C:\\Users\\Sebastian\\Desktop\\sol1.txt");
	std::cout << "wczytanie solution: " << i_result<<"\n";
	std::cout << "wynik: "<<t.dGetQuality(pd_solution, &i_result)<<"\n";
	std::cout << "rozwiazanie: " << i_result<<"\n";
	std::cout << "spelnia: " << t.bConstraintsSatisified(pd_solution, &i_result) << "\n";
	std::cout << "rozwiazanie: " << i_result << "\n";
	delete pd_solution;
}