#include <iostream>
#include <cmath>
using namespace std;
int main ()
{setlocale (0,""); // ����������� �������� �����
	double x;
	long double u,s,E,f;
	int i;
	cout << "������� � \n"; // ���� ���������� �
	cin >> x ;
	cout << "������� E (0 < E << 1) \n"; // ���� �������
	cin >> E ;
	cout << x<< "\n"; // ����� �������� � � ������� ��� ��������
	cout << E<< "\n";
	u=1.0; // ������������ ��������� ��������
	s=1.0;
	i=1;
	while (abs(u)>E) // ������� ������ �����
	{
	u*=(x*x*x)/((3*i)*(3*i-1)*(3*i-2)); // ���������� �������
	cout << u << "\n"; //����� ������������� �����������
	s+=u;
	cout << s << "\n";
	i++;
	cout << i << "\n";
	cout << abs(u) << "\n";
	}
	cout << s << "\n"; 	// ����� ����������
	f=1.0/3.0*(exp(x))+2*exp(-x/2)*cos(x*(sqrt(3))/2); // ��������
	cout << "��������:" << f <<"\n"; // ����� ��������
	return 0;
}
