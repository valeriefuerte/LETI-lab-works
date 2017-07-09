#include <iostream>
#include <iomanip>
#include <windows.h>
#define nElements(a) (sizeof(a)/sizeof(a[0]))
using namespace std;
const unsigned short Max_n = 100; //Максимальное количество элементов массива
typedef int arr1 [Max_n] ; //Описание типа массива
typedef unsigned short uns;
void WriteArr (const arr1 &arr, const uns n); //Функция записи элементов в массив
uns numFirst (const arr1 &arr, const uns n); //Функция поиска первого отрицательно элемента
uns numLast (const arr1 &arr, const uns n);  //Функция поиска последнего отрицательно элемента
int sumArr (const arr1 &arr, const uns nFirst, const uns nLast); //Функция суммы элементов между первым и последним отрицательными
int main()
{
	setlocale (0, ""); //Подключение русского языка
	uns n;
	int a [Max_n]; // Задаем массив а
	cout << "Введите количество элементов массива : ";
    cin >> n;
    	for (int i = 0; i < n; i++)  //Ввод элементов массива по-одному 
		{
            cout << "[" << i << "]" << ": ";
            cin >> a[i];
        }
	uns n1 = nElements(a);
	cout << "Перед вызовом WriteArr: " << n << ':' << n1 << endl; //Количество используемых элементов из общего
	WriteArr (a, n);
	uns numberFirst = numFirst (a, n);// Поиск первого отрицательного
	if (numberFirst==n)  cout << "Нет отрицательных элементов в массиве"<<endl;	//Проверка на наличие отрицательного
	else
		{
		cout << " Номер первого отрицательного = " << numberFirst << " Значение = " << a[numberFirst] << endl;
		uns numberLast = numLast (a, n); //Поиск последнего отрицательного
		//Вывод сообщения при совпадении первого и последнего:
		if (numberFirst==numberLast)  cout << "Отрицательный элемент в массиве один"<<endl;
		else
			{
			cout << " Номер последнего отрицательного = " << numberLast << " Значение = " << a[numberLast] << endl;
			cout <<"Сумма = "<< sumArr(a,numberFirst, numberLast); // Вывод суммы
			}
		}	
	return 0;
}	
void WriteArr (const arr1 &arr, const uns n) //Функция записи элементов в массив
{
	uns n1 = nElements(arr);
	cout << "Внутри WriteArr: " << n << ':' << n1 << endl; //Проверка на количество элементов массива внутри функции
	if ((n==0)||(n>n1)) cout << "Range error" << endl; //Вывод ошибки, если элементов массива нет, 
						//или значение параметра n больше реального размера массива
	else 
		for (uns i=0; i<n; i++) cout << arr[i] << " , "; // Вывод массива
	cout << endl;
}
uns numFirst (const arr1 &arr, const uns n) //Функция поиска первого отрицательно элемента
{	
	for (uns i=0; i<n; i++) 	if (arr[i]<0)  	return i;  
}
uns numLast (const arr1 &arr, const uns n) //Функция поиска последнего отрицательно элемента
{	
	for (uns i=n-1; i>=0; i--) if (arr[i]<0) return i;
}
int sumArr (const arr1 &arr, const uns nFirst, const uns nLast) //Функция суммы элементов между первым и последним отрицательными
{
	int sum=0;
	for (uns i=nFirst+1; i<nLast; i++) sum+=arr[i];
	return sum;	
}
