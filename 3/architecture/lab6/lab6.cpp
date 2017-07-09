//��������� ������������ ������������� ���������� ��������� ��������������� ����� ����� � �������� ���������
//����������� � ���� ���� ������������ ������� (��������), ������ �� ������� ��������� ������������� �������� ����� 
//�� ���������� ��������� ����� � ���������� ��� � ���������� ��������� �� ��� ��� ������������� ���������. 
//����� ��� ������������� ��������� �� ����� � ����������� � �����. ����� ���������� ������ ������������ ������, 
//������� �� ����� �������������� ������������� ��������� ������������� ������������� ��������������� ����� ����� 
//�� ���������� ������������ ����� ( � ��������� ��������� ). ��� ������������� ������������ � �������� ��������� � 
//�������� ��� �������� ��������� � ���� ���������� ����� �, ��������, �������.

//���������: �� ��� ������� ����������� ������ ���� (�������� � ���������), ����� � ��������� ��������������� ����� �����. 
//��� ��������� ���������������� ������� ��������������� �� ����������.

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

    cout << "������� ���������� ����� NumRanDat (>0, <=16000)" << endl;
    int32_t NumRanDat;
    in >> NumRanDat;
    while (in.fail() || NumRanDat <= 0 || NumRanDat > 16000) {
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "NumRanDat �� ����������� ���������� ���������� ��������, ��������� ����" << endl;
        in >> NumRanDat;
    }

    cout << "������� �������� ��������� ����� [Xmin, Xmax] ����� ������" << endl;
    int32_t Xmin, Xmax;
    in >> Xmin >> Xmax;
    while (in.fail() || Xmin >= Xmax) {
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "����������� ������� �������, ��������� ����" << endl;
        in >> Xmin >> Xmax;
    }

    cout << "������� ���������� ����������� ��������� NInt (>0, <=24)" << endl;
    int32_t NInt;
    in >> NInt;
    while (in.fail() || NInt <= 0 || NInt > 24) {
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << "NInt �� ����������� ���������� ���������� ��������, ��������� ����" << endl;
        in >> NInt;
    }

    int32_t* LGrInt = new int32_t[NInt+1];

    LGrInt[0]=Xmin;
    for (int32_t i = 1; i < NInt+1; ++i) {
        cout << "������� ����� ������� LGrInt[" << i <<"], ������ ������������ ["<<Xmin<<","<<Xmax<<"]" << endl;
        in >> LGrInt[i];
        while (in.fail() || LGrInt[i] < Xmin || LGrInt[i] > Xmax) {
            in.clear();
            in.ignore(INT_MAX, '\n');
            cout << "������� ������� �������, ��������� ����" << endl;
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