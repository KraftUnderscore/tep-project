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
	t.vLoadProblemFromFile("C:\\Users\\Sebastian\\Desktop\\teptest.txt");
}