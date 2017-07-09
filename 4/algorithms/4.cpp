//�������������� ���������� �����
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstdlib>
using namespace std;
struct Job{ //���������� � �������
    double time; // ������������
    double a; //����������� ��������� ������
    double b;
};

const unsigned short Max = 256; //������������ ������ �������
double d[Max][Max]; //������ ��� ��

ofstream fout("output.txt");//�������� ����

//�������:
double costJob(double A, double B,double t ); //������ ��������� �����
void print (vector<Job> jobs, int num); //������ ������
void dinamic(vector<Job> jobs, int size); //���������� ��
//int compare(const void * x1, const void * x2)   //����������
//{
//  return ( *(int*)x2 - *(int*)x1 );
//}

double costJob(double A, double B, double t ){ //������ ��������� �����
	return (A * t + B);
}

void print (vector<Job> jobs, int num) //������ ������
{
	Job work;
	cout<<"\n������ ������ ���: " << endl;
	for(int i=0; i<num;i++){
		cout << i + 1 << " ������: ";
		work=jobs[i];   //.pop_back();
		cout << "���������� ������� ���������:  " << work.a << "x+" << work.b << endl;
		cout<<"������������: "<<work.time;
		cout<<"   ���������: "<<costJob(work.a,work.b,work.time)<<endl<<endl;
	}
}

int main()
{
    setlocale(LC_ALL,"Russian");
    int num=0;
	vector<Job> jobs;
    Job job;
    ifstream fin("input.txt"); //����������� ����� ��� �����

	int enter;
	cout << "�������� ��� ����� ������:" << endl;
	cout << "1 �� �������" << endl;
	cout << "2 �� �����" << endl;
	cin >> enter;
	
	while ((enter<1) || (enter>2)) //�������� �� ������������ ���� �����
	{
		cout << "�������� ��� �����! ���������� �����.";
		cin >> enter;
	}

	
	if (enter==1){ //���� �� �������
		cout << "������� ���������� �����: ";
    	cin >> num;
    	if (num <= 0) {
    		cout<<"���������� ����� �� ����� ����� ��� ��������";
			exit(1);
		}
				
		for (int i = 0; i < num; i++)
        {
            cout << endl<< i + 1 << " ������: ";
            cout << "������� ������������ ���������� ������� ax+b: ";
			cin >> job.a;
			cin >> job.b;
            if (job.a <= 0) {
			cout<<"������� ��������� �� ����� ����� ��� ��������";
			exit(1);
			}
			if (job.b < 0) {
			cout<<"������� ��������� �� ����� ����� ��� ��������";
			exit(1);
			}
			
			cout << "������� ������������: ";
    		cin >> job.time;
			if (job.time <= 0) {
			cout<<"������������ �� ����� ����� ��� ��������";
			exit(1);
			}
		jobs.push_back(job);
		}
	}
	
	if (enter==2){ //���� �� �����
		if (!fin.is_open())
    	{
        	cerr << "���� input �� ����� ���� ������!" << endl;
        	exit(0);
    	}
    	
    	fin >> num;
    	if (num <= 0) {
			cout<<"���������� ����� �� ����� ����� ��� ��������";
			exit(1);
		}
    	cout << "���������� �����: " << num <<endl;
    	    	
    	for (int i = 0; i < num; i++)
        {
            fin >> job.a;
            fin >> job.b;
            if (job.a <= 0) {
			cout<<"������� ��������� �� ����� ����� ��� ��������";
			exit(1);
			}
			if (job.b < 0) {
			cout<<"������� ��������� �� ����� ����� ��� ��������";
			exit(1);
			}

			fin >> job.time;
			if (job.time <= 0) {
			cout<<"������������ �� ����� ����� ��� ��������";
			exit(1);
			}
			jobs.push_back(job);
		}
	}
	fin.close();
	print(jobs, num); //������ ������
	dinamic(jobs, num);//��
	return 0;
}

void dinamic(vector<Job> jobs, int size){
	Job work; double D;
	d[size][2*size-1]; //������� ��
	double array[size][3];//������� ��� ����������
	double ct[size][1];
	double summaryTime=0; //����� ������������
	
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
	
	cout << "��������� ������:" << endl;
	cout.width(5);
	cout << "� ";
	cout.width(4);
	cout << "t ";
	cout.width(6);
	cout << "a/t" << endl;
 	for (int i = 0; i < size; i++ ){
		work = jobs[i];
		d[i][0] = i+1;//������ �����
		cout.width(4);
		cout << d[i][0]; 
		d[i][1] = work.time;//������������
		cout.width(4);
		cout << d[i][1];
		summaryTime+=d[i][1];
		d[i][2] = ct[i][0];
//		d[i][2] = costJob(work.a,work.b,work.time); //���������
		cout.width(6);
		cout << d[i][2] << endl;  	
	}
	cout << endl;
	
	

//	for(int l = 0; l < size; l++){
//	cout <<	array[l][0] << " ";
//	cout << array[l][1] << " ";
//	cout << array[l][2] << " ";
//	}
	
	cout<<"���������� ������������� ����������������\n";
	cout.width(5);
	cout << "� ";
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
	for (int i = 0; i < size; i++ ){ //����� ������� �� ����� 1 ����
 		cout.width(4);
	 	cout << d[i][0]; 
		cout.width(4);
	 	cout << d[i][1]; 
		cout.width(6);
	 	cout << d[i][2]<<endl; 	
	}
				
//	unsigned int k = 3;
//	for (int flag = 1; flag < size; flag++){ //���� �� ������� ��� ������
//		cout<<"������� ��� ���������� ������������� ���������������� �� " << flag+1<<" ����\n";
//		cout.width(4);
//		cout << "�";
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
//					for (int h = 0; h <= k+1; h++){ //������������ ������
//				 		D=d[i][h]; d[i][h]=d[j][h];d[j][h]=D;
//				 	}
//				}
//			 }
//		}
		
//		for (int i = 0; i < size; i++ ){ //����� ������� �� ����� ������� ����
//			for (int j = 0; j <= k+1; j++){
//				cout.width(4);
//				if (d[i][j]) cout << d[i][j]; 
//				else cout << " ";
//			}
//	 	cout <<endl; 	
//		}
//		k = k+2;
//	}	
		
	cout <<"\n���������� �����:\n";
	for (int i = 0; i < size; i++ ){
 		cout.width(4);
	 	cout << d[i][0];
		fout << d[i][0] << " ";
	}
		
	cout<<"\n����� ����� "<<summaryTime;
}
