#include <iostream>
#include <fstream>
#include <vector> 
#include <stack>
#include <cstdlib>

using namespace std;
ifstream in("in.txt");
ofstream fout("out.txt");
typedef int Size_t;
typedef int Vector[2000000];
int compare (const void * a, const void * b);
void qsortxi(Vector a, Size_t size_t) 
{
	int compare=0,assign=0; //�������� ���������� ��������� � ������������
	int tmp, pivot; //�������� ��� ��������������� � �������
	stack <int> lows, highs; //�����
   	int low, high, i, j; //������������� ��������� ��������

	cout<<"������ ���������� "<<endl;
	fout<<"������ ���������� "<<endl;
	lows.push(0); //������� � ���� ���� 0
	highs.push(size_t ); //������� � ������ ���� ������ �������

	while (!lows.empty() ) //���� ���� �� ����
	 {
		low  = lows.top();  //��������� � ������� ��������
		lows.pop();			//������� 0
		high = highs.top(); //��������� � ������� ��������
		highs.pop();		//������� ������
		i = low;
		j = high;
		tmp = (int)(low + (high-low)/2); //���� ������� ������� ����������
		pivot = a[tmp];
		
		cout<<"�����: "<<low<<" ������� �������: "<<pivot<<" ������: "<<high<<endl;
		fout<<"�����: "<<low<<" ������� �������: "<<pivot<<" ������: "<<high<<endl;
		do {
			while (a[i] < pivot) { //���� ������� ������ ������� ������ ��������
				i++; compare++;
			}
			while (a[j] > pivot) { //���� ������� ����� ������� ������ ��������
				j--; compare++;
			}
			if (i <= j) { compare++; //���������� 2 ������� ��������
				if (a[i] > a[j]) {
					cout<<"����� ���������: a["<<i<<"]="<<a[i]<<" � a["<<j<<"]="<<a[j]<<endl;
					fout<<"����� ���������: a["<<i<<"]="<<a[i]<<" � a["<<j<<"]="<<a[j]<<endl;
					tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
					compare++;
					assign++;
				}
				i++; 
				if (j > 0) {
					j--; compare++;
				}
			}
		} while (i <= j); //�� ���� �� ������� i,j

		if (i < high) { compare++;
			lows.push(i);
			highs.push(high);
		}
		if (j > low) { compare++;
			lows.push(low);
			highs.push(j);
		}
		cout<<"������: ";
		fout<<"������: ";
		for(int k=0;k<=size_t;k++)
		{
		cout<<a[k]<<" ";
		fout<<a[k]<<" ";
		}
		cout<<endl;	fout<<endl;	
	}
	cout<<"���������� ���������= "<<compare<<endl;
	cout<<"���������� �������= "<<assign<<endl;
}

Vector vec;  
int main()
{ Size_t i=0;
    setlocale(LC_ALL, "rus"); // ���������� ����������� ���������
    int enter=0;
    cout<<"�������� ��� �����: 0-� �������, 1-�� ����� ";
   cin>>enter;
    if(enter==1) {
		if (!in.is_open()) // ���� ���� �� ������
			{cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
			exit(0);}
		else
		{ 	cout<<"������: ";
		while(!in.eof())
			{   in>>vec[i];
			 	cout << vec[i] << ' ';
		 		fout << vec[i] << ' ';
		 		i++;
        	}
		cout<<endl;
		fout<<endl;
		qsortxi( vec, i-1);	
		}}
	else{
		if(enter==0)
		{
		cout<<"������� ���������� ��������� � ������� ";
		Size_t size=0;
		cin>>size;
		cout<<"������� ������: ";
		while(i!=size)
			{   cin>>vec[i];
			 	fout << vec[i] << ' ';
		 		i++;
        	}
		cout<<endl;
		fout<<endl;	
		qsortxi(vec, size-1);
		}
		else {cout<<"������� ������ ��� ����� ������";
			exit(1);}
	}
	cout<<"��������������� ������: "<<endl;
	fout<<"��������������� ������: "<<endl;
	for(int k=0;k<i;k++)
	{
		cout<<vec[k]<<" ";
		fout<<vec[k]<<" ";
	}
	cout<<endl;
	fout<<endl;
	cout<<"��������� � ������������ �������� qsort: "<<endl;
	int n;
	qsort (vec, i, sizeof(int), compare);
	for (n=0; n<i; n++) printf ("%d ",vec[n]);
	in.close(); //�������� �����
	return 0;
}
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
