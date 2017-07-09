#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <fstream>
using namespace std;

ifstream infile("input.txt"); //файл ввода
ofstream outfile("output.txt"); //файл вывода

const int MAXN = 1933; //максимальное значение
vector<int> g[MAXN]; //вектор смежности
int mx[MAXN][MAXN]; //матрица смежности
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];
unsigned int n; // количество вершин

vector< pair<int, int> > bridges; //мосты

void dfs (int v, int p = -1); //обход в глубину
void find_bridges(); //поиск мостов
void isBridge(int source, int destination); //проверка на мост
void inputData(); //ввод данных
void convertMatrixToAdjacenciesList(); //конвертация из матрицы в список смежности
void randomGenerator(); //рандомная генерация
void printGraphState(); //печать графа

int main(/*int argc, char *argv[]*/)
{
    cout << "Graph type: 0-input, 1-random" << endl;
    unsigned int enter=0; //ввод вручную или генерация
    cin >> enter;
    while (enter < 0 || enter > 1){
            cout << "try again!" << endl;
            cin >> enter;
    }

    if (enter == 0) //ввод графа
    {
        inputData();
        printGraphState(); //печать
    }

    if (enter == 1){ //генерация графа
        randomGenerator();
    }

    cout << "Bridges is finding" <<endl;
    find_bridges(); //поиск мостов

    cout << "Bridges: " << endl;
    if(bridges.size() == 0)
    {
        cout << "bridges not found!";
        exit(1);
    }
    else
    {
        for(auto it : bridges) //вывод мостов
        {
            cout << it.first << " " << it.second << endl;
            outfile << it.first << " " << it.second << endl;
        }
        cout << endl;
        outfile << endl;
    }
    return 0;
}

void dfs (int v, int p) { //поиск в глубину
    used[v] = true; //v - начальная вершина
    tin[v] = fup[v] = timer++; //tin[v] - время захода в вершину v
    for (size_t i=0; i<g[v].size(); ++i) { //ходим по всему вектору
        int to = g[v][i];
        if (to == p)  continue;
        if (used[to])
            //время fup[v]  == min из времени
            //захода в вершину tin[v] и времен захода
            //в каждую вершину p
            fup[v] = min (fup[v], tin[to]);
        else {
            dfs (to, v); //поиск в глубину
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] > tin[v]) //является ли ребро мостом
                isBridge(v,to);
        }
    }
}

void find_bridges() { //поиск мостов
    timer = 0;
    for (int i=0; i<n; ++i)
        used[i] = false; //критерий ребра дерева поиска
    for (int i=0; i<n; ++i)
        if (!used[i])
            dfs (i);
}

void isBridge(int source, int destination) //проверка на мост
{
    bridges.push_back(make_pair(source, destination));
}

void inputData() //ввод данных
{
    char inputType; //выбор типа ввода
    cout << "Choosr input type: 0 - from console; 1 - from file" << endl;
    cin >> inputType;
    if(inputType == '1') //ввод из файла
    {
        cout << "input type switched to file" << endl;
        cout << "The content of input type is:" << endl;
        infile >> n; //считывание количества вершин
        cout << n << endl;
        if(n > MAXN)
        {
            cout << "Number of vertices must be nonnegative" << endl;
            exit(1);
        }
        cout << "Graph: " << endl; //вывод графа
        for(unsigned int i = 0; i < n; i++)
        {

            vector<int> tmpVector;
            for(unsigned int j = 0; j < n; j++)
            {
                int tmp;
                infile >> tmp;
                // check item
                if(tmp != 0)
                {
                    tmpVector.push_back(j);
                }
            }
            g[i] = tmpVector;
        }
       printGraphState(); //печать графа
    }
    else //ввод из консоли
    {
        cout << "Input number of vertices: ";
        cin >> n; //считывание количества вершин
        if(n > MAXN)
        {
            cout << "Number of vertices must be nonnegative" << endl;
            return;
        }
        cout << "Input graph: " << endl; //ввод графа
        for(unsigned int i = 0; i < n; i++)
        {
            vector<int> tmpVector;
            for(unsigned int j = 0; j < n; j++)
            {
                int tmp;
                cin >> tmp;
                // check item
                if(tmp != 0)
                {
                    tmpVector.push_back(j);
                }
            }
            g[i] = tmpVector;
        }
    }
}

void printGraphState() //печать графа
{
    for(unsigned int i = 0; i < n; i++)
    {
        for(unsigned int j = 0; j < g[i].size(); j++)
        {
            cout << g[i][j] << " "; //печать вектора смежности
        }
        cout << endl;
    }
}

void randomGenerator() //рандомная генерация
{
    cout << "Input Vertices count" << endl;
    cin >> n; //ввод количества вершин
    int density = -1; //ввод плотности
    cout << "Input Density" << endl;
    while(density < 0)
    {
        cin >> density;
        if(density < 0)
        {
            cout << "Try again" << endl;
        }
    }
    if (density > 100)
    {
        cout << "density can not have this value!";
        exit(1);
    }
    unsigned int count = n*n*density/100; //подсчет ребер
    cout << "Edges count in graph = " << count <<endl;
    unsigned int real_count = 0;

    srand(time(0)); //генерация
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            mx[i][j] = 0;
        }
    }
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if (mx[i][j]) break;
            else{
                if (real_count != count){
                    mx[i][j] = rand() % 2;
                    if (mx[i][j]) {
                        mx[j][i] = 1;
                        real_count++;
                    }
                }
            }
        }
    }

    convertMatrixToAdjacenciesList();
    printGraphState();
}

void convertMatrixToAdjacenciesList()  //конвертация из матрицы в список смежности
{
    for(unsigned int i = 0; i < MAXN; i++)
    {
        g[i] = vector<int>(0);
    }

    for(unsigned int i = 0; i < n; i++)
    {
        vector<int> tmpVector(0);
        for(unsigned int j = 0; j < n; j++)
        {
            if(mx[i][j] != 0)
            {
                tmpVector.push_back(j);
            }
        }
        g[i] = tmpVector;
    }
}
