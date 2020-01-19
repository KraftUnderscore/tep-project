#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"
#include "CRandom.h"

int main()
{
	CRandom r;
	r.iSetIntRange(-10, 10);
	r.iSetDoubleRange(20.0, 200.0);
	for (int i = 0; i < 10; i++)
	{
		std::cout << r.iGetInt() << "; " << r.dGetDouble() << "\n";
	}
	/*CMscnProblem t;
	int i_result;

	i_result = t.iLoadProblemFromFile("C:\\Users\\Sebastian\\Desktop\\teppro2.txt");
	std::cout <<"wczytanie problemu: "<< i_result<<"\n";
	double* pd_solution = NULL;
	i_result = t.iLoadSolutionFromFile("C:\\Users\\Sebastian\\Desktop\\tepsol2.txt", &pd_solution);
	std::cout << "wczytanie rozwiazania: " << i_result << "\n";
	i_result = t.iSaveProblemToFile("C:\\Users\\Sebastian\\Desktop\\savep.txt");
	std::cout << "zapis problemu: " << i_result << "\n";
	i_result = t.iSaveSolutionToFile("C:\\Users\\Sebastian\\Desktop\\saves.txt");
	std::cout << "zapis rozwiazania: " << i_result << "\n";
	std::cout << "wynik: "<<t.dGetQuality(pd_solution, &i_result)<<"\n";
	std::cout << "blad wyniku: " << i_result<<"\n";
	std::cout << "spelnia: " << t.bConstraintsSatisified(pd_solution, &i_result) << "\n";
	std::cout << "blad sprawdzenia: " << i_result << "\n";

	delete pd_solution;*/
}