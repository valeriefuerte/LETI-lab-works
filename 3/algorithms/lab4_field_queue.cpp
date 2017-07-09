//Задано бинарное дерево b типа ВТ с произвольным типом элементов. 
//Используя очередь и операции над ней (см. 2), напечатать все элементы дерева b по уровням: 
//сначала   из корня дерева, затем (слева направо)   из узлов, сыновних по отношению к корню, 
//затем (также слева направо)   из узлов, сыновних по отношению к этим узлам, и т. д.
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

struct TreeNode // данные 
{
   char value;
	TreeNode *left;
    TreeNode *right;
    TreeNode() { left = NULL; right = NULL; } // constructor 
};
typedef TreeNode *binTree; // "представитель" бинарного дерева
class BinaryTree
{
    private: 
	   TreeNode *head;
	   TreeNode *link;

    public:
    	TreeNode* Create();
    	bool isNull();
    	void headBT();//определение вершины дерева
    	
	   	char RootBT(binTree b); // для непустого бин.дерева
    	TreeNode* headRootBT( )	;
    	binTree Left(binTree b);
    	binTree Right(binTree b);
    	
		void displayBT(binTree, ID );
    	void printTree();
    	
		void displayQueue(binTree , ID ); // формирование вектора
    	void displayQueueTree();
    	int getMaxDepth(binTree b, ID n); // глубина дерева
    	int getCount(binTree b, ID n); //общее количество не нулевых вершин
    	
		TreeNode* ConsBT(const char &x, binTree &lst, binTree &rst);
    	TreeNode* enterBT();
		
		void destroyEL(binTree b);
		void destroyTree();
};

TreeNode* BinaryTree::Create()   //создание дерева
{
	link=head=NULL;
    return head;
}

bool BinaryTree::isNull()
{
	return (link == NULL);
}

void BinaryTree::headBT( )			//определение вершины дерева
{ 
         head=link;	
}

char BinaryTree::RootBT(binTree b )			// для непустого бин.дерева
{
        if (b == NULL) { cerr << "Error: RootBT(null) \n"; exit(1); }
        else { return b->value;	} //возвращает символ в текущей вершине
}

TreeNode* BinaryTree::headRootBT( )			// для непустого бин.дерева
{
        if (head == NULL) { cerr << "Error: headRootBT(null) \n"; exit(1); }
        else {
		return head;	} //возвращаем голову на дерево
}
//переходы по дереву
binTree BinaryTree::Left(binTree b)		// для непустого бин.дерева
    {
        if (b == NULL) { cerr << "Error: Left(null) \n"; exit(1); }
        else return b->left;
    }
 
binTree BinaryTree::Right(binTree b)		// для непустого бин.дерева
    {
        if (b == NULL) { cerr << "Error: Right(null) \n"; exit(1); }
        else return b->right;
    }
//формирование узла левой и правой ветви
TreeNode* BinaryTree::ConsBT(const char &x, binTree &lst, binTree &rst)
{//текущей ссылке присваиваем адрес нового узла
    binTree p;
    p = new TreeNode;
    if (p != NULL)	{
        p->value = x;
    	p->left = lst;
        p->right = rst;
        link=p;
		return link;//текущая ссылка
    }
    else { cerr << "Memory not enough\n"; exit(1); }
}

TreeNode* BinaryTree::enterBT() //ввод дерева из файла
{
  	char ch;
    TreeNode* p;
	TreeNode* q;
    
 	if (!in.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{ while(!in.eof())
		{
		in >> ch;         
		cout<<ch;//считывание с конца, пока не "/"
   		if (ch == '/'){ return NULL; }
   		else { p = enterBT();   //формирование узла 
		    q = enterBT();      //нижняя правая ветвь - q, p- нижняя ветвь
			link=ConsBT(ch, p, q);  
   			return link; }
		}
	in.close(); //закрытие файла
	}
}

void BinaryTree::displayBT(binTree b, ID n)
{	// n - уровень узла
    if (b != NULL) {
        cout << ' ' << RootBT(b);
        if (Right(b)!= NULL) { displayBT(Right(b), n + 1); }
        else cout << endl; // вниз
        if (Left(b)!= NULL) {
            for (int i = 1; i <= n; i++) cout << "  "; // вправо
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

void BinaryTree::displayQueue(binTree b, ID n) // формирование вектора 
{	static int i=0; //при последующих вызовах наращивается
    if (b != NULL) {
        d[i]=RootBT(b);
        used[i]=n;
        i++;
        if (Right(b)!= NULL)  displayQueue(Right(b), n + 1); 
        if (Left(b)!= NULL)   displayQueue(Left(b), n + 1);
             
    }
}

int BinaryTree::getCount(binTree b, ID n) //общее количество ненулевых вершин
{   static int i=0;
    if (b != NULL){i++;getCount(b->left, n + 1);getCount(b->right, n + 1);
	}
     return i;        
}

int BinaryTree::getMaxDepth(binTree b, ID n) // глубина дерева
{
    if (b == NULL){ return n; }
    else return max(getMaxDepth(b->left, n + 1), getMaxDepth(b->right, n + 1));        
}

void BinaryTree::displayQueueTree()
{ 
	binTree b=headRootBT();
	int vecSize= getCount(b, 0); //общее количество не нулевых вершин(кол-во символов в строке ввода)
  	ID n=0;
  	displayQueue( headRootBT(), 0); // формирование вектора
  	cout << "Вектор  "<<endl<<"Общее количество ненулевых вершин "<<vecSize<<endl;
    for (int i = 0; i < vecSize; i++) 
	  { cout << "  "<<used[i]; //уровни у вершин
	  }
	 cout<<endl;
	 queue<char> q;
	 int Depth=getMaxDepth(headRootBT(), 0);
	 for (int i = 0; i < Depth; i++) //по глубине
	 { cout<<"Глубина "<<i<<endl;
	 	fout<<"Глубина"<<i<<endl;
	 	for (int j = 0; j < vecSize; j++) // по элементам вектора
	 		 if (used[j]==i) {q.push(d[j]); //  занесение элемента в очередь
			 				cout<<d[j]<<" ";
			 				fout<<d[j]<<endl;
							 }
		cout<<endl;
	}
	cout <<endl<< "Очередь  "<< endl; 
	while (!q.empty())
	{cout<< q.front()<<" "; //вывод первого элемента
	  q.pop();				//и его извлечение
			 }		 
	 cout << endl; 
}
	
int main()
{
	setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы

	BinaryTree Bin;
	Bin.Create();
    Bin.enterBT();
    Bin.headBT();
    ID depth = 1;
    if (Bin.isNull( )) cout << "Пустое БД" << endl;
    else
    {
     cout << endl<<"Бинарное дерево: " << endl;
     Bin.printTree();
     Bin.displayQueueTree();
    
     cout<<"Удаление"<<endl;
	 Bin.destroyTree();
       
    }
   
	return 0;
}
