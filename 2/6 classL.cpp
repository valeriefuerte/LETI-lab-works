#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
typedef  int TData;
struct Node
{
   TData  data;  // проблемные данные 
   Node *next; 
};
class L1List 
{ private:
      Node *head; // начало списка
      Node *curr, // текущий элемент 
           *predCurr; // элемент, предшествующий текущему

   public:
      // конструктор
      L1List(){head=curr=predCurr=NULL;};
      // деструктор
      ~L1List() {c1earList();};
	  // идентификация состояния списка 
    int null() {return head == NULL;};
    int endOfList(){return curr==NULL;};
      
    void insertAfter (TData item);
    Node* addNode( TData item, Node *ptrNext );  
	   
    void Show();
    int find (TData item);
       
    void deleteEl();
    void c1earList();
    
}; 
void L1List::Show() //Функция отображения списка на экране
{
  curr=head; //Определяем указатель, который изначально он равен адресу начала списка
  while (!endOfList()) //До тех пор пока не встретит пустое значение
 {
  cout<<curr->data<<"   "; //Выведет элемент x из списка
  curr=curr->next; //Указываем, что далее нам нужен следующий элемент
 }
 cout<<endl;
}
void L1List::insertAfter(TData item) 
{
	
   Node *newNode;
   if (null()||endOfList())
   // вставить в пустой список или в нача-ло списка
   { 
      newNode = addNode(item, head);
      predCurr= head = curr = newNode;
   }
   else
   // вставить внутрь списка или в его конец
   { 
      newNode = addNode(item, curr);
      predCurr -> next = newNode;
      // вставленный элемент становится текущим
      predCurr=curr= newNode;  
   }
  // 	cout<<head<<"   "<<curr<<"  "<<predCurr<<"  "<<curr->data<<endl;
  }
Node* L1List::addNode(TData item, Node *ptrNext )
{
 	Node *newLst = new Node;   
   	newLst-> data = item; 
	newLst-> next= NULL;
	ptrNext= newLst;
	return ptrNext;
}
int L1List::find (TData item) 
{
   if (null( )) return 0;    // список пуст
   curr = head;
   int j=1; 
   int flag=0;
     while(!endOfList()) 
   {	
  		 if ( curr-> data == item) 
		   {cout<<j<<endl;
		     flag=1;
		   }
         curr = curr -> next;
         j++;
    }
        return flag;
 }

 void L1List::deleteEl()
{
   // выйти, если список в состоянии Null или EOList
      if (null()||endOfList()) return;
   if (curr == head)
   // удалить первый элемент
   {  head = head -> next;
      delete curr;
      curr = head;
      return;
   }
   else {
   // удалить внутренний или последний узел 
      predCurr -> next = curr -> next;
      delete curr;
      curr = predCurr -> next;
   }
}
void L1List::c1earList() 
{
   if (null()) return; // список уже пуст
      curr = head;
      while (!null())
   // удалить текущий (первый) элемент списка
         deleteEl();
}

int main()
{
	setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
	L1List olist;
	TData i;

	int operation=0;
	cout<<"Действия со списком:\n";
	cout<<"1. Создание списка\n";
	cout<<"2. Поиск\n";
	cout<<"3. Удаление списка \n";
	cout<<"4. Вывод списка на экран\n";
	cout<<"5. Выход\n";
	
	
	while(operation!=5)
	{  cout<<endl<<"Выберите действие из предложенных: ";
		cin>>operation;
		
	switch(operation)
	{
	case 1: 
	{
	
	cout<<" Создание списка "<<endl;
	ifstream fin("putin.txt");
 	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{ while(!fin.eof())
		{fin>>i;
		olist.insertAfter(i);
		}
	fin.close(); //закрытие файла
	}
	break;
	}
	case 2:
		
		cout<<" Найти номера всех элементов с заданным значением "<<endl;
		cout<<"Введите элемент для поиска  ";
		cin >>i;
		cout<<endl<<"Номер в списке: "<<endl;
		if (olist.find(i)==0) cout<<"Элемент не найден\n";
		break;
		
    case 3: 
    cout<<" Удаление списка "<<endl;
	olist.c1earList(); 	break;
	
	case 4: 
	cout<<" Вывод списка на экран "<<endl;
	olist.Show(); break;
	
	case 5: 
	cout<<" Выход из программы "<<endl;
	break;
	default: cout<<"Выбранная операция не найдена"<<endl;
	}	
	}
	return 1;
}
