#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
using namespace std;
int main ()
{setlocale (0,""); // Подключение русского языка
	double a,n,i,S;
	while (cin) 
	{
		cout << "Введите N \n"; // Ввод значения N
		cin >> n;
		if (n>=0) { S=1; // Условие работы цикла
		(a=1);
		for (i=1; i<=n/2; (i++)) // Для переменной i=0, и пока i< n/2 прибавляется единица к значению i
		{a*=(n+1)/(n-2*i+1); // Вычисление а(i)
				S+=a; // Вычисление S
		}
		cout << S << "\n"; // Вывод конечного значения S
		}
		else
			cout << "Неверные данные\n" ; // Если n<0, то вывод сообщения об ошибке
	}
	return 0;
}
	