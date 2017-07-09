//Напечатать все перестановки заданных n различных натуральных чисел (или символов).
#include <iostream>
#include <fstream>
using namespace std;

unsigned int strCount=0;
const unsigned short Max = 256; 		  //Максимальное количество элементов массива
unsigned int str[Max];
void permutation(unsigned int l,unsigned int r);

int main()
{
    setlocale(LC_ALL,"Russian");
    cout <<"Введите n для перестановки чисел  ";
    cin>>strCount;
    if(strCount==0) cout <<"Некорректные данные!";
	else
	{
		for(unsigned int i=1; i<= strCount; i++ ) str[i]=i; //Заполнение  массива
		permutation(1,strCount);
	}
    return 0;
}

void permutation(unsigned int l,unsigned int r)
{
	//ofstream fout("output.txt");
	//////////////////////////////////////////////////////////////////////////////////
	for(int k=0;k<l*2;k++)printf(" ");
	
	
	cout<<"Вызов "<<l<<" "<<r<<endl;
	//fout<<"Вызов "<<l<<" "<<r<<endl;
	unsigned int j;//дополнительная переменная для обмена
	if (l==r){ 
	/////////////////////////////////////////////////////////////////////////////////
			for(int k=0;k<l*3;k++)printf(" ");
		
		for(unsigned int i=1; i<= strCount; i++ )
			{ cout<<str[i]<<" ";
			//fout <<str[i]<<" ";
    		}
		cout<<endl;
		}
	else
	{for(unsigned int i=l; i<= r; i++ ){
			j=str[l]; str[l]=str[i];str[i]=j; //обмен a[l],a[i]
			permutation(l+1,r);				  // вызов новой генерации
			j=str[l]; str[l]=str[i];str[i]=j; //обмен a[l],a[i]
			}
	}
	//fout.close(); // закрываем файл
}

