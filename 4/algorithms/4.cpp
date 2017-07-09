//минимизировать расписание работ
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstdlib>
using namespace std;
struct Job{ //информация о работах
    double time; // длительность
    double a; //коэффициент стоимости работы
    double b;
};

const unsigned short Max = 256; //максимальный размер массива
double d[Max][Max]; //массив для ДП

ofstream fout("output.txt");//выходной файл

//Функции:
double costJob(double A, double B,double t ); //расчет стоимости работ
void print (vector<Job> jobs, int num); //печать данных
void dinamic(vector<Job> jobs, int size); //реализация ДП
//int compare(const void * x1, const void * x2)   //сортировка
//{
//  return ( *(int*)x2 - *(int*)x1 );
//}

double costJob(double A, double B, double t ){ //расчет стоимости работ
	return (A * t + B);
}

void print (vector<Job> jobs, int num) //печать данных
{
	Job work;
	cout<<"\nРешить задачу для: " << endl;
	for(int i=0; i<num;i++){
		cout << i + 1 << " Работа : ";
		work=jobs[i];   //.pop_back();
		cout << "Монотонная функция стоимости:  " << work.a << "x+" << work.b << endl;
		cout<<"Длительность: "<<work.time;
		cout<<"   Стоимость: "<<costJob(work.a,work.b,work.time)<<endl<<endl;
	}
}

int main()
{
    setlocale(LC_ALL,"Russian");
    int num=0;
	vector<Job> jobs;
    Job job;
    ifstream fin("input.txt"); //подключение файла для ввода

	int enter;
	cout << "Выберите тип ввода данных:" << endl;
	cout << "1 Из консоли" << endl;
	cout << "2 Из файла" << endl;
	cin >> enter;
	
	while ((enter<1) || (enter>2)) //проверка на корректность типа ввода
	{
		cout << "Неверный тип ввода! Попробуйте снова.";
		cin >> enter;
	}

	
	if (enter==1){ //ввод из консоли
		cout << "Введите количество работ: ";
    	cin >> num;
    	if (num <= 0) {
    		cout<<"Количество работ не может иметь это значение";
			exit(1);
		}
				
		for (int i = 0; i < num; i++)
        {
            cout << endl<< i + 1 << " работа: ";
            cout << "Введите коэффициенты монотонной функции ax+b: ";
			cin >> job.a;
			cin >> job.b;
            if (job.a <= 0) {
			cout<<"Функция стоимости не может иметь это значение";
			exit(1);
			}
			if (job.b < 0) {
			cout<<"Функция стоимости не может иметь это значение";
			exit(1);
			}
			
			cout << "Введите длительность: ";
    		cin >> job.time;
			if (job.time <= 0) {
			cout<<"Длительность не может иметь это значение";
			exit(1);
			}
		jobs.push_back(job);
		}
	}
	
	if (enter==2){ //ввод из файла
		if (!fin.is_open())
    	{
        	cerr << "Файл input не может быть открыт!" << endl;
        	exit(0);
    	}
    	
    	fin >> num;
    	if (num <= 0) {
			cout<<"Количество работ не может иметь это значение";
			exit(1);
		}
    	cout << "Количество работ: " << num <<endl;
    	    	
    	for (int i = 0; i < num; i++)
        {
            fin >> job.a;
            fin >> job.b;
            if (job.a <= 0) {
			cout<<"Функция стоимости не может иметь это значение";
			exit(1);
			}
			if (job.b < 0) {
			cout<<"Функция стоимости не может иметь это значение";
			exit(1);
			}

			fin >> job.time;
			if (job.time <= 0) {
			cout<<"Длительность не может иметь это значение";
			exit(1);
			}
			jobs.push_back(job);
		}
	}
	fin.close();
	print(jobs, num); //печать данных
	dinamic(jobs, num);//ДП
	return 0;
}

void dinamic(vector<Job> jobs, int size){
	Job work; double D;
	d[size][2*size-1]; //матрица ДП
	double array[size][3];//матрица для стоимостей
	double ct[size][1];
	double summaryTime=0; //общая длительность
	
	for(int l = 0; l < size; l++){
		array[l][0] = l+1;
		work = jobs[l];
		array[l][1] = work.a;
		array[l][2] = work.b;
	}
	for(int l = 0; l < size; l++){
		work = jobs[l];
		ct[l][0] = work.a / work.time;
//		cout << ct[l][0];
	}
	
	cout << "Начальные данные:" << endl;
	cout.width(5);
	cout << "№ ";
	cout.width(4);
	cout << "t ";
	cout.width(6);
	cout << "a/t" << endl;
 	for (int i = 0; i < size; i++ ){
		work = jobs[i];
		d[i][0] = i+1;//номера работ
		cout.width(4);
		cout << d[i][0]; 
		d[i][1] = work.time;//длительности
		cout.width(4);
		cout << d[i][1];
		summaryTime+=d[i][1];
		d[i][2] = ct[i][0];
//		d[i][2] = costJob(work.a,work.b,work.time); //стоимости
		cout.width(6);
		cout << d[i][2] << endl;  	
	}
	cout << endl;
	
	

//	for(int l = 0; l < size; l++){
//	cout <<	array[l][0] << " ";
//	cout << array[l][1] << " ";
//	cout << array[l][2] << " ";
//	}
	
	cout<<"Применение динамического программирования\n";
	cout.width(5);
	cout << "№ ";
	cout.width(4);
	cout << "t ";
	cout.width(5);
	cout << "a/t" << endl;
	for (int i = 0; i < size; i++ )
	{
		for (int j = i+1; j < size; j++ ){
			if ( d[i][2] < d[j][2] ){
//				qsort(d, size, sizeof(int), compare);
				D=d[i][2]; d[i][2]=d[j][2];d[j][2]=D;
				D=d[i][0]; d[i][0]=d[j][0];d[j][0]=D;
				D=d[i][1]; d[i][1]=d[j][1];d[j][1]=D;
			}
		}
	}
	for (int i = 0; i < size; i++ ){ //вывод матрицы ДП после 1 шага
 		cout.width(4);
	 	cout << d[i][0]; 
		cout.width(4);
	 	cout << d[i][1]; 
		cout.width(6);
	 	cout << d[i][2]<<endl; 	
	}
				
//	unsigned int k = 3;
//	for (int flag = 1; flag < size; flag++){ //пока не выберем все работы
//		cout<<"Матрица для применения динамического программирования на " << flag+1<<" шаге\n";
//		cout.width(4);
//		cout << "№";
//		for (int i = 0; i < size; i++){
//			cout.width(4);
//			cout << "t";
//			cout.width(4);
//			cout << "c";	
//		}
//		cout << endl;
//		for (int i = flag; i < size; i++ )
//		{
//			 int a,b;
//			 for (int l = 0; l < size; l++){
//			 	if (d[i][0] == array[l][0]){
//			 		a = array[l][1];
//			 		b = array[l][2];
////			 		cout <<a<<b<<endl;
//				 }
//			 }
//			 
//			 for (int j = k; j <= k+1; j++ ){
//			 	d[i][k] = d[flag-1][1]+d[i][k-2];
//				d[i][k+1] = costJob(a,b,d[i][k]);
////			 	cout << array[i][1]<< " ";
////			 	cout << array[i][2] << " ";
////			 	cout << d[i][k] << endl;
//			 }
//		}
		
//		for (int i = flag; i < size; i++ )
//		{
//			 for (int j = i+1; j < size; j++ ){
//			 	if ( ct[i][0] < ct[j][0] ){
////				 if (d[i][k+1]>d[j][k+1]){
//					for (int h = 0; h <= k+1; h++){ //переставляем работы
//				 		D=d[i][h]; d[i][h]=d[j][h];d[j][h]=D;
//				 	}
//				}
//			 }
//		}
		
//		for (int i = 0; i < size; i++ ){ //вывод матрицы ДП после каждого шага
//			for (int j = 0; j <= k+1; j++){
//				cout.width(4);
//				if (d[i][j]) cout << d[i][j]; 
//				else cout << " ";
//			}
//	 	cout <<endl; 	
//		}
//		k = k+2;
//	}	
		
	cout <<"\nРасписание работ:\n";
	for (int i = 0; i < size; i++ ){
 		cout.width(4);
	 	cout << d[i][0];
		fout << d[i][0] << " ";
	}
		
	cout<<"\nОбщее время "<<summaryTime;
}
