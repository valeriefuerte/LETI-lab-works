//В вариантах заданий 2-ой группы (БДП) требуется:
//1)	По заданному файлу F (типа file of Elem), все элементы которого различны, построить БДП определённого типа;
//2)	Выполнить одно из следующих действий:
//а) Для построенного БДП проверить, входит ли в него элемент е типа Elem, и если не входит, то добавить элемент е в дерево поиска.
//б) Для построенного БДП проверить, входит ли в него элемент е типа Elem, и если входит, то удалить элемент е из дерева поиска.
//в) Записать в файл элементы построенного БДП в порядке их возрастания; вывести построенное БДП на экран.
//- "Текущий контроль" - создание программы для генерации заданий с ответами к ним для проведения текущего контроля 
//среди студентов. Задания и ответы должны выводиться в файл в удобной форме: тексты заданий должны быть готовы 
//для передачи студентам, проходящим ТК; ответы должны позволять удобную проверку правильности выполнения заданий.

//9	БДП: случайное* БДП; действие: 1+2в	Случайные БДП - вставка и исключение. Текущий контроль
#include<iostream>
#include <fstream>
#include <string.h>

using namespace std;

ifstream in("in.txt");
typedef int ID;
ofstream fin("out.txt");
struct TreeNode // данные 
{
    char value; //текущий элемент
	TreeNode *left; //ссылка на левый
    TreeNode *right; //ссылка на правый
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
    	void headBT(); //определение вершины дерева
    	

    	char RootBT(binTree b); // для непустого бин.дерева
    	TreeNode* headRootBT( )	;
    	binTree Left(binTree b);
    	binTree Right(binTree b);
    	
		void displayBT(binTree, ID );
    	void printTree();
    	void obhodBT(binTree b);   // Обход и вывод по возрастанию
 //   	bool findEL(char x , binTree b); //Поиск в дереве элемента
    	
	
    	int getMaxDepth(binTree b, ID n); // глубина дерева
    	int getCount(binTree b, ID n); //общее количество не нулевых вершин
    	
    	TreeNode* enterBT();
    	TreeNode* newElBT( char x);
    	TreeNode* enterElBT(char x , binTree b);
    	
		
		void destroyEL(binTree b);
		void destroyTree();

};
//функции
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
        else { return b->value;	}
}
TreeNode* BinaryTree::headRootBT( )			// для непустого бин.дерева
{
        if (head == NULL) { cerr << "Error: headRootBT(null) \n"; exit(1); }
        else {
		return head;	}
}

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


TreeNode* BinaryTree::newElBT( char x) //ввод листа
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
TreeNode* BinaryTree::enterElBT(char x , binTree b) //ввод вершины
{ 
  		if (b!=NULL) { cout<<"Элемент "<<b->value<<" -> ";
			if (x <= b->value)   { b->left=enterElBT(x,b->left);  }   
							else { b->right=enterElBT(x,b->right); }   
		  
		}
		else { 
		b = newElBT(x);
		cout<<" добавлен элемент "<<b->value << endl;
		} 
		return b;
}

TreeNode* BinaryTree::enterBT() //ввод дерева из файла
{
  	char ch;
//  TreeNode* p;
//	TreeNode* q;
    
 	if (!in.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
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

int BinaryTree::getCount(binTree b, ID n) //общее количество не нулевых вершин
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

/*bool BinaryTree::findEL(int x , binTree b) //ввод вершины
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
     
//     cout<< endl<<"Введите элемент "<< endl;
//	 int addValue;
//     cin>>addValue;
//     if (!Bin.findEL(addValue,Bin.headRootBT())) 
//	 	{   cout<< endl<<"Вставка элемента "<<addValue<< endl;
//	 		Bin.enterElBT(addValue,Bin.headRootBT());
//	 	} 
//	 else cout<< endl<<"Элемент "<<addValue<<"  в дереве существует"<< endl;    
     cout << endl<<"Элементы БДП в порядке их возрастания: " << endl;
     Bin.obhodBT(Bin.headRootBT());
     
     cout<< endl<<"Удаление";
	 Bin.destroyTree();
       
    }
   
	return 0;
}
