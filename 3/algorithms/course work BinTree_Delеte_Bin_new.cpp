//� ��������� ������� 2-�� ������ (���) ���������:
//1)	�� ��������� ����� F (���� file of Elem), ��� �������� �������� ��������, ��������� ��� ������������ ����;
//2)	��������� ���� �� ��������� ��������:
//�) ��� ������������ ��� ���������, ������ �� � ���� ������� � ���� Elem, � ���� �� ������, �� �������� ������� � � ������ ������.
//�) ��� ������������ ��� ���������, ������ �� � ���� ������� � ���� Elem, � ���� ������, �� ������� ������� � �� ������ ������.
//�) �������� � ���� �������� ������������ ��� � ������� �� �����������; ������� ����������� ��� �� �����.
//- "������� ��������" - �������� ��������� ��� ��������� ������� � �������� � ��� ��� ���������� �������� �������� 
//����� ���������. ������� � ������ ������ ���������� � ���� � ������� �����: ������ ������� ������ ���� ������ 
//��� �������� ���������, ���������� ��; ������ ������ ��������� ������� �������� ������������ ���������� �������.

//9	���: ���������* ���; ��������: 1+2�	��������� ��� - ������� � ����������. ������� ��������

// http://purecodecpp.com/archives/1012
//rand() � ��������� ��������� ����� � C++
#include <iostream>
#include <fstream>
#include <string.h>

#include <cstdlib>
#include <ctime> //  time()

using namespace std;

ifstream in("in.txt");
ofstream task("task.txt");
ofstream keys("keys.txt");
typedef int ID;
int data[255];
int count;

struct TreeNode // ������ 
{
    int value;
	TreeNode *left;
    TreeNode *right;
    TreeNode() { left = NULL; right = NULL; } // constructor 
};
typedef TreeNode *binTree; // "�������������" ��������� ������
binTree q;
class BinaryTree
{
    private: 
	   TreeNode *head;
	   TreeNode *link;
    public:
		TreeNode* Create();
    	bool isNull();
    	void headBT(); //����������� ������� ������
    	

    	int RootBT(binTree b); // ��� ��������� ���.������
    	TreeNode* headRootBT( )	;
    	binTree Left(binTree b);
    	binTree Right(binTree b);
    	
    	void displayData(); 
		void displayBT(binTree, ID );
    	void printTree();
    	
		void printT(binTree b, unsigned k); //������ ������ ����� �������
    	
	
		
		void obhodBT(binTree b);   // ����� � ����� �� �����������
    	bool findEL(int x , binTree b); //����� � ������ ��������
    	    	
    	TreeNode* enterBT();
    	TreeNode* newElBT( int x);
    	TreeNode* enterElBT(int x , binTree b);
    	
		void destroyEL(binTree b);
		void destroyTree();
		
		bool sheetCheck(int x, binTree b);
		TreeNode* delTree(int x, binTree b);
		TreeNode* delEl(binTree b);
};
//�������
TreeNode* BinaryTree::Create()   //�������� ������
{
	link=head=NULL;
    return head;
}
bool BinaryTree::isNull()
{
	return (link == NULL);
}
void BinaryTree::headBT( )			//����������� ������� ������
{ 
         head=link;	
}
int BinaryTree::RootBT(binTree b )			// ��� ��������� ���.������
{
        if (b == NULL) { cerr << "Error: RootBT(null) \n"; exit(1); }
        else { return b->value;	}
}
TreeNode* BinaryTree::headRootBT( )			// ��� ��������� ���.������
{
        if (head == NULL) { cerr << "Error: headRootBT(null) \n"; exit(1); }
        else {
		return head;	}
}
binTree BinaryTree::Left(binTree b)		// ��� ��������� ���.������
    {
        if (b == NULL) { cerr << "Error: Left(null) \n"; exit(1); }
        else return b->left;
    }
binTree BinaryTree::Right(binTree b)		// ��� ��������� ���.������
    {
        if (b == NULL) { cerr << "Error: Right(null) \n"; exit(1); }
        else return b->right;
    }
TreeNode* BinaryTree::newElBT( int x) //���� �����
{
    binTree p = new TreeNode;
    if (p != NULL)	{
        p->value = x;
    	p->left = NULL;
        p->right = NULL;
        return p;
    }
    else { cerr << "Memory not enough\n"; exit(1); }
}
TreeNode* BinaryTree::enterElBT(int x , binTree b) //���� �������
{ 
  		if (b!=NULL) { cout<<"������� "<<b->value<<" -> ";
			if (x <= b->value)   { b->left=enterElBT(x,b->left);   }   
							else { b->right=enterElBT(x,b->right); }   
		}
		else { 
		b = newElBT(x);
		cout<<" �������� ������� "<<b->value << endl;
		} 
		return b;
}
TreeNode* BinaryTree::enterBT() //���� ������ �� �����
{
  	int ch;
  	count=0;
 	if (!in.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
	else
	{ while(in >> ch)
		{
		data[count]=ch;
		count++;
		//cout<<ch<<" ";
		if (!isNull()){ link=headRootBT();	  
						link = enterElBT(ch,headRootBT());	}
		else {
				link = newElBT(ch); 
				headBT();	}
		}
	in.close(); //�������� �����
	}
}
void BinaryTree::displayBT(binTree b, ID n)
{	// n - ������� ����
	if (b != NULL) {
        cout << " " << RootBT(b);
        keys << " " << RootBT(b);
        if (Right(b)!= NULL) { displayBT(Right(b), n + 1); }
        else {cout << endl; keys<<endl;}// ����
        if (Left(b)!= NULL) {
            for (int i = 1; i <= n; i++){ cout << "  "; keys<<"  ";}// ������
            displayBT(Left(b), n + 1);
        }
    }
    else {};
}
void BinaryTree::printT(binTree b, unsigned k )
{
    if (b != NULL)
    {   printT(b->right, k + 5);
        for (int i = 0; i < k; i++) {
			cout << " "; keys<<" ";
        	}
  	    cout << RootBT(b)<<  endl;;
        keys << RootBT(b)<<  endl;
		  //cout << b->value <<  endl;
        printT(b->left, k + 5);
    }
}

void BinaryTree::displayData()
{	
    if (count!= 0) {
    	cout <<endl<< "�������� ������ " << endl;
    	task << "�� �������� ������: " ;
        for (int i = 0; i < count; i++) 
        {
		 cout<<data[i]<<" ";
		 task<<data[i]<<" ";
        }
        cout<<endl;
        task<<" ��������� �������� ������ ������."<<endl;
    }
    else{};
}


void BinaryTree::printTree()
{ binTree b=headRootBT();
  ID n=1;
  keys<<endl<<"���������� ��������� ������ ������: "<<endl;
  //displayBT( b, n);
  printT(b,n);
}
void BinaryTree::obhodBT(binTree b)
{	if (b != NULL) {
        if (Left(b)!= NULL) {  obhodBT(Left(b));  }
		cout << " " << RootBT(b);
		keys<<" "<< RootBT(b);
        if (Right(b)!= NULL) { obhodBT(Right(b)); }
     }
}
void BinaryTree::destroyEL(binTree b)
{    
        if (b != NULL)	{
            destroyEL(b->left);
            destroyEL(b->right);
            delete b;
            b = NULL;
        }
}
void BinaryTree::destroyTree()
{ 
   destroyEL(headRootBT());
}

bool BinaryTree::sheetCheck(int x, binTree b)   // �������� �� ����
 { if (b!=NULL)
 	{
	if (x!=b->value) 
	 	if (x < b->value)   { sheetCheck(x,b->left);  }   
					else    { sheetCheck(x,b->right); }  
	else
		{ 	  	
		 if ((Right(b)== NULL) && (Left(b)== NULL)) //��� �����������
			 return false;
			else  return true; // ���� ���������	
		}
	}
}
TreeNode* BinaryTree::delTree(int x, binTree b)
 { 
  	if (b!=NULL){
  			if (x!=b->value) 
			 	if (x < b->value)   { b->left=delTree(x,b->left);  }   
							else    { b->right=delTree(x,b->right); }  
 			else
    		{	cout<<"������ ������� ��� �������� "<<b->value; 
				//task<<"������� ������� "<<b->value;	  
		    	q=b; 
		    	  	
//			 	if ((Right(q)== NULL) && (Left(q)== NULL)) //��� �����������
//				 { cout<<" � ���� ��� �����������"<<endl;
//				 b=NULL;
//				  }
//			   	  else 	
						// ���� ���������		   
		 			if (Right(q)== NULL) {
		 			cout<<" � ���� ��� ������� ���������"<<endl;
			   	   	b=q->left;
			   	   	}
					else 
					if (Left(q)== NULL) {
					cout<<" � ���� ��� ������ ���������"<<endl;
					b=q->right;
					}
				    
					else  // ��� ���������
					{ 
					cout<<" � ���� ��� ��������� ";
					binTree y=q->right;
					if(Left(y) == NULL)  // ��� � ������ ����� ������ �����
					{
					cout<<" �� � ������ ����� ��� ������ �����"<<endl;
					y->left = q->left;
					b=y;
					}
						else
						{
						binTree z=y->left;  // ���� � ������ ����� ����� ����
						while(Left(z) != NULL)
						{
							y = z;
							z = y->left;
						}
						cout<<" ������� � ������ ����� ����� ����� ����"<<endl;
						//cout<<"b="<<b->value<<" q="<<q->value<<" y="<<y->value<<" z="<<z->value<<endl;
						y->left = z->right;
						z->left = q->left;
						z->right =q->right;
						b=z;
						
						}
					}
			}
	} 
	if (q==head) head=b;   //���� ������� �������, �� ����� �������� ������ �� ������ ������
	delete q;
	return b;
 } 

bool BinaryTree::findEL(int x , binTree b) 
{ 
  		if (b==NULL) { return false;}
  		else
  			if (x==b->value) return true;
  			else
			if (x < b->value)    { findEL(x,b->left);  }   
							else { findEL(x,b->right); }   
}
	
int main()
{
	setlocale(LC_ALL, "rus"); // ���������� ����������� ���������

	BinaryTree Bin;
	Bin.Create();
    Bin.enterBT();
    Bin.headBT();
    ID depth = 1;
    if (Bin.isNull( )) cout << "������ ��" << endl;
    else
    {
     Bin.displayData();
	 cout << endl<<"�������� ������: " << endl;
     Bin.printTree();
    //Bin.printT(Bin.headRootBT(),0);                                 // ������ �����
	/*  task<<"�������� �������� ������ �� �����������."<<endl;
     keys<< endl<<"�������� ������ �� �����������: "<<endl;
	 Bin.obhodBT(Bin.headRootBT());
	 */	      
    srand(time(NULL));
    int addValue;
    cout<<"�������������� �������� ��� ������� ";
    while(true)
	{
	addValue=rand() % 41 - 20; // ��������� ����� o� �20 �o 20
     cout<<addValue<<" ";
	if (!Bin.findEL(addValue,Bin.headRootBT())) 
	 	{   cout<< endl<<"������� �������� "<<addValue<< endl;
	 		task <<endl<<"�������� �������: "<<addValue<< endl;
	 		keys<<endl<<endl<<"���������� �������� "<<addValue<< endl;
	 		Bin.enterElBT(addValue,Bin.headRootBT());
	 		Bin.printTree();
	 		break;
	 		} 
	/* else {
	 	   task <<endl<<"�������� �������: "<<addValue<< endl;
	 	   keys<<endl<<endl<<"���������� �������� "<<addValue<< endl;
		   cout<< endl<<"������� "<<addValue<<"  � ������ ����������"<< endl;
		   keys<< endl<<"������� "<<addValue<<"  � ������ ����������"<< endl;}
     */
	}
    // cout<< endl<<"��������"<<endl;
     int delValue;
     cout<<"�������������� �������� ��� �������� ";
	 while(true)
	{ delValue=rand() % 41 - 20; // ��������� ����� o� �20 �o 20
      cout<<delValue<< " ";  
	 if (Bin.findEL(delValue,Bin.headRootBT())) 	//  ���� �������
	 	{
	 	if (Bin.sheetCheck(delValue,Bin.headRootBT())) // ���� ����������
	 	{   cout<< endl<<"�������� �������� "<<delValue<<endl;
	 		task<< endl<<"������� �������: "<<delValue<<endl;
	 		keys<<endl<<endl<<"�������� �������� "<<delValue<<endl;
	 		Bin.delTree(delValue,Bin.headRootBT());
	 		Bin.printTree();
	  		break;
	 	} 
		}
	}
	/* else {
	 cout<< endl<<"�������� �������� "<<delValue<<endl;
	 cout<< endl<<"������� "<<delValue<<"  � ������ �� ����������"<< endl;
	 task<< endl<<"������� �������: "<<delValue<<endl;
	 keys<< endl<<"������� "<<delValue<<"  � ������ �� ����������"<< endl;
	 }*/
	// cout << endl<<"�������� ������: " << endl;
	 //keys<< endl<<"�������� ������: " << endl;
     //Bin.printTree();
     
	 /*cout << endl<<"����� ��������� ������: " << endl;
	 keys<< endl<<"�������� ������ �� �����������: "<<endl;
     Bin.obhodBT(Bin.headRootBT());*/
     
     
	 Bin.destroyTree();
    }
   	return 0;
}
