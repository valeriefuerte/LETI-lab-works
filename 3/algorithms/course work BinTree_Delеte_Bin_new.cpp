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

// http://purecodecpp.com/archives/1012
//rand() — генератор случайных чисел в C++
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

struct TreeNode // данные 
{
    int value;
	TreeNode *left;
    TreeNode *right;
    TreeNode() { left = NULL; right = NULL; } // constructor 
};
typedef TreeNode *binTree; // "представитель" бинарного дерева
binTree q;
class BinaryTree
{
    private: 
	   TreeNode *head;
	   TreeNode *link;
    public:
		TreeNode* Create();
    	bool isNull();
    	void headBT(); //определение вершины дерева
    	

    	int RootBT(binTree b); // для непустого бин.дерева
    	TreeNode* headRootBT( )	;
    	binTree Left(binTree b);
    	binTree Right(binTree b);
    	
    	void displayData(); 
		void displayBT(binTree, ID );
    	void printTree();
    	
		void printT(binTree b, unsigned k); //Печать дерева новый вариант
    	
	
		
		void obhodBT(binTree b);   // Обход и вывод по возрастанию
    	bool findEL(int x , binTree b); //Поиск в дереве элемента
    	    	
    	TreeNode* enterBT();
    	TreeNode* newElBT( int x);
    	TreeNode* enterElBT(int x , binTree b);
    	
		void destroyEL(binTree b);
		void destroyTree();
		
		bool sheetCheck(int x, binTree b);
		TreeNode* delTree(int x, binTree b);
		TreeNode* delEl(binTree b);
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
int BinaryTree::RootBT(binTree b )			// для непустого бин.дерева
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
TreeNode* BinaryTree::newElBT( int x) //ввод листа
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
TreeNode* BinaryTree::enterElBT(int x , binTree b) //ввод вершины
{ 
  		if (b!=NULL) { cout<<"Элемент "<<b->value<<" -> ";
			if (x <= b->value)   { b->left=enterElBT(x,b->left);   }   
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
  	int ch;
  	count=0;
 	if (!in.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
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
	in.close(); //закрытие файла
	}
}
void BinaryTree::displayBT(binTree b, ID n)
{	// n - уровень узла
	if (b != NULL) {
        cout << " " << RootBT(b);
        keys << " " << RootBT(b);
        if (Right(b)!= NULL) { displayBT(Right(b), n + 1); }
        else {cout << endl; keys<<endl;}// вниз
        if (Left(b)!= NULL) {
            for (int i = 1; i <= n; i++){ cout << "  "; keys<<"  ";}// вправо
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
    	cout <<endl<< "Исходные данные " << endl;
    	task << "По исходным данным: " ;
        for (int i = 0; i < count; i++) 
        {
		 cout<<data[i]<<" ";
		 task<<data[i]<<" ";
        }
        cout<<endl;
        task<<" построить бинарное дерево поиска."<<endl;
    }
    else{};
}


void BinaryTree::printTree()
{ binTree b=headRootBT();
  ID n=1;
  keys<<endl<<"Построение бинарного дерева поиска: "<<endl;
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

bool BinaryTree::sheetCheck(int x, binTree b)   // проверка на ЛИСТ
 { if (b!=NULL)
 	{
	if (x!=b->value) 
	 	if (x < b->value)   { sheetCheck(x,b->left);  }   
					else    { sheetCheck(x,b->right); }  
	else
		{ 	  	
		 if ((Right(b)== NULL) && (Left(b)== NULL)) //нет поддеревьев
			 return false;
			else  return true; // одно поддерево	
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
    		{	cout<<"Найден элемент для удаления "<<b->value; 
				//task<<"Удалить элемент "<<b->value;	  
		    	q=b; 
		    	  	
//			 	if ((Right(q)== NULL) && (Left(q)== NULL)) //нет поддеревьев
//				 { cout<<" у него нет поддеревьев"<<endl;
//				 b=NULL;
//				  }
//			   	  else 	
						// одно поддерево		   
		 			if (Right(q)== NULL) {
		 			cout<<" у него нет правого поддерева"<<endl;
			   	   	b=q->left;
			   	   	}
					else 
					if (Left(q)== NULL) {
					cout<<" у него нет левого поддерева"<<endl;
					b=q->right;
					}
				    
					else  // два поддерева
					{ 
					cout<<" у него два поддерева ";
					binTree y=q->right;
					if(Left(y) == NULL)  // нет у правой ветви левого листа
					{
					cout<<" но у правой ветви нет левого листа"<<endl;
					y->left = q->left;
					b=y;
					}
						else
						{
						binTree z=y->left;  // есть у правой ветви левый лист
						while(Left(z) != NULL)
						{
							y = z;
							z = y->left;
						}
						cout<<" находим в правой ветви самый левый лист"<<endl;
						//cout<<"b="<<b->value<<" q="<<q->value<<" y="<<y->value<<" z="<<z->value<<endl;
						y->left = z->right;
						z->left = q->left;
						z->right =q->right;
						b=z;
						
						}
					}
			}
	} 
	if (q==head) head=b;   //если удаляем вершину, то нужно поменять ссылку на голову дерева
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
	setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы

	BinaryTree Bin;
	Bin.Create();
    Bin.enterBT();
    Bin.headBT();
    ID depth = 1;
    if (Bin.isNull( )) cout << "Пустое БД" << endl;
    else
    {
     Bin.displayData();
	 cout << endl<<"Бинарное дерево: " << endl;
     Bin.printTree();
    //Bin.printT(Bin.headRootBT(),0);                                 // СРАВНИ ВЫВОД
	/*  task<<"Записать элементы дерева по возрастанию."<<endl;
     keys<< endl<<"Элементы дерева по возрастанию: "<<endl;
	 Bin.obhodBT(Bin.headRootBT());
	 */	      
    srand(time(NULL));
    int addValue;
    cout<<"Генерировались элементы для вставки ";
    while(true)
	{
	addValue=rand() % 41 - 20; // Случайное число oт —20 дo 20
     cout<<addValue<<" ";
	if (!Bin.findEL(addValue,Bin.headRootBT())) 
	 	{   cout<< endl<<"Вставка элемента "<<addValue<< endl;
	 		task <<endl<<"Добавить элемент: "<<addValue<< endl;
	 		keys<<endl<<endl<<"Добавление элемента "<<addValue<< endl;
	 		Bin.enterElBT(addValue,Bin.headRootBT());
	 		Bin.printTree();
	 		break;
	 		} 
	/* else {
	 	   task <<endl<<"Добавить элемент: "<<addValue<< endl;
	 	   keys<<endl<<endl<<"Добавление элемента "<<addValue<< endl;
		   cout<< endl<<"Элемент "<<addValue<<"  в дереве существует"<< endl;
		   keys<< endl<<"Элемент "<<addValue<<"  в дереве существует"<< endl;}
     */
	}
    // cout<< endl<<"Удаление"<<endl;
     int delValue;
     cout<<"Генерировались элементы для удаления ";
	 while(true)
	{ delValue=rand() % 41 - 20; // Случайное число oт —20 дo 20
      cout<<delValue<< " ";  
	 if (Bin.findEL(delValue,Bin.headRootBT())) 	//  есть элемент
	 	{
	 	if (Bin.sheetCheck(delValue,Bin.headRootBT())) // есть поддеревья
	 	{   cout<< endl<<"Удаление элемента "<<delValue<<endl;
	 		task<< endl<<"Удалить элемент: "<<delValue<<endl;
	 		keys<<endl<<endl<<"Удаление элемента "<<delValue<<endl;
	 		Bin.delTree(delValue,Bin.headRootBT());
	 		Bin.printTree();
	  		break;
	 	} 
		}
	}
	/* else {
	 cout<< endl<<"Удаление элемента "<<delValue<<endl;
	 cout<< endl<<"Элемент "<<delValue<<"  в дереве не существует"<< endl;
	 task<< endl<<"Удалить элемент: "<<delValue<<endl;
	 keys<< endl<<"Элемент "<<delValue<<"  в дереве не существует"<< endl;
	 }*/
	// cout << endl<<"Бинарное дерево: " << endl;
	 //keys<< endl<<"Бинарное дерево: " << endl;
     //Bin.printTree();
     
	 /*cout << endl<<"Обход бинарного дерева: " << endl;
	 keys<< endl<<"Элементы дерева по возрастанию: "<<endl;
     Bin.obhodBT(Bin.headRootBT());*/
     
     
	 Bin.destroyTree();
    }
   	return 0;
}
