//���������� ��� ������������ �������� n ��������� ����������� ����� (��� ��������).
#include <iostream>
#include <fstream>
using namespace std;

unsigned int strCount=0;
const unsigned short Max = 256; 		  //������������ ���������� ��������� �������
unsigned int str[Max];
void permutation(unsigned int l,unsigned int r);

int main()
{
    setlocale(LC_ALL,"Russian");
    cout <<"������� n ��� ������������ �����  ";
    cin>>strCount;
    if(strCount==0) cout <<"������������ ������!";
	else
	{
		for(unsigned int i=1; i<= strCount; i++ ) str[i]=i; //����������  �������
		permutation(1,strCount);
	}
    return 0;
}

void permutation(unsigned int l,unsigned int r)
{
	//ofstream fout("output.txt");
	//////////////////////////////////////////////////////////////////////////////////
	for(int k=0;k<l*2;k++)printf(" ");
	
	
	cout<<"����� "<<l<<" "<<r<<endl;
	//fout<<"����� "<<l<<" "<<r<<endl;
	unsigned int j;//�������������� ���������� ��� ������
	if (l==r){ 
	/////////////////////////////////////////////////////////////////////////////////
			for(int k=0;k<l*3;k++)printf(" ");
		
		for(unsigned int i=1; i<= strCount; i++ )
			{ cout<<str[i]<<" ";
			//fout <<str[i]<<" ";
    		}
		cout<<endl;
		}
	else
	{for(unsigned int i=l; i<= r; i++ ){
			j=str[l]; str[l]=str[i];str[i]=j; //����� a[l],a[i]
			permutation(l+1,r);				  // ����� ����� ���������
			j=str[l]; str[l]=str[i];str[i]=j; //����� a[l],a[i]
			}
	}
	//fout.close(); // ��������� ����
}

