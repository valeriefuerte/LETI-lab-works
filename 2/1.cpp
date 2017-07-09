//������� ���������, ���������� ��������� ����: �������� ������ ���������� �����; ����� �����; ��� ��������. 
//�������� ���������, ����������� (�� �������) ��������� ��������:
//	���� � ���������� ������ � ������ ��������, ������ ������ ���� ��������� � ���������� ������� �� ��������� ������� ����������;
//	����� �� ����� ������� ���������� � ������� ������, ������������� ���������, ��� �������� ������ � ����������;
//	���� ����� ������ ���, ������ �� ������� ��������������� ���������.
#include <iostream>
#include <cstring>
using namespace std;
typedef char tAirplane[10];
struct flight // ���������� ���������
{
char name[20 ];
unsigned int number;
tAirplane typeAirplane;
};
const unsigned short Max_n = 10; // ������������ ���������� ������
typedef flight arrF[Max_n] ;	// ������ ��������
typedef unsigned short uns;

void ReadRecord ( arrF &arrA, const uns count); // ���� ������� ���������
void WriteRecord (const arrF &arrA, const uns count);   // ����� ������� ���������
void IFWriteRecord (const arrF &arrA, const uns count, tAirplane &tA );   // ����� ������� ���������
int main()
{ 
setlocale(0, "");
arrF arrA; // ������
uns count; // ����������
tAirplane tA; // ��� ��������, ��� �������

cout<< "������� ���������� ������: " ;
cin>> count ;
cout<< endl; 
ReadRecord (arrA, count);

cout<< endl<<"������ ������: "<<endl;
WriteRecord (arrA, count);

cout<< "������� ��� ��������: " ;
cin>> tA ;
cout<< endl; 
IFWriteRecord(arrA, count, tA);

return 0;
}
// ���� ������� 
void ReadRecord ( arrF &arrA, const uns count)
{
flight record;
	for (int i = 0; i < count; i++) 
	{
	cout<< "���� "<< i+1<<endl;
    // ���� ����� ������
	cout<< "�������� ������ ���������� �����: " ;
	cin>>record.name ;
	cout<< "����� �����: " ;
	cin >> record.number ;
	cout<< "��� ��������: " ;
	cin>> record.typeAirplane ;

	arrA[i]=record; // ���� � ������ ������
	
    }
int min;
flight f; 
for(int i=0; i<count; i++)
	{
	min=i; 
	for (int j=i+1; j<count; j++)
		{if(strcmp (arrA[j].name,arrA[min].name)) min=j;}
	if(i!=min){
		f=arrA[i];
		arrA[i]=arrA[min];
		arrA[min]=f;}}
}

// ����� �������
void WriteRecord (const arrF &arrA, const uns count)
{
	for (int i=0; i<count; i++)
	cout <<" "<<arrA[i].name<<" "<<arrA[i].number<<" "<< arrA[i].typeAirplane<< endl;
}

//������� strcmp ����� ��������:  int strcmp(const char* str1, const char* str2);
//����� ��������� ����� str1 � str2 ������ ������� ��������� ����� ��������:
//	<0 , ���� str1 < str2
//	=0 , ���� str1 = str2
//	>0 , ���� str1 > str2
//	��� ������� ���������� ���������, �������� ��������� � �������� �����


void IFWriteRecord (const arrF &arrA, const uns count, tAirplane &tA )
{   unsigned short flag=0; // ���� ���� �� ������ �� ����� ���� ��������
	cout << "������ � ��������� ����: "<< tA<<endl;
	for (int i=0; i<count; i++)
	{
	if (strcmp(arrA[i].typeAirplane,tA)==0) 
		{	flag=1;
		cout<< "����� ����������: "<<arrA[i].name<< " ����� �����: "<<arrA[i].number<<  endl;
		}
	}	
	if (flag==0) cout<< "������ � ��������� ������ ���� ���"<<endl;
}
