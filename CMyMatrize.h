#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "CMyVektor.h"
using namespace std;

class CMyMatrize
{
private:

	int reihe;
	int spalte;
	vector<CMyVektor> matrize;


public:
	CMyMatrize();
	CMyMatrize(int spalte, int reihe);
	void setDimensionMatrize(int Spalte, int Reihe);
	void setKomponentMatrize(int reihe, int spalte, double data);

	double getKomponentMatrize(int zeile, int spalte);

	CMyMatrize invers()
	{
		CMyMatrize invers(2, 2);
		if (spalte = 2 && reihe == 2)
		{
			
			double determinant = 0;

			determinant = (1 / ((matrize[0].getKomponent(1)*matrize[1].getKomponent(1)) - (matrize[1].getKomponent(0)*matrize[0].getKomponent(1))));

			invers.setKomponentMatrize(0, 0, determinant * matrize[1].getKomponent(1));
			invers.setKomponentMatrize(0, 1, -1 * determinant * matrize[0].getKomponent(1));
			invers.setKomponentMatrize(1, 0, determinant * matrize[1].getKomponent(0));
			invers.setKomponentMatrize(1, 1, -1 * determinant * matrize[0].getKomponent(0));
			cout << determinant << endl;
			return invers;
		}
		else
		{
			cout << "Reihe und Spalte sin groesser als 2 x 2" << endl;
	
		}
	};

	void print()
	{
		cout << matrize[0].getKomponent(0) << " " << matrize[0].getKomponent(1) << "\n"
			<< matrize[1].getKomponent(0) << " " << matrize[1].getKomponent(1) << "\n";
	}

	friend CMyVektor operator*(CMyMatrize A, CMyVektor X)
	{
		CMyVektor multMatVek(X.getDimension());
		double ausgabe = 0;
		for (int i = 0; i < X.getDimension(); i++)
		{
			ausgabe = A.getKomponentMatrize(i, 0) * X.getKomponent(i);
			multMatVek.setKomponent(i, ausgabe);
		}
		return multMatVek;
	}



	//jacobi matrize
	CMyMatrize jacobi(CMyVektor x, CMyVektor(*funktion1)(CMyVektor a), CMyVektor(*funktion2)(CMyVektor b))
	{
		CMyMatrize result(2, 2);
		for (int j = 0; j < result.spalte; j++) {
			result.setKomponentMatrize(0, j, funktion1(x).getKomponent(j));
		}
		for (int j = 0; j < result.spalte; j++) {
			result.setKomponentMatrize(1, j, funktion2(x).getKomponent(j));
		}
		return result;
	}

};

