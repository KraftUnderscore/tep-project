#pragma once
#include "CTable.h"
class CMatrix
{
public:
	CMatrix() {i_rows = 0; i_columns = 0;}
	CMatrix(int iRows, int iColumns, int& iError);
	int iSetSize(int iRows, int iColumns);
	int iGetLength() { return i_rows * i_columns; }
	int iSetValue(double dValue, int iRow, int iColumn);
	int iSetValue(double dValue, int iIndex);
	double dGetValue(int iRow, int iColumn, int& iError);
	double dGetValue(int iIndex, int& iError);
	void vPrint();
private:
	int i_rows, i_columns;
	CTable c_matrix;
};