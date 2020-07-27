#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;


double h = pow(10, -4);

class CMyVektor {
private:
	vector<double> vektor;

public:
	CMyVektor() {
		this->vektor = {};
	}
	CMyVektor(int size) {
		this->vektor.resize(size);
	}

	CMyVektor(vector<double> vektor) {
		this->vektor = vektor;
	}

	int getDimension() {
		return vektor.size();
	}

	void setKomponent(int line, double key) {
		this->vektor[line] = key;
	}

	double getKomponent(int line) {
		return this->vektor[line];
	}

	double longVector() {
		double total = 0;
		for (unsigned int i = 0; i < this->vektor.size(); i++) {
			total += this->vektor[i] * this->vektor[i];
		}
		return sqrt(total);
	}

	void showMember() {
		cout << "( ";
		unsigned int i = 0;
		while (i < vektor.size()) {
			cout << vektor[i] << "; ";
			i++;
		}
		cout << ")" << endl;
	}

};
CMyVektor gradient(CMyVektor x, double(*function)(CMyVektor x)) {
	CMyVektor endresult(x.getDimension());
	CMyVektor xplush = x;

	for (int i = 0; i < x.getDimension(); i++) {
		xplush.setKomponent(i, x.getKomponent(i) + h);

		double fx = ((function(xplush) - function(x)) / h);
		endresult.setKomponent(i, fx);
		xplush = x;
	}
	return endresult;
}
CMyVektor operator+(CMyVektor& a, CMyVektor& b) {
	CMyVektor c(a.getDimension());
	if (a.getDimension() == b.getDimension()) {
		for (int i = 0; i < a.getDimension(); i++) {
			double res = (a.getKomponent(i) + b.getKomponent(i));
			c.setKomponent(i, res);
		}
	}
	return c;
}
CMyVektor operator*(double lambda, CMyVektor a) {
	CMyVektor c(a.getDimension());
	if (a.getDimension() != 0) {
		for (int i = 0; i < a.getDimension(); i++) {
			c.setKomponent(i, a.getKomponent(i)*lambda);
		}
	}
	return c;
}

double f(CMyVektor vektor) {
	double x = vektor.getKomponent(0);
	double y = vektor.getKomponent(1);
	return ((pow(x, 3) * pow(y, 3)) - (2 * y));
}

double g(CMyVektor vektor) {
	double x1 = vektor.getKomponent(0);
	double x2 = vektor.getKomponent(1);

	return (x1 - 2);
}

void gradientVerfahren(double lambda, CMyVektor vektor, double(*function)(CMyVektor x)) {

	CMyVektor vektorStart = vektor;
	CMyVektor vektorNew = vektorStart;
	CMyVektor vektorOld = vektor;
	CMyVektor vektorTest(vektor.getDimension());

	int schritte = 0;
	double j = gradient(vektorOld, function).longVector();
	while (true) {


		vektorOld = vektorNew;


		///////////////////////////////////////
		if (gradient(vektorOld, function).longVector() < pow(10, -5)) {
			cout << "\tEnde wegen ||gradf(x)|| <1e-5 bei" << endl;
		}
		else if (schritte >= 25) {
			cout << "\tEnde wegen Schrittanzahl = 25 bei" << endl;
		}
		else {
			cout << "Schritt " << schritte << endl;
		}
		cout << "\tx = "; vektorOld.showMember();


		cout << "\tlambda = " << lambda << endl;
		///////////////////////////////////////

		CMyVektor tmp = lambda * gradient(vektorOld, function);
		vektorNew = vektorOld + tmp;

		/////////////////////////////
		cout << "\tf(x) = " << function(vektorOld) << endl;
		cout << "\tgrad f(x) = ";
		gradient(vektorOld, function).showMember();

		cout << "\t||grad f(x)|| = " << gradient(vektorOld, function).longVector() << endl << endl;
		///////////////////////////////

		if (gradient(vektorOld, function).longVector() < pow(10, -5) || schritte >= 25)break;

		///////////////////////////////
		cout << "\tx_neu = ";
		vektorNew.showMember();

		cout << "\tf(x_neu) = " << function(vektorNew) << endl << endl;
		///////////////////////////////

		if (function(vektorNew) > function(vektorOld)) {
			CMyVektor tmp = (2 * lambda)*gradient(vektorOld, function);
			vektorTest = vektorOld + tmp;

			////////////////////////////
			cout << "\tTest mit doppelter Schrittweite (lambda = " << lambda * 2 << "):" << endl;
			cout << "\tx_test = ";
			vektorTest.showMember();
			cout << "\tf(x_Test) = " << function(vektorTest) << endl;

			/////////////////////////

			if (function(vektorTest) > function(vektorNew)) {
				vektorNew = vektorTest;
				lambda *= 2;
				cout << "\tverdoppele Schrittweite!" << endl << endl;
			}
			else {
				cout << "\tBehalte alte Schrittweite!" << endl << endl;
			}

		}
		else if (function(vektorNew) <= function(vektorOld)) {

			while (function(vektorNew) < function(vektorOld)) {
				lambda = lambda / 2;
				cout << "\thalbiere Schrittweite (lambda = " << lambda << "):" << endl;
				CMyVektor tmp = lambda * gradient(vektorOld, function);
				vektorNew = vektorOld + tmp;

				cout << "\tx_neu = ";
				vektorNew.showMember();

				cout << "\tf(x_neu) = " << function(vektorNew) << endl << endl;
			}

		}
		schritte++;
	}
}

class CMyMatrix {
private:
	vector<vector<double>> matrix;
public:
	CMyMatrix(int row, int col) {
		matrix.resize(row);
		for (int i = 0; i < row; i++) {
			matrix[i].resize(col);
		}
	}


	CMyMatrix invers() {
		CMyMatrix tmp(this->getRow(), this->getCol());

		if (this->getRow() == 2 && this->getCol() == 2) {
			double zahl = 1 / ((this->matrix[0][0] * this->matrix[1][1]) - (this->matrix[0][1] * this->matrix[1][0]));

			tmp.setKomponent(0, 0, (zahl*this->matrix[1][1]));
			tmp.setKomponent(0, 1, (zahl*this->matrix[0][1] * -1));
			tmp.setKomponent(1, 0, (zahl*this->matrix[1][0] * -1));
			tmp.setKomponent(1, 1, (zahl*this->matrix[0][0]));
		}
		else {
			cout << "\tkein 2x2-Matrix" << endl;
		}
		return tmp;
	}

	void setKomponent(int row, int col, double key) {
		matrix[row][col] = key;
	}

	double getKomponent(int row, int col) {
		return matrix[row][col];
	}

	int getRow() {
		return matrix.size();
	}
	int getCol() {
		return matrix[0].size();
	}

	void showMember() {
		cout << "\t\t( ";
		for (unsigned int i = 0; i < this->matrix.size(); i++) {
			for (unsigned int j = 0; j < this->matrix[i].size(); j++) {
				cout << matrix[i][j] << "; ";
			}cout << endl << "\t\t";
		}cout << ")" << endl;
	}
};

CMyVektor operator*(CMyMatrix a, CMyVektor v) {

	CMyVektor tmp(a.getRow());
	for (int i = 0; i < a.getRow(); i++) {
		double r = 0;
		for (int j = 0; j < a.getCol(); j++) {

			r += (a.getKomponent(i, j)*v.getKomponent(j));
		}
		tmp.setKomponent(i, r);
	}
	return tmp;
};
CMyVektor gradF(CMyVektor v) {
	CMyVektor result(v.getDimension());

	result = gradient(v, f);
	return result;

}
CMyVektor gradG(CMyVektor v) {
	CMyVektor result(v.getDimension());

	result = gradient(v, g);
	return result;
}

CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion1)(CMyVektor a), CMyVektor(*funktion2)(CMyVektor b)) {
	CMyMatrix result(2, 2);

	for (int j = 0; j < result.getCol(); j++) {
		result.setKomponent(0, j, funktion1(x).getKomponent(j));
	}
	for (int j = 0; j < result.getCol(); j++) {
		result.setKomponent(1, j, funktion2(x).getKomponent(j));
	}
	return result;
}
void newtonVerfahren(CMyVektor x, CMyVektor(*funktion1)(CMyVektor a), CMyVektor(*funktion2)(CMyVektor b)) {
	int i = 0;
	CMyVektor startPunkt(x);
	CMyVektor naechstePunkt(x);

	CMyMatrix jacob(2, 2);

	CMyVektor deltaX(2);
	CMyVektor funktion(2);


	while (true) {
		startPunkt = naechstePunkt;

		funktion.setKomponent(0, f(startPunkt));
		funktion.setKomponent(1, g(startPunkt));

		if (funktion.longVector() < pow(10, -5)) {
			cout << "Ende wegen ||f(x)||<1e-5 bei" << endl;
		}
		else if (i == 50) {
			cout << "Schrittzahl ist 50" << endl;
		}
		else {
			cout << "Schritt " << i << ":\n";

		}
		cout << "\tx = "; startPunkt.showMember();
		cout << "\tf(x) = "; funktion.showMember();

		if (funktion.longVector() < pow(10, -5) || i == 50) {
			cout << "\t||f(x)|| = " << funktion.longVector() << endl;
			break;
		}

		jacob = jacobi(startPunkt, funktion1, funktion2);
		cout << "\tf'(x) =\n"; jacob.showMember();

		cout << "\t(f'(x))^(-1) =\n"; jacob.invers().showMember();

		deltaX = jacob.invers() * (-1 * funktion);
		cout << "\tdx = "; deltaX.showMember();

		naechstePunkt = naechstePunkt + deltaX;
		cout << "\t||f(x)|| = " << funktion.longVector() << endl;

		i++;
	}
}


int main() {


	vector<double> startPunkt = { 1,1 };
	CMyVektor test1(startPunkt);

	newtonVerfahren(test1, gradF, gradG);


	system("pause");
	return 0;
}