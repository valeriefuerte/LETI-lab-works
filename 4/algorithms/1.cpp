#include <iostream>
#include <fstream>
#include <vector> 
#include <stack>
#include <cstdlib>

using namespace std;
ifstream in("in.txt");
ofstream fout("out.txt");
typedef int Size_t;
typedef int Vector[2000000];
int compare (const void * a, const void * b);
void qsortxi(Vector a, Size_t size_t) 
{
	int compare=0,assign=0; //счетчики количества сравнений и присваиваний
	int tmp, pivot; //элементы для пересприсваения и опорный
	stack <int> lows, highs; //стеки
   	int low, high, i, j; //фиксированные начальные значения

	cout<<"Начало сортировки "<<endl;
	fout<<"Начало сортировки "<<endl;
	lows.push(0); //заносим в один стек 0
	highs.push(size_t ); //заносим в другой стек размер массива

	while (!lows.empty() ) //если стек не пуст
	 {
		low  = lows.top();  //переходим к первому элементу
		lows.pop();			//удаляем 0
		high = highs.top(); //переходим к первому элементу
		highs.pop();		//удаляем размер
		i = low;
		j = high;
		tmp = (int)(low + (high-low)/2); //ищем опорный элемент посередине
		pivot = a[tmp];
		
		cout<<"Левое: "<<low<<" Опорный элемент: "<<pivot<<" Правое: "<<high<<endl;
		fout<<"Левое: "<<low<<" Опорный элемент: "<<pivot<<" Правое: "<<high<<endl;
		do {
			while (a[i] < pivot) { //если текущий справа элемент меньше опорного
				i++; compare++;
			}
			while (a[j] > pivot) { //если текущий слева элемент больше опорного
				j--; compare++;
			}
			if (i <= j) { compare++; //сравниваем 2 текущих элемента
				if (a[i] > a[j]) {
					cout<<"Обмен элементов: a["<<i<<"]="<<a[i]<<" и a["<<j<<"]="<<a[j]<<endl;
					fout<<"Обмен элементов: a["<<i<<"]="<<a[i]<<" и a["<<j<<"]="<<a[j]<<endl;
					tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
					compare++;
					assign++;
				}
				i++; 
				if (j > 0) {
					j--; compare++;
				}
			}
		} while (i <= j); //не уйти за пределы i,j

		if (i < high) { compare++;
			lows.push(i);
			highs.push(high);
		}
		if (j > low) { compare++;
			lows.push(low);
			highs.push(j);
		}
		cout<<"Массив: ";
		fout<<"Массив: ";
		for(int k=0;k<=size_t;k++)
		{
		cout<<a[k]<<" ";
		fout<<a[k]<<" ";
		}
		cout<<endl;	fout<<endl;	
	}
	cout<<"Количество сравнений= "<<compare<<endl;
	cout<<"Количество обменов= "<<assign<<endl;
}

Vector vec;  
int main()
{ Size_t i=0;
    setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
    int enter=0;
    cout<<"Выберите тип ввода: 0-с консоли, 1-из файла ";
   cin>>enter;
    if(enter==1) {
		if (!in.is_open()) // если файл не открыт
			{cout << "Файл не может быть открыт!\n"; // сообщить об этом
			exit(0);}
		else
		{ 	cout<<"Массив: ";
		while(!in.eof())
			{   in>>vec[i];
			 	cout << vec[i] << ' ';
		 		fout << vec[i] << ' ';
		 		i++;
        	}
		cout<<endl;
		fout<<endl;
		qsortxi( vec, i-1);	
		}}
	else{
		if(enter==0)
		{
		cout<<"Введите количество элементов в массиве ";
		Size_t size=0;
		cin>>size;
		cout<<"Введите массив: ";
		while(i!=size)
			{   cin>>vec[i];
			 	fout << vec[i] << ' ';
		 		i++;
        	}
		cout<<endl;
		fout<<endl;	
		qsortxi(vec, size-1);
		}
		else {cout<<"Неверно выбран тип ввода данных";
			exit(1);}
	}
	cout<<"Отсортированный массив: "<<endl;
	fout<<"Отсортированный массив: "<<endl;
	for(int k=0;k<i;k++)
	{
		cout<<vec[k]<<" ";
		fout<<vec[k]<<" ";
	}
	cout<<endl;
	fout<<endl;
	cout<<"Сравнение с библиотечной функцией qsort: "<<endl;
	int n;
	qsort (vec, i, sizeof(int), compare);
	for (n=0; n<i; n++) printf ("%d ",vec[n]);
	in.close(); //закрытие файла
	return 0;
}
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
