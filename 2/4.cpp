#include <string.h>
#include <iostream>

using namespace std;
const unsigned short Max = 100;
typedef char strString[Max];
void Repeat(strString &str);
int main()
{
	setlocale(0, "");
	int num;
	strString stroka;
	cout<< " ������� ������ " ;
	gets(stroka);
	num=strlen(stroka);
	cout << endl<<" ������: "<<stroka<<endl<<" ���������� ���������: "<<num << endl;
    Repeat(stroka);
	return 0;
}
void Repeat(strString &str)
{
  int	n=strlen(str);
	int i,j;
	int flag=0;
	for (i=0; i<n; i++)
	{
		if (str[i]==str[i+1])
			{
			for (j=i+1;j<n; j++)
				if (str[j]==str[j+1])
				{cout <<" �������� A[i]A[i+1] "<<str[i]<<str[i+1]<<" ����� "<<i<<endl;
				 cout <<" �������� A[j]A[j+1] "<<str[j]<<str[j+1]<<" ����� "<<j<<endl;
				 cout <<endl;
				 flag=1;
				}
			}
	}
if (flag==0) cout<<" ����� ��������� ���! "<<endl;
}
