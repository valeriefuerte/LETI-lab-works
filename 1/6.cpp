#include <iostream>
#include <iomanip>
#include <windows.h>
#define nElements(a) (sizeof(a)/sizeof(a[0]))
using namespace std;
const unsigned short Max_n = 100; //������������ ���������� ��������� �������
typedef int arr1 [Max_n] ; //�������� ���� �������
typedef unsigned short uns;
void WriteArr (const arr1 &arr, const uns n); //������� ������ ��������� � ������
uns numFirst (const arr1 &arr, const uns n); //������� ������ ������� ������������ ��������
uns numLast (const arr1 &arr, const uns n);  //������� ������ ���������� ������������ ��������
int sumArr (const arr1 &arr, const uns nFirst, const uns nLast); //������� ����� ��������� ����� ������ � ��������� ��������������
int main()
{
	setlocale (0, ""); //����������� �������� �����
	uns n;
	int a [Max_n]; // ������ ������ �
	cout << "������� ���������� ��������� ������� : ";
    cin >> n;
    	for (int i = 0; i < n; i++)  //���� ��������� ������� ��-������ 
		{
            cout << "[" << i << "]" << ": ";
            cin >> a[i];
        }
	uns n1 = nElements(a);
	cout << "����� ������� WriteArr: " << n << ':' << n1 << endl; //���������� ������������ ��������� �� ������
	WriteArr (a, n);
	uns numberFirst = numFirst (a, n);// ����� ������� ��������������
	if (numberFirst==n)  cout << "��� ������������� ��������� � �������"<<endl;	//�������� �� ������� ��������������
	else
		{
		cout << " ����� ������� �������������� = " << numberFirst << " �������� = " << a[numberFirst] << endl;
		uns numberLast = numLast (a, n); //����� ���������� ��������������
		//����� ��������� ��� ���������� ������� � ����������:
		if (numberFirst==numberLast)  cout << "������������� ������� � ������� ����"<<endl;
		else
			{
			cout << " ����� ���������� �������������� = " << numberLast << " �������� = " << a[numberLast] << endl;
			cout <<"����� = "<< sumArr(a,numberFirst, numberLast); // ����� �����
			}
		}	
	return 0;
}	
void WriteArr (const arr1 &arr, const uns n) //������� ������ ��������� � ������
{
	uns n1 = nElements(arr);
	cout << "������ WriteArr: " << n << ':' << n1 << endl; //�������� �� ���������� ��������� ������� ������ �������
	if ((n==0)||(n>n1)) cout << "Range error" << endl; //����� ������, ���� ��������� ������� ���, 
						//��� �������� ��������� n ������ ��������� ������� �������
	else 
		for (uns i=0; i<n; i++) cout << arr[i] << " , "; // ����� �������
	cout << endl;
}
uns numFirst (const arr1 &arr, const uns n) //������� ������ ������� ������������ ��������
{	
	for (uns i=0; i<n; i++) 	if (arr[i]<0)  	return i;  
}
uns numLast (const arr1 &arr, const uns n) //������� ������ ���������� ������������ ��������
{	
	for (uns i=n-1; i>=0; i--) if (arr[i]<0) return i;
}
int sumArr (const arr1 &arr, const uns nFirst, const uns nLast) //������� ����� ��������� ����� ������ � ��������� ��������������
{
	int sum=0;
	for (uns i=nFirst+1; i<nLast; i++) sum+=arr[i];
	return sum;	
}
