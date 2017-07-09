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
#include<iostream>
#include <fstream>
#include <string.h>

using namespace std;

ifstream in("in.txt");
typedef int ID;
ofstream fin("out.txt");
struct TreeNode // ������ 
{
    char value; //������� �������
	TreeNode *left; //������ �� �����
    TreeNode *right; //������ �� ������
    TreeNode() { left = NULL; right = NULL; } // constructor 
};
typedef TreeNode *binTree; // "�������������" ��������� ������
class BinaryTree
{
    private: 
	   TreeNode *head;
	   TreeNode *link;
    public:
		TreeNode* Create();
    	bool isNull();
    	void headBT(); //����������� ������� ������
    	

    	char RootBT(binTree b); // ��� ��������� ���.������
    	TreeNode* headRootBT( )	;
    	binTree Left(binTree b);
    	binTree Right(binTree b);
    	
		void displayBT(binTree, ID );
    	void printTree();
    	void obhodBT(binTree b);   // ����� � ����� �� �����������
 //   	bool findEL(char x , binTree b); //����� � ������ ��������
    	
	
    	int getMaxDepth(binTree b, ID n); // ������� ������
    	int getCount(binTree b, ID n); //����� ���������� �� ������� ������
    	
    	TreeNode* enterBT();
    	TreeNode* newElBT( char x);
    	TreeNode* enterElBT(char x , binTree b);
    	
		
		void destroyEL(binTree b);
		void destroyTree();

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

char BinaryTree::RootBT(binTree b )			// ��� ��������� ���.������
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


TreeNode* BinaryTree::newElBT( char x) //���� �����
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
TreeNode* BinaryTree::enterElBT(char x , binTree b) //���� �������
{ 
  		if (b!=NULL) { cout<<"������� "<<b->value<<" -> ";
			if (x <= b->value)   { b->left=enterElBT(x,b->left);  }   
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
  	char ch;
//  TreeNode* p;
//	TreeNode* q;
    
 	if (!in.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
	else
	{
		while(in >> ch )
		{
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
        cout << ' ' << RootBT(b);
        if (Right(b)!= NULL) { displayBT(Right(b), n + 1); }
        else cout << endl; // ����
        if (Left(b)!= NULL) {
            for (int i = 1; i <= n; i++) cout << "  "; // ������
            displayBT(Left(b), n + 1);
        }
    }
    else {};
}
void BinaryTree::printTree()
{ binTree b=headRootBT();
  ID n=1;
  displayBT( b, n);
}
void BinaryTree::obhodBT(binTree b)
{	if (b != NULL) {
        if (Left(b)!= NULL) {  obhodBT(Left(b));  }
		cout << ' ' << RootBT(b);
		fin << ' ' << RootBT(b);
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

int BinaryTree::getCount(binTree b, ID n) //����� ���������� �� ������� ������
{   static int i=0;
    if (b != NULL){i++;getCount(b->left, n + 1);getCount(b->right, n + 1);
	}
     return i;        
}
int BinaryTree::getMaxDepth(binTree b, ID n) // ������� ������
{
    if (b == NULL){ return n; }
    else return max(getMaxDepth(b->left, n + 1), getMaxDepth(b->right, n + 1));        
}

/*bool BinaryTree::findEL(int x , binTree b) //���� �������
{ 
  		if (b==NULL) { return false;}
  		else
  			{if (x==b->value) return true;
  			else
			{if (x < b->value)   { findEL(x,b->left);  }   
							else { findEL(x,b->right); }   
  			}}
}
*/	
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
     cout << endl<<"�������� ������: " << endl;
     Bin.printTree();
     
//     cout<< endl<<"������� ������� "<< endl;
//	 int addValue;
//     cin>>addValue;
//     if (!Bin.findEL(addValue,Bin.headRootBT())) 
//	 	{   cout<< endl<<"������� �������� "<<addValue<< endl;
//	 		Bin.enterElBT(addValue,Bin.headRootBT());
//	 	} 
//	 else cout<< endl<<"������� "<<addValue<<"  � ������ ����������"<< endl;    
     cout << endl<<"�������� ��� � ������� �� �����������: " << endl;
     Bin.obhodBT(Bin.headRootBT());
     
     cout<< endl<<"��������";
	 Bin.destroyTree();
       
    }
   
	return 0;
}
