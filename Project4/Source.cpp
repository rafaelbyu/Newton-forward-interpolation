// Задание 4
// Группа 05194-1, студент Букреев Рафаэль
// Первая интерполяционная формула Ньютона

#include <iostream>
#include <math.h>
#include <iomanip>
#include <fstream>
using namespace std;

double f(double x)//задал функцию
{
	return sqrt(sin(x * x));
}

double NewtonOne(double a, double b, double x, double** delta, int n) // Первая Интерполяционная формула Ньютона
{
	double F = delta[0][1];
	double h = (b - a) / n;											  //шаг интерполяции
	double q = (x - a) / h;
	double q1 = 1;
	for (int i = 1; i <= n; i++)
	{			
		q1 = q1 * (q - i + 1) / i;
		F += delta[0][i + 1] * q1; 
	}
	return F;
}

void main()
{	
	setlocale(0, "");
	
	double a = 0;
	double b = 0;
	cout << "Введите x0 " << endl;
	cin >> a;
	cout << "Введите xn " << endl;
	cin >> b;

	

	ofstream fout;
	fout.open("Interpol.txt");
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}

	else {

		int n = 0;
		

		cout << "Введите число разбиений " << endl;
		cin >> n;
		
		
		if (n == 0) return ;
		double h = (b - a) / n;																							

		double** delta = new double* [n + 1];				//таблица конечных разностей в виде двумерного динамического массива

		for (int i = 0; i <= n; i++)																						
		{
			delta[i] = new double[n + 2];                                                                                   //заменил n на i в new double
		}
		for (int i = 0; i <= n; i++)		// 0 строка - значения переменной x_i
		{	
			delta[i][0] = a + h * i;																						//заменил 0 на а
		}
		for (int i = 0; i <= n; i++)		// 1 строка - значения функции f(x_i)
		{
			delta[i][1] = f(delta[i][0]);
			//cout << delta[i][1] << " ";
		}
		/*cout << endl;*/
		for (int m = 1; m <= n+1; m++)	// 2, 3, 4... и все последующие строки - это таблица конечных разностей
		{
			for (int i = 0; i <= n - m; i++)
			{
				delta[i][m + 1] = delta[i + 1][m] - delta[i][m];
				//cout << setprecision(6) << delta[i][m + 1] << setw(6) << "\t";
			}
			/*cout << endl;
			cout << endl;*/
		}

		//for (int i = 0; i <= n; i++)		// 1 строка - значения функции f(x_i)
		//{
		//	cout << " " << delta[i][1];
		//}

		//cout << endl;
		//cout << endl;
		//cout << endl;
		//cout << endl;

		//for (int m = 1; m <= n + 1; ++m)	// 2, 3, 4... и все последующие строки - это таблица конечных разностей
		//{
		//	cout << "Разность порядка: "<<"("<< m<<")";
		//	for (int i = 0; i <= n - m; i++)
		//	{
		//		cout << " " <<setprecision(2) << delta[i][m + 1];
		//	}
		//	cout << endl;
		//}


		/*double xj = -1.05;
		cout << "Введите начальную границу для xj " << endl;
		cin >> xj;
		cout << endl;*/

		cout << "xj\t" << setw(16) << "F(xj)\t\t\t\t" << setw(8) << "f(xj)-F(xj)\t" << setw(30) << "f(xj) :" << setw(15) << "n = " << n << endl;
		for (double j = -1.05; j <= -0.95; j += 0.01)
		{
			/*if (j >= -1.05 && j <= -1)*/
			{	
				
				cout << j << '\t' << setprecision(8) << setw(16) << NewtonOne(a, b, j, delta, n) << "\t\t" << setw(16) << fabs(f(j) - NewtonOne(a, b, j, delta, n)) << "\t\t\t" << setw(16) << f(j) << endl;
			}
			/*if (j >= -0.99 && j <= -0.95)
			{
				double x0 = -0.95;
				cout << j << '\t' << setprecision(8) << setw(16) << NewtonOne(a, b, j, delta, n, x0) << "\t\t" << setw(16) << fabs(f(j) - NewtonOne(a, b, j, delta, n, x0)) << "\t\t\t" << setw(16) << f(j) << endl;
			}*/
		}
		cout << endl;

		fout << "xj\t" << setw(16) << "F(xj)\t\t\t\t" << setw(8) << "f(xj)-F(xj)\t" << setw(30) << "f(xj) :" << setw(15) << "n = " << n << endl;
		for (double j = -1.05; j <= -0.95; j += 0.01)
		{
			/*if (j >= -1.05 && j <= -1)*/
			{
		
				fout << j << '\t' << setprecision(8) << setw(16) << NewtonOne(a, b, j, delta, n) << "\t\t" << setw(16) << fabs(f(j) - NewtonOne(a, b, j, delta, n)) << "\t\t\t" << setw(16) << f(j) << endl;
			}
			/*if (j >= -0.99 && j <= -0.95)
			{
				double x0 = -0.95;
				fout << j << '\t' << setprecision(8) << setw(16) << NewtonOne(a, b, j, delta, n, x0) << "\t\t" << setw(16) << fabs(f(j) - NewtonOne(a, b, j, delta, n, x0)) << "\t\t\t" << setw(16) << f(j) << endl;
			}*/
			}
		fout << endl;
		delete[] delta;
	}
	fout.close();

}