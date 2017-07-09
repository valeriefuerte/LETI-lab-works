#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

struct Job{ //информация о работах
    int id; //номер работы
    int time; // длительность
    int a; //коэффициенты стоимости работ
    int b;
    Job(int _id = 0, int _a = 0, int _b = 0, int _time = 0): //конструктор
     id(_id), time(_time), a(_a), b(_b){}
};

ofstream fout("output.txt");//выходной файл

int upperBound; //верхняя граница
vector<Job> originVector(0); //начальный вектор
vector<Job> solutionVector(0); //вектор с решением
vector<Job> temporarySolutionVector(0); //временное решение
//Функции:
//void preMVG();
bool cmp(Job first, Job second); //сравнение
void inputData(); //ввод данных
void printVectorOfJob(const vector<Job> &v, unsigned int level); //печать данных
void mvg(vector<Job> &used, vector<Job> &unused, unsigned int level);//выполнение метода ветвей и границ
void calculateUpperBound(); //подсчет верхней границы
int calculateLowerBound(const queue<int> &used); //подсчет нижней границы
void printFile(const vector<Job> &v); //печать ответа

int main(/*int argc, char *argv[]*/)
{
    inputData(); //считывание данных
    calculateUpperBound(); //подсчет верхней границы

    vector<Job> used(0); //вектор с использованными значениями
    vector<Job> unused = originVector; //начальный вектор с неиспользованными значениями
    mvg(used, unused, 0); //МВГ

    cout << endl << endl << "--------------------" << endl << "Solution" << endl;
    solutionVector = temporarySolutionVector; //вывод решения
    printVectorOfJob(solutionVector, 0);
    printFile(solutionVector);
    return 0;
}


bool cmp(Job first, Job second) //сравнение
{
    if((first.a/first.time) >= (second.a/second.time)) //сравниваваем отношения коэф а и длительности работы
    {
        return true;
    }
    else
    {
        return false;
    }
}

void inputData() //ввод данных
{
    cout << "Input type: 0-console, 1-file" << endl;
    unsigned int enter=0;
    cin >> enter;
    while (enter < 0 || enter > 1){
        cout << "try again!" << endl;
        cin >> enter;
    }

    unsigned int n;

    if (enter == 0) //ввод из консоли
    {
        cout << "Number of job is ";
        cin >> n; //ввод количества работ
        if (n <= 0) {
                    cout<<"Number of job can not have this value";
                    exit(1);
        }
        for(unsigned int i = 0; i < n; i++)
        {
            int tmpA, tmpB, tmpTime;
            cout << "Job " << i+1;
            cout << ". Input coefficients a, b and time:" << endl;
            cin >> tmpA >> tmpB >> tmpTime;
            if (tmpA <= 0)
            {
                cout<<"Coefficient a can not have this value";
                exit(1);
            }
            if (tmpB < 0) {
                cout<<"Coefficient b can not have this value";
                exit(1);
            }
            if (tmpTime < 0) {
                cout<<"Time can not have this value";
                exit(1);
            }
            Job tmpJob(i, tmpA, tmpB, tmpTime);
            originVector.push_back(tmpJob); //заносим данные в вектор
        }
    }

    if (enter == 1) //ввод из файла
    {
        ifstream fin("input.txt"); //подключение файла для ввода
        if (!fin.is_open())
                {
                    cerr << "File input does not open!" << endl;
                    exit(0);
                }

        fin >> n; //ввод количества работ
        if (n <= 0) {
                    cout<<"Number of job can not have this value";
                    exit(1);
        }
        cout << "Number of job is " << n << endl;
        for(unsigned int i = 0; i < n; i++)
        {
            int tmpA, tmpB, tmpTime;
            cout << "Job " << i+1;
            cout << ": function: ";
            fin >> tmpA >> tmpB >> tmpTime;
            if (tmpA <= 0)
            {
                cout<<"Coefficient a can not have this value";
                exit(1);
            }
            if (tmpB < 0) {
                cout<<"Coefficient b can not have this value";
                exit(1);
            }
            if (tmpTime < 0) {
                cout<<"Time can not have this value";
                exit(1);
            }
            cout << tmpA << "t+"<< tmpB << ", time: " << tmpTime << endl;
            Job tmpJob(i, tmpA, tmpB, tmpTime);
            originVector.push_back(tmpJob); //заносим данные в вектор
        }

        fin.close(); //закрываем файл
    }

}

void printVectorOfJob(const vector<Job> &v, unsigned int level) //печать данных
{
    for(unsigned int i = 0; i < level; i++) //проходим по всем уровням
    {
        cout << "| ";
    }
    cout << endl;
    for(auto it : v)
    {
        for(unsigned int i = 0; i < level; i++)
        {
            cout << "| ";
        }
        //выводим номер работы, коэффициенты и длительность
        cout << it.id+1 << "job";
        cout.width(4);
        cout << it.a << "t+" << it.b;
        cout.width(4);
        cout << "t=" << it.time << endl;
    }
    for(unsigned int i = 0; i < level; i++)
    {
        cout << "| ";
    }
    cout << endl;
}

void calculateUpperBound() //подсчет верхней границы
{
    solutionVector = originVector;
    sort(solutionVector.begin(), solutionVector.end(), cmp);//сортируем вектор решения
    upperBound = 0; //верхняя граница

    //preMVG();

    if(solutionVector.size() > 0)
    {
        vector<int> cache(solutionVector.size(), 0);

        cache[0] = solutionVector[0].time; //заносим длительности в кэш
        upperBound += cache[0] * solutionVector[0].a; //подсчитываем границу

        for(unsigned int i = 1; i < solutionVector.size(); i++)
        {
           cache[i] = cache[i - 1] + solutionVector[i].time;
           upperBound += cache[i] * solutionVector[i].a;
        }
    }
}

int calculateLowerBound(const vector<Job> &v) //подсчет нижней границы
{
    int lowerBound = 0; //нижняя граница
    vector<int> cache(v.size(), 0);
    if(v.size() > 0)
    {
        cache[0] = v[0].time;//заносим длительности в кэш
        lowerBound += cache[0] * v[0].a; //подсчитываем границу

        for(unsigned int i = 1; i < v.size(); i++)
        {
            cache[i] = cache[i - 1] + v[i].time;
            lowerBound += cache[i] * v[i].a;
        }
    }
    return lowerBound;
}

//void preMVG()
//{
//    for(auto it : originVector)
//    {
//        upperBound += it.b;
//    }
//}

void mvg(vector<Job> &used, vector<Job> &unused, unsigned int level)
{
    int lowerBound = calculateLowerBound(used); //подсчитваем нижнюю границу
    printVectorOfJob(used, level); //печатаем вектор

    if(lowerBound < upperBound)//если нижняя граница < верхней
    {
        if(unused.size() > 0) //пока не используем все значения
        {
            for(unsigned int i = 0; i < unused.size(); i++)
            {
                Job tmp = unused[i];//запоминаем неиспользованные значения
                used.push_back(tmp);
                unused.erase(unused.begin() + i);//удаляем значение
                mvg(used, unused, ++level);//МВГ
                used.pop_back();
                unused.insert(unused.begin() + i, tmp);//добавляем значение
                level--;//возвращаемся вверх
            }
        }
        else
        {
            for(unsigned int i = 0; i < level; i++)
            {
                cout << "| ";
            }
            cout << "New upper bound" << endl; //новая верняя граница
            temporarySolutionVector = used;
            upperBound = lowerBound;
        }
    }
    else
    {
        if(upperBound == lowerBound && unused.size() == 0)//если границы совпали и просмотрены все значения
        {
            for(unsigned int i = 0; i < level; i++)
            {
                cout << "| ";
            }
            cout << "Solution has finded" << endl;
            temporarySolutionVector = used;//решение найдено
        }
        else
        {
            for(unsigned int i = 0; i < level; i++)
            {
                cout << "| ";
            }
            cout << "Push branch off " << upperBound << " < " << lowerBound << endl;//откидываем
            level--;
        }
    }
}


void printFile(const vector<Job> &v) //печать решения
{
    for(auto it : v)
    {
        //выводим номер работы, коэффициенты и длительность
        fout << it.id+1 << "job";
        fout.width(4);
        fout << it.a << "t+" << it.b;
        fout.width(4);
        fout << "t=" << it.time << endl;
    }
}
