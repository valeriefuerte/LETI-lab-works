//���������� ��������� ���������� ����� F, 
//������������ �� ������, ���������� � ��������� ���� G, 
//��������� ������ ������ ������ � �������� �������.
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
using namespace std;

struct str;
void Stack(vector<string>  lit,int size); //������� ������ � ��������� �� � ����
void Rewrite(vector<string>  lit,int size); //�������, ����������� �������
//��������� ������
struct str {
    vector<string> lit ();
};

int main()
{
	setlocale(LC_ALL,"Russian");
    cout<<"�������� ��� ����� ������ \n";
    cout<<"0 - �������, 1 - ���� \n";
    int enter=0;
    cin>>enter;
    int vecSize = 0; //������ �������
    vector<string> lit(vecSize);
    //���� �� �������
	if(enter == 0) { cout<<"ok";
/*	cout<<"������� ���������� �����  ";
	cin >> vecSize;//������ �������
	vector<string> lit();
	if(vecSize>100) {cerr<<"������! ������� ������ � ����������� ����� ������ 100!";
	exit(1);}
	else{
		for(int i = 0; i < vecSize; i++) {
	        		cin >> lit[i];
	        		//lit.push_back();
   					}
   		int size=lit.size();
    	cout<<"����� �������"<<size;

	}*/
	}
    else{ 
		if(enter == 1) { //���� �� �����
    		ifstream fin("in.txt");
   			if (!fin.is_open())
   			{
       			 cerr << "���� input �� ����� ���� ������!" << endl;
       		 	return 1;
   		 	}
   			//fin>>vecSize;
   				
		
			   int size=lit.size();
			   	   vector<string> lit(size);
				cout<<"���������� �����: "<<size<<endl;
   				for(int i = 0; i < size; i++) { fin>>lit[i];
   				//	lit.push_back(vecSize);
					cout << lit[i] << ' ';}
			}
    	else {cerr<<"������� ������ ��� ����� ������!\n";
			exit(3);}
	}
//	cout<<"����� ��������  ";
//	for(int i = 0; i < vecSize; i++) { 
//					cout << lit[i] << ' ';}
					
   // Rewrite(lit, vecSize); //�������, ����������� �������
    return 0;
}
void Stack(vector<string>  lit,int size)
{
	
}
/*
void Rewrite(vector<string> lit,int size)
{
	ofstream fout("out.txt"); // ������ ������ ������ ofstream ��� ������ � ��������� ��� � ������
	int i=size;cout<<"\n � �������� �������: \n"<<i;
	while (i>=0) 
	{
	//	cout<<lit[i]<<" \n";
		for (int j=lit[i].size()-1; j>=0; j--)
		{cout<<lit[i][j];
		fout<<lit[i][j]; // ������ ������ � ����
		}
		cout<<" \n";
		fout<<endl;
		i--;
	}
	fout.close(); // ��������� ����
}*/
