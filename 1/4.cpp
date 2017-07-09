#include <iostream>
#include <cmath>
using namespace std;
long double count_sum(double y, double e); 
int main ()
{setlocale (0,""); // ����������� �������� �����
   int type;
   cout << "�������� ������� ����� ������ \n";
   cin >> type;
   if (type ==2) {
   	freopen ("input.txt", "r", stdin );
   	freopen ("output.txt", "w", stdout);
      }
double x, E;  // �������� ����������
long double s,f;
cout << "������� � \n"; // ���� ���������� �
cin >> x ;
cout << "������� E (0 < E << 1) \n"; // ���� �������
cin >> E ;
s=count_sum(x,E);  // �������� �������� s ����� �������
cout << s << "\n"; 	// ����� ����������
f=1.0/3.0*(exp(x))+2*exp(-x/2)*cos(x*(sqrt(3))/2); // ��������
cout << "��������:" << f <<"\n"; // ����� ��������
system("output.txt");
return 0;
}
long double count_sum( double y, double e)
{   double u=1.0; // ������������ ��������� ��������
	double S=1.0;
	int i=1;
	while (abs(u)>e) // ������� ������ �����
	{
	u*=(y*y*y)/((3*i)*(3*i-1)*(3*i-2)); // ���������� �������
	S+=u;
	i++;
	}
	return S;
}
