#include "pch.h"
#include <iostream>
#include "CTable.h"

CTable::CTable()
{
	pd_tab = NULL;
	i_length = 0;
}

CTable::CTable(int iSize, int& iError)
{
	if (iSize <= 0)
	{
		pd_tab = NULL;
		i_length = 0;
		iError = INCORRECT_ARRAY_LENGTH;
	}
	else
	{
		pd_tab = new double[iSize];
		i_length = iSize;
		iError = SUCCESS;
	}
}

CTable::~CTable()
{
	if (pd_tab != NULL) delete pd_tab;
}

int CTable::iSetSize(int iSize)
{
	if (iSize <= 0) return INCORRECT_ARRAY_LENGTH;
	if (pd_tab != NULL) delete pd_tab;
	pd_tab = new double[iSize];
	i_length = iSize;
	return SUCCESS;
}

int CTable::iSetValue(double dValue, int iIndex)
{
	if (pd_tab == NULL) return NULL_ARRAY;
	if (iIndex < 0 || iIndex >= i_length)return INDEX_OUT_OF_RANGE;
	pd_tab[iIndex] = dValue;
	return SUCCESS;
}

int CTable::iGetLength()
{
	return i_length;
}

double CTable::dGetValue(int iIndex, int& iError)
{
	if (pd_tab == NULL) return NULL_ARRAY;
	if (iIndex < 0 || iIndex >= i_length) 
	{
		iError = INDEX_OUT_OF_RANGE;
		return 0.0;
	}
	iError = SUCCESS;
	return pd_tab[iIndex];
}

void CTable::vPrint()
{
	for (int ii = 0; ii < i_length; ii++)std::cout << pd_tab[ii] << " ";
}