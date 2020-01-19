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
	int i_result = c_matrix.iSetSize(iRows * iColumns);
	if (i_result == SUCCESS)
	{
		i_rows = iRows;
		i_columns = iColumns;
	}
	return i_result;
}

int CMatrix::iSetValue(double dValue, int iRow, int iColumn)
{
	return c_matrix.iSetValue(dValue, iRow*i_columns + iColumn);
}

int CMatrix::iSetValue(double dValue, int iIndex)
{
	return c_matrix.iSetValue(dValue, iIndex);
}

double CMatrix::dGetValue(int iRow, int iColumn, int& iError)
{
	return c_matrix.dGetValue(iRow*i_columns + iColumn, iError);
}

double CMatrix::dGetValue(int iIndex, int& iError)
{
	return c_matrix.dGetValue(iIndex, iError);
}

void CMatrix::vPrint()
{
	int i_result;
	for (int ii = 0; ii < i_rows; ii++)
	{
		for (int ij = 0; ij < i_columns; ij++)
		{
			double d_value = c_matrix.dGetValue(ii * i_columns + ij, i_result);
			if (i_result != SUCCESS)std::cout << "ERROR ";
			else std::cout << d_value<<" ";
		}
		std::cout << "\n";
	}
}