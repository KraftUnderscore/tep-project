#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"
int main()
{
    std::cout << "Hello World!\n"; 
	CMscnProblem c_test;
	c_test.vSetFactoriesCount(10);
	c_test.vSetShopsCount(20);
	c_test.vSetSuppliersCount(5);
	c_test.vSetWarehousesCount(2);
	std::string s_file_name = "test_mscn_prob.txt";
	c_test.vSaveProblemToFile(s_file_name);
}