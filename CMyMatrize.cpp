#include <iostream>
#include "CMyMatrize.h"
#include "CMyVektor.h"

CMyMatrize::CMyMatrize()
{
	reihe = 0;
	spalte = 0;
}

CMyMatrize::CMyMatrize(int reihe, int spalte)
{
	this->matrize.resize(reihe);
	for (int i = 0; i < reihe; i++)
	{
		matrize.at(i) = CMyVektor(spalte);
	}
	setDimensionMatrize(reihe, spalte);
}

void CMyMatrize::setDimensionMatrize(int Reihe, int Spalte) { spalte = Spalte; reihe = Reihe; }

void CMyMatrize::setKomponentMatrize(int Reihe, int Spalte, double Data)
{
	matrize.at(Reihe).setKomponent(Spalte, Data);
}
double CMyMatrize::getKomponentMatrize(int Reihe, int Spalte)
{
	return matrize.at(Reihe).getKomponent(Spalte);
}

