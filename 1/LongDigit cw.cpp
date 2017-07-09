#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

const unsigned short Max_n = 10000; 	  //������������ ���������� ��������� �������
typedef unsigned int arrDigital [Max_n] ; //�������� ���� �������
typedef unsigned short arrCount;		  //�������� ���� ��� ���������� ��������� �������
typedef char strDigital[10000]; 		  //��� ������ �� ����� ������ �������� �����
typedef short T; 						  // ��� �������� ���������� ��� �������� �������
//typedef	unsigned short F;			  // ��� ��� ����� ���� ��������� ������������� ��� �������������	  

//������� ������ ��������� � ������ � ������ �� �����
void readArr ( const int t, const strDigital strN, arrDigital &arr,arrCount &count ); 
void writeArr ( arrDigital &arr,arrCount &count);
void writeStr (  arrDigital &arr, arrCount &count, const unsigned short f, const T &tT);

void addArr(arrDigital  &a, arrCount &counta, arrDigital  &b, arrCount &countb, T &tT);
void subtract(arrDigital  &a, arrCount &counta, arrDigital  &b, arrCount &countb, T &tT);
int main ( )
{	setlocale (0,""); // ����������� �������� �����

 T tCount; // �������� ���������� ��� �������� �������
 strDigital strNumber1, strNumber2, strRezult; // ������ �� �����=������
 arrDigital arrA,arrB={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // �������
 arrCount countA,countB;			// ���������� ��������� � �������
 char operation;
unsigned short flag=0;  //���� ��������� �������������

	ifstream infile ("in_data.txt"); //������ ������� �� �����
    ofstream outfile ("out_data.txt"); //������ ������������ �  ����

	if (!infile) {cout << "������� ���� �� ������!" << endl; return 0;
	}

	cout << "������� ���������� ��� �������� ������� : ";
    cin >> tCount;
    
    cout << "������� �������� + ����� ��� - �������� : ";
    cin >> operation;
    
    infile >> strNumber1;
    infile >> strNumber2;
    
    cout << "����� ������: " << strNumber1 <<  endl; 
    cout << "����� ������: " << strNumber2 <<  endl;
   
	if(strlen(strNumber1)>strlen(strNumber2)) // ����  ����� ������� ����� ������ ����� �������
		{
			readArr(tCount,strNumber1,arrA,countA);
	    	readArr(tCount,strNumber2,arrB,countB);
	    
	    }
	else 	if(strlen(strNumber1)<strlen(strNumber2)) // ���� ����� ������� ����� ������ ����� �������
			{ 	if (operation=='-') flag=1;
				readArr(tCount,strNumber2,arrA,countA);
	    		readArr(tCount,strNumber1,arrB,countB);
			}
			else 	// ���� ���������� ���� �����
			{	readArr(tCount,strNumber1,arrA,countA);
	    		readArr(tCount,strNumber2,arrB,countB);
				if (operation=='-') 
				// ��� �������� ��������� ����� ������ ����� ���� ������ �������
				// ���� �� ��� ������ ������� ����� aarA �������� ������� �����
				{ for (int i=countA; i>=0; i--) if (arrA[i]<arrB[i])  {
										 	flag=1;
											readArr(tCount,strNumber2,arrA,countA);
	    									readArr(tCount,strNumber1,arrB,countB);
	    									break; // ����� �� �����
											}
				}
			}
	writeArr(arrA,countA);
	writeArr(arrB,countB);  
	if (operation=='+')
	{   
		addArr(arrA, countA, arrB, countB, tCount);
	}
    else{
		
		subtract(arrA, countA, arrB, countB, tCount);
    }; 
	writeArr(arrA,countA);
	writeStr(arrA,countA,flag, tCount);

	infile.close();
	outfile.close();
	return 0;
}
void readArr ( const int t, const strDigital strN, arrDigital &arr, arrCount &count)  //������� ������ ��������� � ������
{   count=0;		//���������� ��������� � �������
    char  s[t-1];  	// ������ ��� ������ �������� �������
	int len=strlen(strN);
//  cout <<"����� ������ = "<< len<<  endl; 
   
   while (t*(count+1)<=len) //���� �� ��������� ������
   {     
      for (int i=0;i<t;i++) s[i]=strN[len-t*(count+1)+i] ; // ������������ ������ ��� ����� �������
      arr[count]=  atoi(s);			// ���������� �������� ������� ������ (�������������� ������ � �����)
    
//	 cout<<count<<" =  "<<arr[count]  << endl;
     count++;	//����������� ���������� ��������� �������
   }
   
   // ������������ ���������� �������� ������� ���� ���������� ��������� � ������ �� ������� ������ �� �
   if(len%t!=0)   
   { 
   int m=len%t;
   memset (s,' ',t);
   strcat (s,"\0");
   for (int i=0;i<m;i++) s[t-m+i]=strN[i] ;
   arr[count]=  atoi(s);
//   cout<<count<<" =  "<<arr[count]<< endl;
    }
	else count--;
  
}

 void writeArr (  arrDigital &arr, arrCount &count) //������� ������ �������
{
	int n = count;
	cout << "WriteArr: " <<  n << endl; 
	for (int i=0; i<=n; i++) cout << i<<" = " << arr[i]<< endl;; // ����� �������
	
}
void writeStr (  arrDigital &arr, arrCount &count,const unsigned short f, const T &tT) //������� ������ ������� �������
{
	cout << "���������: " << endl;
	if (f==1) cout << '-';
    // ���� ������� �������� = 0, �� ������� ������ �� ������� ������� �������
	int k=count;
	while (arr[k]==0)
		{k--;
		}
	// ����� ������� ������� 
	for (int i=k; i>=0; i--) {
	 cout <<  arr[i];
	 // ���� ���������� ���� � arr[i] ������ � (��������  t=3, arr[i]=45, ����� ������� 045)
	 cout.fill('0'); // ������ ����������
	 cout.width(tT); // ���������� ��� ���������� 0
	}
}
void addArr(arrDigital  &a, arrCount &counta, arrDigital  &b, arrCount &countb, T &tT)
{
	// ������������ �������� ������������ �� �
	int tD=1;  	
	for(int i = 0; i < tT; i++) tD*=10;
	cout<<tD<< endl;
	int r = 0;
	
/*r - ���������� ������� � ��� "� ���"
 ��� �������� ������� ���� � ��� � ��� 0*/
	for(int i = 0; i <= counta; i++) {
		a[i] += b[i] + r;
		//����� ��������� ���� � ��������
		if (a[i] >= tD) {
		//������, ����� ���������� ������� � ��������� ������
			r = 1;
			a[i] -= tD;
		} else {
		//������, ����� �������� �� ����������
			r = 0;
		}
	}
	//���� ����� �������� ������� ��� �������, �� ����� �������� ��� ���� �����
	if (r > 0) {
		counta++;
		a[counta] = r;
	}
}

void subtract(arrDigital  &a, arrCount &counta, arrDigital  &b, arrCount &countb, T &tT)
{
	// ������������ �������� ������������ �� �
	int tD=1;  	
	for(int i = 0; i < tT; i++) tD*=10;
	cout<<tD<< endl;
	
//������� �������� �� ����� a ����� b
//r - ���������� ��� �� ���� ������� �� �������� �������
	int r = 0;
//���� �� �������� ������� �����������
	for(int i = 0; i <= counta; i++) {
		if (a[i] < b[i]) 
		{//�������� ��������� ���� � ������ �����
		
			a[i] = (tD+a[i] )-b[i] - r;
			r = 1;
		
		} else {
		//������, ����� ���� �� ����������
			a[i] -= b[i] + r;
			r = 0;
		}
	}
}


