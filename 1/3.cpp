#include <iostream>
#include <cmath>
using namespace std;
int main ()
{setlocale (0,""); // Подключение русского языка
	double x;
	long double u,s,E,f;
	int i;
	cout << "Введите Х \n"; // Ввод переменной х
	cin >> x ;
	cout << "Введите E (0 < E << 1) \n"; // Ввод эпсилон
	cin >> E ;
	cout << x<< "\n"; // Вывод значений х и эпсилон для проверки
	cout << E<< "\n";
	u=1.0; // Присваивание начальных значений
	s=1.0;
	i=1;
	while (abs(u)>E) // Условие работы цикла
	{
	u*=(x*x*x)/((3*i)*(3*i-1)*(3*i-2)); // Вычисление функции
	cout << u << "\n"; //Вывод промежуточных результатов
	s+=u;
	cout << s << "\n";
	i++;
	cout << i << "\n";
	cout << abs(u) << "\n";
	}
	cout << s << "\n"; 	// Вывод результата
	f=1.0/3.0*(exp(x))+2*exp(-x/2)*cos(x*(sqrt(3))/2); // Проверка
	cout << "Проверка:" << f <<"\n"; // Вывод проверки
	return 0;
}
