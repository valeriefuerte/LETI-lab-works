#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std ;
int main ( )
{	setlocale (0,""); // ����������� �������� �����
	short i; // �������� ����������
	float x0 , x1,x2; 
	ifstream infile ("in_data.txt"); //������ ������� �� �����
    ofstream outfile ("out_data.txt"); //������ ������������ �  ����

	if (!infile) cout << "������� ���� �� ������!" << endl;
	else {
		
		//�������� ������� ��������
    	if(!(infile >> x0) ) cout << "���� ����!" << endl;
  		else{
		  
  			 //�������� ������� ��������
			if(!(infile >> x1)) {i=1; cout << "����� ��������� max ������������������ = " << i << endl;
    								  cout << "��������� max ������������������ = " << x0 << endl;
									  outfile << "����� max ������������������  = " << i << endl; 
									  cout << "����� max ������������������  = " << i << endl; 	
   								 } 
    		else 
			{
				if ( x0 > x1) i=1;		
				else i=0;
			
				//�������� �������� ��������
				if(!(infile >> x2)) 
				{
					if (i==1) cout << "��������� max ������������������ = " << x0 << endl;	
   					else    cout << "��������� max ������������������ = " << x1 << endl;					
				    cout << "����� ��������� max ������������������ = " << 1 << endl;
				}
				else 
				{
				
				// ����������� ������ ��������� ���������� 
				do {	
				if (( x0 <x1 )&&(x1>x2)) i++;
				cout <<  x0 << "<" <<  x1 << ">" << x2 << "  max: " << i << endl;
				outfile << setw(5)<< x0 << "<" << setw(5)<< x1 << ">" << setw(5)<< x2 << "  max: " << i << endl;
				x0=x1;
				x1=x2;
				}
				while (infile >> x2);
				
				// �������� �������� �� ��������� ������� ��������� ���������� 
				if ( x1 > x0) i++; 
				outfile << "����� max ������������������  = " << i << endl; 
				cout << "����� max ������������������  = " << i << endl; 
				}
			}
			
		}
	infile.close();
	outfile.close();
	return 0;
	}
}
