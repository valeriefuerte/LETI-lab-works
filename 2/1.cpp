//Описать структуру, содержащую следующие поля: название пункта назначения рейса; номер рейса; тип самолета. 
//Написать программу, выполняющую (по запросу) следующие действия:
//	ввод с клавиатуры данных в массив структур, записи должны быть размещены в алфавитном порядке по названиям пунктов назначения;
//	вывод на экран пунктов назначения и номеров рейсов, обслуживаемых самолетом, тип которого введен с клавиатуры;
//	если таких рейсов нет, выдать на дисплей соответствующее сообщение.
#include <iostream>
#include <cstring>
using namespace std;
typedef char tAirplane[10];
struct flight // объявление структуры
{
char name[20 ];
unsigned int number;
tAirplane typeAirplane;
};
const unsigned short Max_n = 10; // Максимальное количество рейсов
typedef flight arrF[Max_n] ;	// Массив структур
typedef unsigned short uns;

void ReadRecord ( arrF &arrA, const uns count); // Ввод массива структуры
void WriteRecord (const arrF &arrA, const uns count);   // Вывод массива структуры
void IFWriteRecord (const arrF &arrA, const uns count, tAirplane &tA );   // Вывод массива структуры
int main()
{ 
setlocale(0, "");
arrF arrA; // массив
uns count; // количество
tAirplane tA; // тип самолета, для запроса

cout<< "Введите количество рейсов: " ;
cin>> count ;
cout<< endl; 
ReadRecord (arrA, count);

cout<< endl<<"Массив рейсов: "<<endl;
WriteRecord (arrA, count);

cout<< "Введите тип самолета: " ;
cin>> tA ;
cout<< endl; 
IFWriteRecord(arrA, count, tA);

return 0;
}
// Ввод массива 
void ReadRecord ( arrF &arrA, const uns count)
{
flight record;
	for (int i = 0; i < count; i++) 
	{
	cout<< "Рейс "<< i+1<<endl;
    // Ввод одной записи
	cout<< "Название пункта назначения рейса: " ;
	cin>>record.name ;
	cout<< "Номер рейса: " ;
	cin >> record.number ;
	cout<< "Тип самолета: " ;
	cin>> record.typeAirplane ;

	arrA[i]=record; // Ввод в массив записи
	
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

// Вывод массива
void WriteRecord (const arrF &arrA, const uns count)
{
	for (int i=0; i<count; i++)
	cout <<" "<<arrA[i].name<<" "<<arrA[i].number<<" "<< arrA[i].typeAirplane<< endl;
}

//Функция strcmp имеет прототип:  int strcmp(const char* str1, const char* str2);
//После сравнения строк str1 и str2 данная функция возвратит целое значение:
//	<0 , если str1 < str2
//	=0 , если str1 = str2
//	>0 , если str1 > str2
//	Эта функция производит сравнение, различая прописные и строчные буквы


void IFWriteRecord (const arrF &arrA, const uns count, tAirplane &tA )
{   unsigned short flag=0; // флаг есть ли данные по этому типу самолета
	cout << "Данные о самолетах типа: "<< tA<<endl;
	for (int i=0; i<count; i++)
	{
	if (strcmp(arrA[i].typeAirplane,tA)==0) 
		{	flag=1;
		cout<< "Пункт назначения: "<<arrA[i].name<< " Номер рейса: "<<arrA[i].number<<  endl;
		}
	}	
	if (flag==0) cout<< "Данных о самолетах такого типа нет"<<endl;
}
