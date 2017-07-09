//программа формирования распределения количества попаданий псевдослучайных целых чисел в заданные интервалы
//реализуется в виде двух ассемблерных модулей (процедур), первый из которых формирует распределение исходных чисел 
//по интервалам единичной длины и возвращает его в вызывающую программу на ЯВУ как промежуточный результат. 
//Также это распределение выводится на экран и сохраняется в файле. Затем вызывается второй ассемблерный модуль, 
//который по этому промежуточному распределению формирует окончательное распределение псевдослучайных целых чисел 
//по интервалам произвольной длины ( с заданными границами ). Это распределение возвращается в головную программу и 
//выдается как основной результат в виде текстового файла и, возможно, графика.

//Замечание: На ЯВУ следует реализовать только ввод (возможно с контролем), вывод и генерацию псевдослучайных целых чисел. 
//Всю остальную функциональность следует программировать на ассемблере.

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <cinttypes>
#include <cstdlib>
using namespace std;
extern "C" void numCatch(int32_t NumRanDat, int32_t* RanDat, int32_t NInt, int32_t* LGrInt, int32_t* Freqs);

int compareInt32_t (const void * a, const void * b)
{
  return ( *(int32_t*)a - *(int32_t*)b );
}
int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Russian");
    istream& in = cin;
    // ifstream in("input.txt");
    ofstream fout("output.txt");

    cout << "Введите количество чисел NumRanDat (>0, <=16000)" << endl;
    int32_t NumRanDat;
    in >> NumRanDat;
    while (in.fail() || NumRanDat <= 0 || NumRanDat > 16000) {
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "NumRanDat не принадлежит промежутку допустимых значений, повторите ввод" << endl;
        in >> NumRanDat;
    }

    cout << "Введите интервал случайных чисел [Xmin, Xmax] через пробел" << endl;
    int32_t Xmin, Xmax;
    in >> Xmin >> Xmax;
    while (in.fail() || Xmin >= Xmax) {
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "Неправильно указаны границы, повторите ввод" << endl;
        in >> Xmin >> Xmax;
    }

    cout << "Введите количество промежутков разбиения NInt (>0, <=24)" << endl;
    int32_t NInt;
    in >> NInt;
    while (in.fail() || NInt <= 0 || NInt > 24) {
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "NInt не принадлежит промежутку допустимых значений, повторите ввод" << endl;
        in >> NInt;
    }

    int32_t* LGrInt = new int32_t[NInt+1];

    LGrInt[0]=Xmin;
    for (int32_t i = 1; i < NInt+1; ++i) {
        cout << "Введите левую границу LGrInt[" << i <<"], должна принадлежать ["<<Xmin<<","<<Xmax<<"]" << endl;
        in >> LGrInt[i];
        while (in.fail() || LGrInt[i] < Xmin || LGrInt[i] > Xmax) {
            in.clear();
            in.ignore(INT_MAX, '\n');
            cout << "Неверно указана граница, повторите ввод" << endl;
            in >> LGrInt[i];
        }
    }

    qsort(LGrInt, NInt, sizeof(int32_t), compareInt32_t);

    int32_t* RanDat = new int32_t[NumRanDat];
    mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int32_t> dist(Xmin, Xmax);
    for (int32_t i = 0; i < NumRanDat; ++i) {
        RanDat[i] = dist(rng);
    }

    int32_t* Freqs = new int32_t[NInt+1]();

    numCatch(NumRanDat, RanDat, NInt+1, LGrInt, Freqs);

    for (int32_t i = 0; i < NInt+1 ; ++i) {
        cout << LGrInt[i] << " " << Freqs[i] << endl;
        fout << LGrInt[i] << " " << Freqs[i] << endl;
    }

    return 0;
}