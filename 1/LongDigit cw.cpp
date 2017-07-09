#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

const unsigned short Max_n = 10000; 	  //Максимальное количество элементов массива
typedef unsigned int arrDigital [Max_n] ; //Описание ТИПА массива
typedef unsigned short arrCount;		  //Описание типа для количества элементов массива
typedef char strDigital[10000]; 		  //Тип строки из файла равная длинному числу
typedef short T; 						  // Тип описание количество для разбивки массива
//typedef	unsigned short F;			  // Тип для флага если результат положительный или отрицательный	  

//Функции записи элементов в массив и вывода на экран
void readArr ( const int t, const strDigital strN, arrDigital &arr,arrCount &count ); 
void writeArr ( arrDigital &arr,arrCount &count);
void writeStr (  arrDigital &arr, arrCount &count, const unsigned short f, const T &tT);

void addArr(arrDigital  &a, arrCount &counta, arrDigital  &b, arrCount &countb, T &tT);
void subtract(arrDigital  &a, arrCount &counta, arrDigital  &b, arrCount &countb, T &tT);
int main ( )
{	setlocale (0,""); // Подключение русского языка

 T tCount; // описание количество для разбивки массива
 strDigital strNumber1, strNumber2, strRezult; // Строки из файла=числам
 arrDigital arrA,arrB={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Массивы
 arrCount countA,countB;			// Количество элементов в массиве
 char operation;
unsigned short flag=0;  //Если результат положительный

	ifstream infile ("in_data.txt"); //данные берутся из файла
    ofstream outfile ("out_data.txt"); //данные записываются в  файл

	if (!infile) {cout << "Входной файл не открыт!" << endl; return 0;
	}

	cout << "Введите количество для разбивки массива : ";
    cin >> tCount;
    
    cout << "Введите операцию + сумма или - разность : ";
    cin >> operation;
    
    infile >> strNumber1;
    infile >> strNumber2;
    
    cout << "Число первое: " << strNumber1 <<  endl; 
    cout << "Число второе: " << strNumber2 <<  endl;
   
	if(strlen(strNumber1)>strlen(strNumber2)) // если  длина первого числа больше длины второго
		{
			readArr(tCount,strNumber1,arrA,countA);
	    	readArr(tCount,strNumber2,arrB,countB);
	    
	    }
	else 	if(strlen(strNumber1)<strlen(strNumber2)) // если длина первого числа меньше длины второго
			{ 	if (operation=='-') flag=1;
				readArr(tCount,strNumber2,arrA,countA);
	    		readArr(tCount,strNumber1,arrB,countB);
			}
			else 	// если количество цифр равно
			{	readArr(tCount,strNumber1,arrA,countA);
	    		readArr(tCount,strNumber2,arrB,countB);
				if (operation=='-') 
				// для разности проверяем чтобы первое число было больше втогого
				// если не так меняем массивы чтобы aarA содержал большее число
				{ for (int i=countA; i>=0; i--) if (arrA[i]<arrB[i])  {
										 	flag=1;
											readArr(tCount,strNumber2,arrA,countA);
	    									readArr(tCount,strNumber1,arrB,countB);
	    									break; // выход из цикла
											}
				}
			}
	writeArr(arrA,countA);
	writeArr(arrB,countB);  
	if (operation=='+')
	{   
		addArr(arrA, countA, arrB, countB, tCount);
	}
    else{
		
		subtract(arrA, countA, arrB, countB, tCount);
    }; 
	writeArr(arrA,countA);
	writeStr(arrA,countA,flag, tCount);

	infile.close();
	outfile.close();
	return 0;
}
void readArr ( const int t, const strDigital strN, arrDigital &arr, arrCount &count)  //Функция записи элементов в массив
{   count=0;		//Количестро элементов в массиве
    char  s[t-1];  	// Строка для одного элемента массива
	int len=strlen(strN);
//  cout <<"Длина строки = "<< len<<  endl; 
   
   while (t*(count+1)<=len) //Цикл по элементам строки
   {     
      for (int i=0;i<t;i++) s[i]=strN[len-t*(count+1)+i] ; // Формирование строки для числа массива
      arr[count]=  atoi(s);			// Заполнение элемента массива числом (преобразование строки в целое)
    
//	 cout<<count<<" =  "<<arr[count]  << endl;
     count++;	//Увеличиваем количество элементов массива
   }
   
   // Формирование последнего элемента массива если количество элементов в строке не делится нацело на Т
   if(len%t!=0)   
   { 
   int m=len%t;
   memset (s,' ',t);
   strcat (s,"\0");
   for (int i=0;i<m;i++) s[t-m+i]=strN[i] ;
   arr[count]=  atoi(s);
//   cout<<count<<" =  "<<arr[count]<< endl;
    }
	else count--;
  
}

 void writeArr (  arrDigital &arr, arrCount &count) //Функция вывода массива
{
	int n = count;
	cout << "WriteArr: " <<  n << endl; 
	for (int i=0; i<=n; i++) cout << i<<" = " << arr[i]<< endl;; // Вывод массива
	
}
void writeStr (  arrDigital &arr, arrCount &count,const unsigned short f, const T &tT) //Функция вывода массива строкой
{
	cout << "Результат: " << endl;
	if (f==1) cout << '-';
    // если старшие элементы = 0, то находим первый не нулевой элемент массива
	int k=count;
	while (arr[k]==0)
		{k--;
		}
	// Вывод массива строкой 
	for (int i=k; i>=0; i--) {
	 cout <<  arr[i];
	 // если количество цифр в arr[i] меньше Т (например  t=3, arr[i]=45, нужно вывести 045)
	 cout.fill('0'); // символ заполнения
	 cout.width(tT); // количество для заполнения 0
	}
}
void addArr(arrDigital  &a, arrCount &counta, arrDigital  &b, arrCount &countb, T &tT)
{
	// Формирование делителя взависимости от Т
	int tD=1;  	
	for(int i = 0; i < tT; i++) tD*=10;
	cout<<tD<< endl;
	int r = 0;
	
/*r - обозначает сколько у нас "в уме"
 при сложение младших цифр в уме у нас 0*/
	for(int i = 0; i <= counta; i++) {
		a[i] += b[i] + r;
		//сумма очередных цифр и переноса
		if (a[i] >= tD) {
		//случай, когда происходит перенос в следующий разряд
			r = 1;
			a[i] -= tD;
		} else {
		//случай, когда переноса не происходит
			r = 0;
		}
	}
	//если после сложения остался еще перенос, то нужно добавить еще одну цифру
	if (r > 0) {
		counta++;
		a[counta] = r;
	}
}

void subtract(arrDigital  &a, arrCount &counta, arrDigital  &b, arrCount &countb, T &tT)
{
	// Формирование делителя взависимости от Т
	int tD=1;  	
	for(int i = 0; i < tT; i++) tD*=10;
	cout<<tD<< endl;
	
//функция вычитает из числа a число b
//r - обозначает был ли заем единицы из текущего разряда
	int r = 0;
//заем из младшего разряда отсутствует
	for(int i = 0; i <= counta; i++) {
		if (a[i] < b[i]) 
		{//разность очередных цифр с учетом заема
		
			a[i] = (tD+a[i] )-b[i] - r;
			r = 1;
		
		} else {
		//случай, когда заем не происходит
			a[i] -= b[i] + r;
			r = 0;
		}
	}
}


