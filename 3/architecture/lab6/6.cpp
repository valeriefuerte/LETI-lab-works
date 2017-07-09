#include <iostream>
#include <fstream>
#include <locale>
#include <string.h>
#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <list>
#include <ctype.h>
#include <random>
#include <ratio>
#include <chrono>
#include <cinttypes>

using namespace std;

extern "C" {
    // void count(int NumRanDat, int* RanDat, int FInt, int* LGrInt, int* Freqs); 
    void first(int NumRanDat, int* RanDat, int Xmin, int* fInt);
    void second(int* LGrInt, int NInt, int* fInt, int fIntSize, int Xmax, int* Freqs);
}

int compareInt32_t (const void * a, const void * b)
{
  return ( *(int32_t*)a - *(int32_t*)b );
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    ofstream fout("output.txt");
    istream& in = cin;

    cout << "¬ведите количество чисел NumRanDat (>0, <=16000)" << endl;
    int NumRanDat;
    in >> NumRanDat;
    while (in.fail() || NumRanDat <= 0 || NumRanDat > 16000) {
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "NumRanDat не принадлежит промежутку допустимых значений, повторите ввод." << endl;
        in >> NumRanDat;
    }

    cout << "¬ведите интервал случайных чисел[Xmin, Xmax]" << endl;
    int Xmin, Xmax;
    in >> Xmin >> Xmax;
    while (in.fail() || Xmin >= Xmax) {
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "Ќеправильно указаны граничные значени€, повторите ввод." << endl;
        in >> Xmin >> Xmax;
    }

    //cout<<"–аспределение по интервалам единичный длины: "<<endl;
    //LGrInt[NInt+1];
    
    cout << "¬ведите количество промежутков разбиени€ NInt (>0, <=24)" << endl;
    int NInt;
    in >> NInt;
    while (in.fail() || NInt <= 0 || NInt > 24) {
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "NInt не принадлежит промежутку допустимых значений, повторите ввод" << endl;
        in >> NInt;
    }

    ++NInt;

    int LGrInt[25];
    LGrInt[0]=Xmin;
    for (int i = 1; i < NInt; ++i) {
        cout << "¬ведите левую границу LGrInt[" << i <<"], должна принадлежать ["<<Xmin<<","<<Xmax<<"]" << endl;
        in >> LGrInt[i];
        while (in.fail() || LGrInt[i] < Xmin || LGrInt[i] > Xmax) {
            in.clear();
            in.ignore(INT_MAX, '\n');
            cout << "Ќеверно указана граница, повторите ввод" << endl;
            in >> LGrInt[i];
        }
    }
    for (int i=NInt-1; i>=0; i--)
    {
    	for(int j=0; j<i; j++)
    	{
    		if (LGrInt[j]>LGrInt[j+1])
    		{
    			int tmp=LGrInt[j];
    			LGrInt[j]=LGrInt[j+1];
    			LGrInt[j+1]=tmp;
    		}
    	}
    }
    // cout<< "LGrInt[0] " <<LGrInt[0]<<endl;
    /*int i=1;
    while (LGrInt[i]>Xmax) {
        cout << " LGrInt[" << i <<"]  ";// << endl;
        LGrInt[i]=LGrInt[i-1]+1;
        i++;
    }*/
 //    int i = 0;
 //   	do  {i++;
 //    	LGrInt[i]=LGrInt[i-1]+1;
 //    	 cout << " LGrInt[" << i <<"]  "<<LGrInt[i];// << endl;
	// }while(  LGrInt[i]<=Xmax);
 //    int FInt=i;
	// cout<<endl<<" оличество промежутков единичной длины "<<FInt<<endl;
	   
    int RanDat[16000] = {0};

    // RanDat[NumRanDat];
    mt19937 rng(chrono::system_clock::now().time_since_epoch().count()); //генератор случайных чисел
    uniform_int_distribution<int> dist(Xmin, Xmax);
    for (int i = 0; i < NumRanDat; ++i) {
        RanDat[i] = dist(rng);
    }
    
    // const unsigned int Max = 16001;           //ћаксимальное количество элементов массива
    // int fInt[16000] = {0};
    int fIntSize = Xmax-Xmin+1; // размер интервала
    int* fInt = new int[fIntSize]();
    first(NumRanDat,RanDat,Xmin,fInt);

    // void first(int NumRanDat, int* RanDat, int Xmin, int* fInt);

    for (int i = 0; i < fIntSize; ++i)
    {
        cout << i+Xmin << ' ' << fInt[i] << endl;
    }

    int Freqs[25];

    //void second(int* LGrInt, int NInt, int* fInt, int NumRanDat, int Xmax, int* Freqs);
    second(LGrInt, NInt, fInt, fIntSize, Xmax, Freqs);
    ofstream fin("out.txt");
    for (int i = 0; i < NInt; ++i)
    {
        cout <<"»нтервал"<< i << " " <<LGrInt[i] << ' ' << Freqs[i] << endl;
        fin <<"»нтервал"<< i << " " <<LGrInt[i] << ' ' << Freqs[i] << endl;
    }
    fin.close();
	// int* Freqs = new int[FInt+1]();
 //    count(NumRanDat, RanDat, FInt+1, LGrInt, Freqs);
 //    for (int i = 0; i < FInt+1 ; ++i) {
 //        cout << LGrInt[i] << " " << Freqs[i] << endl;
 //        fout << LGrInt[i] << " " << Freqs[i] << endl;
 //    }
   
	// cout << "¬ведите количество промежутков разбиени€ NInt (>0, <=24)" << endl;
 //    int NInt;
 //    in >> NInt;
 //    while (in.fail() || NInt <= 0 || NInt > 24) {
 //        in.clear();
 //        in.ignore(INT_MAX, '\n');
 //        cout << "NInt не принадлежит промежутку допустимых значений, повторите ввод." << endl;
 //        in >> NInt;
 //    }
	    
 //    fout.close();
    return 0;
}
