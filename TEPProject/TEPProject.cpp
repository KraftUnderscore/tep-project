#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"

int main()
{
	CMscnProblem t;
	int i_result;
	i_result = t.iSetFactCap(0.1, 10);
	std::cout << "wczytanie problemu: " << i_result << "\n";

	i_result = t.iLoadProblemFromFile("C:\\Users\\Sebastian\\Desktop\\teppro2.txt");
	std::cout <<"wczytanie problemu: "<< i_result<<"\n";
	double* pd_solution = NULL;
	i_result = t.iLoadSolutionFromFile("C:\\Users\\Sebastian\\Desktop\\tepsol2.txt", &pd_solution);
	std::cout << "wczytanie rozwiazania: " << i_result << "\n";
	i_result = t.iSaveProblemToFile("C:\\Users\\Sebastian\\Desktop\\prob2.txt");
	std::cout << "zapis problemu: " << i_result << "\n";
	i_result = t.iSaveSolutionToFile("C:\\Users\\Sebastian\\Desktop\\sol2.txt");
	std::cout << "zapis rozwiazania: " << i_result << "\n";
	std::cout << "wynik: "<<t.dGetQuality(pd_solution, &i_result)<<"\n";
	std::cout << "blad wyniku: " << i_result<<"\n";
	std::cout << t.dGetMax(5, i_result);
	std::cout << "; blad minmax: " << i_result << "\n";
	std::cout << "spelnia: " << t.bConstraintsSatisified(pd_solution, &i_result) << "\n";
	std::cout << "blad sprawdzenia: " << i_result << "\n";

	delete pd_solution;
}