//Содержимое заданного текстового файла F, 
//разделенного на строки, переписать в текстовый файл G, 
//выписывая литеры каждой строки в обратном порядке.
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
using namespace std;

struct str;
void Stack(vector<string>  lit,int size); //считать данные и поместить их в стек
void Rewrite(vector<string>  lit,int size); //функция, реализующая задание
//структуры данных
struct str {
    vector<string> lit ();
};

int main()
{
	setlocale(LC_ALL,"Russian");
    cout<<"Выберите тип ввода данных \n";
    cout<<"0 - консоль, 1 - файл \n";
    int enter=0;
    cin>>enter;
    int vecSize = 0; //размер вектора
    vector<string> lit(vecSize);
    //ввод из консоли
	if(enter == 0) { cout<<"ok";
/*	cout<<"Введите количество строк  ";
	cin >> vecSize;//размер вектора
	vector<string> lit();
	if(vecSize>100) {cerr<<"Ошибка! Введите данные с количеством строк меньше 100!";
	exit(1);}
	else{
		for(int i = 0; i < vecSize; i++) {
	        		cin >> lit[i];
	        		//lit.push_back();
   					}
   		int size=lit.size();
    	cout<<"Длина вектора"<<size;

	}*/
	}
    else{ 
		if(enter == 1) { //ввод из файла
    		ifstream fin("in.txt");
   			if (!fin.is_open())
   			{
       			 cerr << "Файл input не может быть открыт!" << endl;
       		 	return 1;
   		 	}
   			//fin>>vecSize;
   				
		
			   int size=lit.size();
			   	   vector<string> lit(size);
				cout<<"Количество строк: "<<size<<endl;
   				for(int i = 0; i < size; i++) { fin>>lit[i];
   				//	lit.push_back(vecSize);
					cout << lit[i] << ' ';}
			}
    	else {cerr<<"Неверно выбран тип ввода данных!\n";
			exit(3);}
	}
//	cout<<"Ввоод закончен  ";
//	for(int i = 0; i < vecSize; i++) { 
//					cout << lit[i] << ' ';}
					
   // Rewrite(lit, vecSize); //функция, реализующая задание
    return 0;
}
void Stack(vector<string>  lit,int size)
{
	
}
/*
void Rewrite(vector<string> lit,int size)
{
	ofstream fout("out.txt"); // создаём объект класса ofstream для записи и связываем его с файлом
	int i=size;cout<<"\n В обратном порядке: \n"<<i;
	while (i>=0) 
	{
	//	cout<<lit[i]<<" \n";
		for (int j=lit[i].size()-1; j>=0; j--)
		{cout<<lit[i][j];
		fout<<lit[i][j]; // запись строки в файл
		}
		cout<<" \n";
		fout<<endl;
		i--;
	}
	fout.close(); // закрываем файл
}*/
