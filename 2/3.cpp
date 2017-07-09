//Определить количество вхождений в строку каждого из знаков, встречающихся в ней один или более раз.
//Строка с явной длиной, описывается структурой:
//struct StringL
//{   char str[MAX];   int len;};
#include <string.h>
#include <iostream>
//const unsigned short Max = 100; // Максимальное количество элементов в строке
struct StringL // объявление структуры
{
	char str[100];
	int len;
};
void Sign(StringL &record); // если процедура не возвращает значение то нужно тип void
using namespace std;
int main()
{
	setlocale(0, "");
	StringL rec;
//	cout<< "Введите количество элементов " ;
//	cin>> rec.len ;
	cout<< "Введите строку " ;
	cin>> rec.str ;
	//int rec.len=strlen(record.str) переменная rec и тип писать не нужно, ты заново определяешь
	// библиотеку string не подключила
	rec.len=strlen(rec.str);
	cout << endl<<"Строка: "<<rec.str<<endl<<"Количество символов: "<<rec.len<<endl;
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
	for (int i=1; i<record.len; i++) // я исправила убрала -1
	{
	if(record.str[0] != record.str[i]) {
	int count=1;
	for(int j=i+1; j<record.len; j++) 
		{if (record.str[i]==record.str[j]) {count++;
		record.str[j]=record.str[0];}
		}
	cout<<record.str[i]<<count<<endl;
	}}
	//cout<<record.str; //вывод строки с заменой
}
