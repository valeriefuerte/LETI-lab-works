//���������� ���������� ��������� � ������ ������� �� ������, ������������� � ��� ���� ��� ����� ���.
//������ � ����� ������, ����������� ����������:
//struct StringL
//{   char str[MAX];   int len;};
#include <string.h>
#include <iostream>
//const unsigned short Max = 100; // ������������ ���������� ��������� � ������
struct StringL // ���������� ���������
{
	char str[100];
	int len;
};
void Sign(StringL &record); // ���� ��������� �� ���������� �������� �� ����� ��� void
using namespace std;
int main()
{
	setlocale(0, "");
	StringL rec;
//	cout<< "������� ���������� ��������� " ;
//	cin>> rec.len ;
	cout<< "������� ������ " ;
	cin>> rec.str ;
	//int rec.len=strlen(record.str) ���������� rec � ��� ������ �� �����, �� ������ �����������
	// ���������� string �� ����������
	rec.len=strlen(rec.str);
	cout << endl<<"������: "<<rec.str<<endl<<"���������� ��������: "<<rec.len<<endl;
	Sign(rec);
	return 0;
}
void Sign(StringL &record)
{
		int count=1;
	for (int i=1; i<record.len; i++)
	{ 
		if (record.str[0]==record.str[i]) count++;
	}
	cout<<record.str[0]<<count<<endl;
	for (int i=1; i<record.len; i++) // � ��������� ������ -1
	{
	if(record.str[0] != record.str[i]) {
	int count=1;
	for(int j=i+1; j<record.len; j++) 
		{if (record.str[i]==record.str[j]) {count++;
		record.str[j]=record.str[0];}
		}
	cout<<record.str[i]<<count<<endl;
	}}
	//cout<<record.str; //����� ������ � �������
}
