#include <iostream>
#include <cmath>
using namespace std;
long double count_sum(double y, double e); 
int main ()
{setlocale (0,""); // Подключение русского языка
   int type;
   cout << "Выберите вариант ввода данных \n";
   cin >> type;
   if (type ==2) {
   	freopen ("input.txt", "r", stdin );
   	freopen ("output.txt", "w", stdout);
      }
double x, E;  // Описание переменных
long double s,f;
cout << "Введите Х \n"; // Ввод переменной х
cin >> x ;
cout << "Введите E (0 < E << 1) \n"; // Ввод эпсилон
cin >> E ;
s=count_sum(x,E);  // Задается значение s через функцию
cout << s << "\n"; 	// Вывод результата
f=1.0/3.0*(exp(x))+2*exp(-x/2)*cos(x*(sqrt(3))/2); // Проверка
cout << "Проверка:" << f <<"\n"; // Вывод проверки
system("output.txt");
return 0;
}
long double count_sum( double y, double e)
{   double u=1.0; // Присваивание начальных значений
	double S=1.0;
	int i=1;
	while (abs(u)>e) // Условие работы цикла
	{
	u*=(y*y*y)/((3*i)*(3*i-1)*(3*i-2)); // Вычисление функции
	S+=u;
	i++;
	}
	return S;
}
