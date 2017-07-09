//������ �������� ������ b ���� �� � ������������ ����� ���������. 
//��������� ������� � �������� ��� ��� (��. 2), ���������� ��� �������� ������ b �� �������: 
//�������   �� ����� ������, ����� (����� �������)   �� �����, �������� �� ��������� � �����, 
//����� (����� ����� �������)   �� �����, �������� �� ��������� � ���� �����, � �. �.
#include<iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
ifstream in("1in.txt");
ofstream fout("out.txt");
typedef int ID;
vector<int> used (20);
vector<char> d (20);

struct TreeNode // ������ 
{
   char value;
	TreeNode *left;
    TreeNode *right;
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
    	void headBT();//����������� ������� ������
    	
	   	char RootBT(binTree b); // ��� ��������� ���.������
    	TreeNode* headRootBT( )	;
    	binTree Left(binTree b);
    	binTree Right(binTree b);
    	
		void displayBT(binTree, ID );
    	void printTree();
    	
		void displayQueue(binTree , ID ); // ������������ �������
    	void displayQueueTree();
    	int getMaxDepth(binTree b, ID n); // ������� ������
    	int getCount(binTree b, ID n); //����� ���������� �� ������� ������
    	
		TreeNode* ConsBT(const char &x, binTree &lst, binTree &rst);
    	TreeNode* enterBT();
		
		void destroyEL(binTree b);
		void destroyTree();
};

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
        else { return b->value;	} //���������� ������ � ������� �������
}

TreeNode* BinaryTree::headRootBT( )			// ��� ��������� ���.������
{
        if (head == NULL) { cerr << "Error: headRootBT(null) \n"; exit(1); }
        else {
		return head;	} //���������� ������ �� ������
}
//�������� �� ������
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
//������������ ���� ����� � ������ �����
TreeNode* BinaryTree::ConsBT(const char &x, binTree &lst, binTree &rst)
{//������� ������ ����������� ����� ������ ����
    binTree p;
    p = new TreeNode;
    if (p != NULL)	{
        p->value = x;
    	p->left = lst;
        p->right = rst;
        link=p;
		return link;//������� ������
    }
    else { cerr << "Memory not enough\n"; exit(1); }
}

TreeNode* BinaryTree::enterBT() //���� ������ �� �����
{
  	char ch;
    TreeNode* p;
	TreeNode* q;
    
 	if (!in.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
	else
	{ while(!in.eof())
		{
		in >> ch;         
		cout<<ch;//���������� � �����, ���� �� "/"
   		if (ch == '/'){ return NULL; }
   		else { p = enterBT();   //������������ ���� 
		    q = enterBT();      //������ ������ ����� - q, p- ������ �����
			link=ConsBT(ch, p, q);  
   			return link; }
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

void BinaryTree::displayQueue(binTree b, ID n) // ������������ ������� 
{	static int i=0; //��� ����������� ������� ������������
    if (b != NULL) {
        d[i]=RootBT(b);
        used[i]=n;
        i++;
        if (Right(b)!= NULL)  displayQueue(Right(b), n + 1); 
        if (Left(b)!= NULL)   displayQueue(Left(b), n + 1);
             
    }
}

int BinaryTree::getCount(binTree b, ID n) //����� ���������� ��������� ������
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

void BinaryTree::displayQueueTree()
{ 
	binTree b=headRootBT();
	int vecSize= getCount(b, 0); //����� ���������� �� ������� ������(���-�� �������� � ������ �����)
  	ID n=0;
  	displayQueue( headRootBT(), 0); // ������������ �������
  	cout << "������  "<<endl<<"����� ���������� ��������� ������ "<<vecSize<<endl;
    for (int i = 0; i < vecSize; i++) 
	  { cout << "  "<<used[i]; //������ � ������
	  }
	 cout<<endl;
	 queue<char> q;
	 int Depth=getMaxDepth(headRootBT(), 0);
	 for (int i = 0; i < Depth; i++) //�� �������
	 { cout<<"������� "<<i<<endl;
	 	fout<<"�������"<<i<<endl;
	 	for (int j = 0; j < vecSize; j++) // �� ��������� �������
	 		 if (used[j]==i) {q.push(d[j]); //  ��������� �������� � �������
			 				cout<<d[j]<<" ";
			 				fout<<d[j]<<endl;
							 }
		cout<<endl;
	}
	cout <<endl<< "�������  "<< endl; 
	while (!q.empty())
	{cout<< q.front()<<" "; //����� ������� ��������
	  q.pop();				//� ��� ����������
			 }		 
	 cout << endl; 
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
     cout << endl<<"�������� ������: " << endl;
     Bin.printTree();
     Bin.displayQueueTree();
    
     cout<<"��������"<<endl;
	 Bin.destroyTree();
       
    }
   
	return 0;
}
