//�-������, �.�. ������ ��������������� �����. ������������ ������� �� ������������.
//������� ����������� ��������� ��������.
//�������� ������ � �������, ������ ����� ��������� (��������� � �������� ����� � ������ � ���  ���������).
//���������� ���������� ���������
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
const unsigned short Max = 10000;
typedef char strString[Max];
strString str1,str2;			//��� ������
  								//��� ���������
int podstroka(strString &str1, strString &str2, int count1, int count2);	/*�������, ����������� �������*/
int main()
{						
setlocale (0,""); // ����������� �������� �����
int count1, count2,f; //���������� ��������� � ������ � ���������
cout << "������� ������: \n";
gets(str1); count1= strlen(str1);
cout << "������� ���������: \n";
gets(str2); count2= strlen(str2);
cout << "������: \n";
cout<<str1<<endl<<str2<<endl;
f=podstroka(str1, str2, count1, count2);
if (f==0) 
cout <<"�� ������! \n";
else 
cout <<"������! \n";
return 0;
}
int podstroka(strString &str1, strString &str2, int count1, int count2)	/*�������, ����������� �������*/
{
int i, j, flag=0;
for (j=0; j<count2; j++)
{
	for (i=0; i<count1; i++)
	{
		if (str1[i]==str2[j]) {
		flag =1;
		break;}
	}
	if (flag==0) return flag;

}
 return flag;
}
