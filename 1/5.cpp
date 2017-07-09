#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std ;
int main ( )
{	setlocale (0,""); // Подключение русского языка
	short i; // описание переменных
	float x0 , x1,x2; 
	ifstream infile ("in_data.txt"); //данные берутся из файла
    ofstream outfile ("out_data.txt"); //данные записываются в  файл

	if (!infile) cout << "Входной файл не открыт!" << endl;
	else {
		
		//проверка первого элемента
    	if(!(infile >> x0) ) cout << "Файл пуст!" << endl;
  		else{
		  
  			 //проверка второго элемента
			if(!(infile >> x1)) {i=1; cout << "Число локальных max последовательности = " << i << endl;
    								  cout << "Локальный max последовательности = " << x0 << endl;
									  outfile << "Число max последовательности  = " << i << endl; 
									  cout << "Число max последовательности  = " << i << endl; 	
   								 } 
    		else 
			{
				if ( x0 > x1) i=1;		
				else i=0;
			
				//проверка третьего элемента
				if(!(infile >> x2)) 
				{
					if (i==1) cout << "Локальный max последовательности = " << x0 << endl;	
   					else    cout << "Локальный max последовательности = " << x1 << endl;					
				    cout << "Число локальных max последовательности = " << 1 << endl;
				}
				else 
				{
				
				// продолжение поиска локальных максимумов 
				do {	
				if (( x0 <x1 )&&(x1>x2)) i++;
				cout <<  x0 << "<" <<  x1 << ">" << x2 << "  max: " << i << endl;
				outfile << setw(5)<< x0 << "<" << setw(5)<< x1 << ">" << setw(5)<< x2 << "  max: " << i << endl;
				x0=x1;
				x1=x2;
				}
				while (infile >> x2);
				
				// проверка является ли последний элемент локальным максимумом 
				if ( x1 > x0) i++; 
				outfile << "Число max последовательности  = " << i << endl; 
				cout << "Число max последовательности  = " << i << endl; 
				}
			}
			
		}
	infile.close();
	outfile.close();
	return 0;
	}
}
