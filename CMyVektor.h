#pragma once
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include "CMyMatrize.h"

using namespace std;

class CMyVektor
{
private:

	int dimension;
	vector<double> vek;

public:
	CMyVektor()
	{
		dimension = 0;
	}

	CMyVektor(int dim)
	{
		dimension = dim;
		vek.resize(dim);
	}

	int getDimension() const { return dimension; }; // Um die Dimension eines Vektors zurueckzugeben;

	void setKomponent(int position, double wert)// um eine bestimmte Komponente des Vektors zu setzen;
	{
		vek.at(position) = wert;
	};

	double getKomponent(int pos) const { return vek.at(pos); };  // um eine bestimmte Komponente des Vektors zurückzugeben.

	double laenge()
	{
		double tmp = 0, laenge = 0;
		for (int i = 0; i < dimension; i++)
		{
			tmp = vek.at(i) * vek.at(i);
			laenge += tmp;
		}

		laenge = sqrt(laenge);
		return laenge;
	}

	string Komponent()
	{
		string ausgabe;
		ausgabe += "(";
		for (int i = 0; i < dimension - 1; i++)
		{
			ausgabe += to_string((double)vek.at(i)) + " , ";  //casting

		}

		ausgabe += to_string((double)vek.at(dimension - 1)) + ")";
		return ausgabe;
	}

};



/*
CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	CMyVektor sum(a.getDimension());
	double ausgabe;
	for (int i = 0; i < a.getDimension(); i++)
	{
		ausgabe = a.getKomponent(i) + b.getKomponent(i);
		sum.setKomponent(i, ausgabe);
	}
	return sum;
}

CMyVektor operator*(double lambda, CMyVektor a)
{
	CMyVektor mult(a.getDimension());
	double ausgabe;
	for (int i = 0; i < a.getDimension(); i++)
	{
		ausgabe = lambda * a.getKomponent(i);
		mult.setKomponent(i, ausgabe);
	}

	return mult;
}*/

CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x))
{
	long double h = 1e-8;
	CMyVektor gradient(x.getDimension());
	for (int i = 0; i < x.getDimension(); i++)
	{
		CMyVektor tmp = x;
		tmp.setKomponent(i, x.getKomponent(i) + h);
		gradient.setKomponent(i, (funktion(tmp) - funktion(x)) / h);
		tmp.setKomponent(i, x.getKomponent(i));
	}

	return gradient;
}


 CMyVektor operator-(CMyVektor A, CMyVektor X)
{
	CMyVektor multMatVek(X.getDimension());
	double ausgabe = 0;
	for (int i = 0; i < X.getDimension(); i++)
	{
		ausgabe = A.getKomponent(i) - X.getKomponent(i);
		multMatVek.setKomponent(i, ausgabe);
	}
	return multMatVek;
}



/*
CMyVektor GVM(CMyVektor x, double(*funktion)(CMyVektor x), double lambda)
{
	CMyVektor x_neu(x.getDimension());
	CMyVektor x_test(x.getDimension());
	int Schritt = 0;
	double fx_neu, fx, fx_test;


	for (int i = 0; i < 25; i++)
	{

	

		fx = funktion(x);

		cout << "Schritt " << i << ":" << endl;
		cout << "		x = (" << x.Komponent() << ")" << endl;
		cout << "		lambda = " << lambda << endl;
		cout << "		f(x) = " << fx << endl;
		cout << "		grad f(x) = (" << gradient(x, funktion).Komponent() << ")" << endl;
		cout << "		||grad f(x)|| = " << gradient(x, funktion).laenge() << endl << endl;

		x_neu = x + lambda * gradient(x, funktion);
		fx_neu = funktion(x_neu);

		cout << "		x_neu = (" << x_neu.Komponent() << ")" << endl;
		cout << "		f(x_neu) = " << fx_neu << endl << endl;



		if (fx_neu > fx)
		{
			x_test = x + 2 * lambda * gradient(x, funktion);

			cout << "		Test mit doppelter Schrittweite (lambda = " << 2 * lambda << "):" << endl;
			cout << "		x_test = (" << x_test.Komponent() << ")" << endl;
			fx_test = funktion(x_test);
			cout << "		f(x_test) = " << fx_test << endl;

			if (fx_test > fx_neu)
			{
				x = x_test;
				cout << "		verdoppele Schrittweite!" << endl << endl;
				lambda = 2 * lambda;

			}
			else {
				x = x_neu;
				cout << "		behalte alte Schrittweite!" << endl << endl;
			}
		}
		else if (fx_neu <= fx)
		{

			//while schleife
			do {
				lambda = lambda / 2;
				x_neu = x + lambda * gradient(x, funktion);
				fx_neu = funktion(x_neu);
				cout << "		halbiere Schrittweite (lambda = " << lambda << "):" << endl;
				cout << "		x_neu (" << x_neu.Komponent() << ")" << endl;
				cout << "		f(x_neu) = " << fx_neu << endl << endl;


			} while (fx_neu < fx);

			x = x_neu;

		}

		if (gradient(x, funktion).laenge() < 1e-5)
		{
			cout << "Ende wegen ||grad f(x)||<1e-5 bei" << endl;
			cout << "		x = (" << x.Komponent() << endl;
			cout << "		lambda = " << lambda << endl;
			cout << "		f(x) = " << fx << endl;
			cout << "		grad f(x) = (" << gradient(x, funktion).Komponent() << ")" << endl;
			cout << "		||grad f(x)|| = " << gradient(x, funktion).laenge() << endl << endl;
			break;
		}
		else if (i + 1 == 25)
		{
			cout << "Ende wegen Schrittanzahl = 25 bei " << endl;
			cout << "		x = (" << x.Komponent() << endl;
			cout << "		lambda = " << lambda << endl;
			cout << "		f(x) = " << fx << endl;
			cout << "		grad f(x) = (" << gradient(x, funktion).Komponent() << ")" << endl;
			cout << "		||grad f(x)|| = " << gradient(x, funktion).laenge() << endl << endl;
			break;
		}
	}




	return x;
	
}
	*/

