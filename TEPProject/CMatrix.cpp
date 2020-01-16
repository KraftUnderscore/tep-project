#include "pch.h"
#include <iostream>
#include "CMatrix.h"

CMatrix::CMatrix(int iRows, int iColumns, int& iError)
{
	int i_size = iRows * iColumns;
	c_matrix = CTable(i_size, iError);
	i_rows = iRows;
	i_columns = iColumns;
}

int CMatrix::iSetSize(int iRows, int iColumns)
{
	return c_matrix.iSetSize(iRows * iColumns);
}
int CMatrix::iSetValue(double dValue, int iRow, int iColumn)
{
	return c_matrix.iSetValue(dValue, iRow*i_columns + iColumn);
}
double CMatrix::dGetValue(int iRow, int iColumn, int& iError)
{
	return c_matrix.dGetValue(iRow*i_columns + iColumn, iError);
}