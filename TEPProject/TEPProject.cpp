#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"

int main()
{
	CMscnProblem t;
	t.iSetSuppliersCount(2);
	t.iSetFactoriesCount(4);
	t.iSetWarehousesCount(3);
	t.iSetShopsCount(5);
	int result = t.iGenerateInstance(123456789);
	std::cout << "generate: " << result << "\n";
	result = t.iSaveProblemToFile("C:\\Users\\Sebastian\\Desktop\\TEST.txt");
	std::cout << "save: " << result << "\n";
}