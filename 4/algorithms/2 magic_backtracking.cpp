#include <iostream>
#include <fstream>
using namespace std;
void Initialization(int size, int ***table);
void InitializationDigit(int size2, int* &dataDigit);
void Destruction(int size, int **table,int* &dataDigit);

int sumRow(int** &table, int size,int i);
int sumCol(int** &table, int size,int j);
bool checkRows(int** table, int size);
bool checkCols(int** table, int size);
bool checkDiag(int** table, int size);
int magicSum(int size);
bool isFull(int** table,int size);

void print(int** table, int size); //������ �� �����
void printfile(int** table, int size); //������ �������
void printfileAll(int** table, int size);
void solutionArray (int** table, int** tableSolution, int size);

void Magic(int** table,int** tableSolution,int* &dataDigit,int size,unsigned int l,unsigned int r);
bool turn90(int** table, int size);
bool turn180(int** table, int size);
bool turn270(int** table, int size);
bool reflectionVer(int** table, int size);
bool reflectionGor(int** table, int size);
bool reflectionMainDiagonal(int** table, int** tableSolution, int size);
bool reflectionSecondaryDiagonal(int** table, int** tableSolution, int size);

ofstream f("out.txt");
ofstream fout("outAll.txt");

int static count=0; //���������� ���������� ���������
int static countEquivalent=0;//���������� ������������� ���������� ���������

int main(){
  int n, n2,i, j;
 
  int **mas;
  int *dDigit;
 // bool *bDigit;
  int **solution;
  int *dN;
 
  setlocale(0,"");
  cout<<"������� ������ ����������� �������� n : ";
  cin>>n;
  Initialization(n,&mas);
  n2=n*n;
  InitializationDigit(n2, dDigit ); // ������������������ �����
  Initialization(n,&solution);      // ���������� �������
  Magic(mas,solution,dDigit,n, 0,n2-1);
  cout<<endl<<"���������� ����� �����: "<<magicSum(n)<<endl;
  cout<<"���������� ���������� ���������: "<<count<<endl; 
  f<<"���������� ���������� ���������: "<<count<<endl; 
  cout<<"���������� ������������� ���������� ���������: "<<countEquivalent<<endl;
  f<<"���������� ������������� ���������� ���������: "<<countEquivalent<<endl;
  Destruction(n,mas, dDigit);
  system("pause");
  return 0;
}

//������������� �������
void Initialization(int size, int ***table){ 
  *table = new int*[size]; 
  for (int i = 0 ; i < size; i++ ){
    (*table)[i] = new int[size];
    for (int j = 0 ; j < size ; j++ )
      (*table)[i][j] = 0;
  }
} 
void InitializationDigit(int size2, int* &dataDigit){
	 dataDigit = new int [size2]; 
 for (int i = 0 ; i < size2; i++ ){
      dataDigit[i]= i+1;
      }
}

// ������������ ������
void Destruction(int size, int **table,int* &dataDigit){ 
   for (int i = 0 ; i < size; i++ )
    delete [] table[i];
  delete [] table;
  delete [] dataDigit;
} 

//��������
int sumRow(int** &table, int size, int i) {
    // ������������ ����� � ������
    int sum,j;
    sum=0;
    for(j=0;j<size;j++)
        sum+=table[i][j];
    return sum;
}
int sumCol(int** &table, int size,int j) {
    // ��������� ����� � �������
    int sum,i;
    sum=0;
    for(i=0;i<size;i++)
        sum+=table[i][j];
    return sum;
}

bool checkRows(int** table, int size) {
    // ��������� �� �������
    int i;
    int sum1,sum2;
    sum1 = sumRow(table, size, 0);
    for(i=1;i<size;i++) {
        sum2 = sumRow(table,size,i);
        if(sum1 != sum2) return false;
    }
    return true;
}
bool checkCols(int** table, int size) {
    // ��������� �� ��������
    int i;
    int sum1,sum2;
    sum1 = sumCol(table, size, 0);
    for(i=1;i<size;i++) {
        sum2 = sumCol(table,size,i);
        if(sum1 != sum2) return false;
    }
    return true;
} 
bool checkDiag(int** table, int size) {
    // ��������� ���������
    int i,j;
    int sum1,sum2;
    sum1=0;
    sum2=0;
    for(i=0;i<size;i++){
        j=size-i-1;
        sum1+=table[i][i];
        sum2+=table[j][i];
    }
    return (sum1 == sum2);
}
int magicSum(int size) {
	//���������� �����
    return size*(size*size+1)/2;
    }
    
bool turn90(int** table, int** tableSolution, int size)
{  
	int **newtable= new int* [size]; 
  	for (int i = 0 ; i < size; i++ ){
    newtable[i] = new int [size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
		{
            newtable[j][size-i-1] =tableSolution[i][j];
        }
    }
//	��������� � �������� 
 	for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           if(newtable[i][j]!=table[i][j]) return false;
        }
    }
    return true;
}
bool turn180(int** table, int** tableSolution, int size)
{
	int **newtable= new int* [size]; 
  	for (int i = 0 ; i < size; i++ ){
    newtable[i] = new int [size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
		{
            newtable[size-i-1][size-j-1] =tableSolution[i][j];
        }
    }
	for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           if(newtable[i][j]!=table[i][j]) return false;
        }
    }
    return true;
}
bool turn270(int** table, int** tableSolution, int size)
{
	int **newtable= new int* [size]; 
  	for (int i = 0 ; i < size; i++ ){
    newtable[i] = new int [size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
		{
            newtable[size-j-1][i] =tableSolution[i][j];
        }
    }
	for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           if(newtable[i][j]!=table[i][j]) return false;
        }
    }
    return true;
}

bool reflectionGor(int** table, int** tableSolution, int size)
{
	int **newtable= new int* [size]; 
  	for (int i = 0 ; i < size; i++ ){
    newtable[i] = new int [size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
		{
            newtable[size-i-1][j] =tableSolution[i][j];
        }
    }
	for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           if(newtable[i][j]!=table[i][j]) return false;
        }
    }
    return true;
}
bool reflectionVer(int** table, int** tableSolution, int size)
{
	int **newtable= new int* [size]; 
  	for (int i = 0 ; i < size; i++ ){
    newtable[i] = new int [size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
		{
            newtable[i] [size-j-1]=tableSolution[i][j];
        }
    }
	for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           if(newtable[i][j]!=table[i][j]) return false;
        }
    }
    return true;
}
bool reflectionMainDiagonal(int** table, int** tableSolution, int size)
{
	int **newtable= new int* [size]; 
  	for (int i = 0 ; i < size; i++ ){
    newtable[i] = new int [size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
		{
            newtable[i][j] =tableSolution[j][i];
        }
    }
	       
	for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           if(newtable[i][j]!=table[i][j]) return false;
        }
    }
    return true;
}
bool reflectionSecondaryDiagonal(int** table, int** tableSolution,int size)
{
	int **newtable= new int* [size]; 
  	for (int i = 0 ; i < size; i++ ){
    newtable[i] = new int [size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
		{
            newtable[i][j] =tableSolution[size-j-1][size-i-1];
        }
    }
	    
	for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
           if(newtable[i][j]!=table[i][j]) return false;
        }
    }
    return true;
}
bool isFull(int** table,int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(table[i][j] == 0) return false;
        }
    }
    return true;
}
void print(int** table, int size) {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << table[i][j] << "  ";
        }
        cout << endl;
    }
}
void printfile(int** table, int size) // �� ������������� �������
{
     for (int i = 0 ; i < size; i++ ){
        for (int j = 0 ; j < size ; j++ )
          f<<table[i][j]<<" ";
        f<<endl;
      }
}
    
void printfileAll(int** table, int size)
{
     fout<<"�������: \n";
      for (int i = 0 ; i < size; i++ ){
        for (int j = 0 ; j < size ; j++ )
          fout<<table[i][j]<<" ";
        fout<<endl;
      }
}
void solutionArray (int** table, int** tableSolution, int size) 
{
for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
		{
            tableSolution[i][j] = table[i][j];
        }
    }
}
void Magic(int** table,int** tableSolution,int* &dataDigit,int size,unsigned int l,unsigned int r)
{// count  ���������� ���������� ���������
//	countEquivalent  ���������� ������������� ���������� ���������
	unsigned int j;//�������������� ���������� ��� ������
	if (l==r){ 
			for(unsigned int i=0; i<size*size ; i++ )
			{ cout<<dataDigit[i]<<" ";
    		}
			cout<<endl;
		for(int i = 0; i < size; i++)
	        for(int j = 0; j < size; j++)
            table[i][j] =0;
		
		int row=0,col=0;
		for(unsigned int i =0;  i < size*size; i++){
				table[row][col]=dataDigit[i]; 
    			col++; 
				if(col == size) 
					if (sumRow(table, size, row)==magicSum(size) )
								{ row++; col=0;
								}
					else 
					{exit;
					}
   		 }
   		 
//   		�������
	  if(checkCols(table, size) && checkRows(table,size) && checkDiag(table, size)) 
	 {		cout<<"Solution find "<<endl;
	        print(table, size);
	
	        if(! isFull(tableSolution, size) ){ //�������� �� ������ �������
      			solutionArray (table, tableSolution, size);
		 		printfile(table, size);
				count++;
				}
			else
			{
			if(turn90(table, tableSolution,size)) {
					cout<<"������� ������������� �������: ������� �� 90 �������� \n";
					fout<<"������� ������������� �������: ������� �� 90 �������� \n";
					};
				
			if(turn180(table, tableSolution,size)) {
					cout<<"������� ������������� �������: ������� �� 180 �������� \n";
					fout<<"������� ������������� �������: ������� �� 180 �������� \n";
					};
				
            if(turn270(table, tableSolution,size)) {
					cout<<"������� ������������� �������: ������� �� 270 �������� \n";
					fout<<"������� ������������� �������: ������� �� 270 �������� \n";
					};
				
        	if(reflectionVer(table, tableSolution,size)) {
					cout<<"������� ������������� �������: ������������ �����������  \n";
					fout<<"������� ������������� �������: ������������ �����������  \n";
					};
				
			if(reflectionGor(table, tableSolution,size)) {
					cout<<"������� ������������� �������: �������������� ����������� \n";
					fout<<"������� ������������� �������: �������������� �����������  \n";
					};
					
        	if(reflectionMainDiagonal(table, tableSolution,size)) {
					cout<<"������� ������������� �������: ����������� ������������ ������� ��������� \n";
					fout<<"������� ������������� �������: ����������� ������������ ������� ��������� \n";
					};
					
				if(reflectionSecondaryDiagonal(table, tableSolution,size)) {
					cout<<"������� ������������� �������: ����������� ������������ �������� ��������� \n";
					fout<<"������� ������������� �������: ����������� ������������ �������� ��������� \n";
					};
				
			}
			printfileAll(table,  size);
			countEquivalent++;
			system("pause");
	 }
	}
	else
	{for(unsigned int i=l; i<= r; i++ ){
			j=dataDigit[l]; dataDigit[l]=dataDigit[i];dataDigit[i]=j; //����� a[l],a[i]
			Magic(table,tableSolution,dataDigit,size,l+1,r);					// ����� ����� ���������
			j=dataDigit[l]; dataDigit[l]=dataDigit[i];dataDigit[i]=j; //����� a[l],a[i]
			}
	}
}
