#pragma once
#include "Constants.h"

class CTable
{
public:
	CTable();
	CTable(int iSize, int& iError);
	~CTable();
	int iSetSize(int iSize);
	int iSetValue(double dValue, int iIndex);
	int iGetLength();
	double dGetValue(int iIndex, int& iError);
	void vPrint();
private:
	int i_length;
	double* pd_tab;
};