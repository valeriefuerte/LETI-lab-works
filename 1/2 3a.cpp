#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
using namespace std;
int main ()
{setlocale (0,""); // ����������� �������� �����
	double a,n,i,S;
	while (cin) 
	{
		cout << "������� N \n"; // ���� �������� N
		cin >> n;
		if (n>=0) { S=1; // ������� ������ �����
		(a=1);
		for (i=1; i<=n/2; (i++)) // ��� ���������� i=0, � ���� i< n/2 ������������ ������� � �������� i
		{a*=(n+1)/(n-2*i+1); // ���������� �(i)
				S+=a; // ���������� S
		}
		cout << S << "\n"; // ����� ��������� �������� S
		}
		else
			cout << "�������� ������\n" ; // ���� n<0, �� ����� ��������� �� ������
	}
	return 0;
}
	