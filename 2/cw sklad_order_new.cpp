#include <iostream>
#include <fstream>
#include <cstddef>
#include <stdexcept>
#include <string.h>
#include <Windows.h>
#include <io.h>

const unsigned int MAX_STR_LEN = 100;

using namespace std;
typedef int TData;
typedef char TDataName[MAX_STR_LEN + 1];
struct Node
{	//данные 
   TData  data; 
   TDataName field;
    
   Node *next; 
};
class List 
{ private:
      Node *head; // начало списка
      Node *curr, // текущий элемент 
           *predCurr; // элемент, предшествующий текущему

   public:
      // конструктор
      List(){head=curr=predCurr=NULL;};
	  // идентификация состояния списка 
    int null() {return head == NULL;};
    int endOfList(){return curr==NULL;};
    
											// считывание данных из списка
											TData getData(){return curr->data;	};
											Node getCurrentElement() { return *curr; }
										    
	  
	void insertAfter (TData item, TDataName name); 
	Node* addNode( TData item, TDataName name );  
			
									void addNumber( TData item) { curr->data+=item;};// прибавить количество товара
									void subOrder (TData item) {curr->data-=item;} ; //отнять количество товара	
	void Show();
    
     Node* findEl( TDataName name);
    // функции навигации списка
    void goBegin ();
    void goNext ();
   											 void goLast();
											 void deleteEl();
    										 void clearList();	
}; 
void List::Show() //Функция отображения списка на экране
{
  curr=head; //Определяем указатель, который изначально он равен адресу начала списка
  while (!endOfList())//До тех пор пока не встретит пустое значение
 {
 	printf(" %-10s%5d\n",curr->field,curr->data);//Выведет элемент x из списка
  //cout<<curr->field<<"  "<<curr->data<<endl; 
  curr=curr->next; //Указываем, что далее нам нужен следующий элемент
 	
 }
 cout<<endl;
}

void List::insertAfter(TData item,TDataName name) 
{
   Node *newNode;
   if (null()||endOfList())
   // вставить в пустой список или в начало списка
   { 
      newNode = addNode(item, name);
      predCurr= head = curr = newNode;
   }
   else
   // вставить внутрь списка или в его конец
   {  predCurr=curr;  // запоминаем текущий
      newNode = addNode(item,name);
      predCurr -> next = newNode;
      // вставленный элемент становится текущим
      predCurr=curr= newNode;  
   }
}
  Node* List::addNode(TData item,TDataName name )
{
 	Node *newLst = new Node;   
   	newLst-> data = item; 
   	strcpy( newLst->field,name);
	newLst-> next= NULL;
	return newLst;
}

Node* List::findEl( TDataName name)
 { 
 	 if (null()) return NULL;    // список пуст
  	goBegin();
  	int k=strlen(name);
	
	while  ((curr->next != NULL) && (strncmp(curr->field,name,k) != 0) )

   {//	cout<<curr-> data<<"  "<< curr->field<<" !!! "<<name<< strncmp(curr->field,name,k)<<" !!! "<<endl;
  		  goNext();       
    }
    //	cout<<curr-> data<<"  "<< curr->field<<" !!! "<<name<< strncmp(curr->field,name,k)<<" ostanovrf "<<endl;
    if ((curr->next != NULL))
	return curr;
    else if((strncmp(curr->field,name,k) == 0)) return curr; 
    		else 
			return NULL;
 }
 
 void List::goBegin()
{
   if (null()) return;
   curr = head;
   predCurr = NULL;
}

void List::goNext()
{
   // выйти, если список в состоянии Null или EOList
   if (null()||endOfList()) return;
   // сделать текущим следующий элемент списка
      predCurr = curr;
      curr = curr->next; 
}
void List::goLast()
{
   // выйти, если список в состоянии Null или EOList
   if (null() ||endOfList()) return;
         curr=head; //Определяем указатель, который изначально он равен адресу начала списка
		  while (getCurrentElement().next!=NULL)//До тех пор пока не встретит пустое значение
		 {
		   curr=curr->next; //Указываем, что далее нам нужен следующий элемент
		 }
	//	cout<<"Last "<<curr->field<<"   "<<curr->data<<"  "<< endl; // вывод для отладки
}

 void List::deleteEl()
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
void List::clearList() 
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
		
	cout<<"Мебельная фабрика\n";
	cout<<"\nРабота с базой данных:\n";
	cout<<"1. Создание списка\n";
	cout<<"2. Отображение продукции фирмы\n";
	cout<<"3. Добавление товаров \n";
	cout<<"\nВыполнение заказов\n";
	cout<<"4. Сделать заказ одного товара\n";
	cout<<"5. Сделать заказ нескольких товаров \n";
	cout<<"\n6. Выход\n";
	
	

	TData num;
	TDataName str;
	List list;
	List order;
	int operation=0;
	while(operation!=6)
	{  
	cout<<endl<<"Выберите действие из предложенных: ";
	cin>>operation;
		
	switch(operation)
	{
	case 1: 
		{cout<<" Создание списка "<<endl;
		if(list.null()) {
		ifstream fin("put_in.txt");
		if (!fin.is_open()) // если файл не открыт
			cout << "Файл не может быть открыт!\n"; // сообщить об этом
		else
		while(!fin.eof())
		{
			fin>>num;
			fin.getline(str, MAX_STR_LEN);
		//	cout << num << ", " << str << endl;
			list.insertAfter(num,str);
		}
		fin.close();
		}
		break;
		}
	case 2:
		{
		cout<<" Отображение продукции фирмы "<<endl;
		list.Show();
		break;
		}
	case 3: 
    	{	
			cout<<" Добавление товаров "<<endl;
    		
			cout<<"Введите наименование товара: ";
			SetConsoleCP(1251);
			cin>>str;
			SetConsoleCP(866);
			
			cout << "Введите количество: "; 
			cin>>num;
			
			if (num<=0)
			{cout<<"Добавление товара невозможно, Вы неправильно ввели данные \n";
			break;
			}
			
			
			if (list.findEl(str)!= NULL)                  
			{cout << "Добавляем количество товара\n"; 
			list.addNumber(num);
			}
			else { 
				list.goLast();
				cout << "Добавляем новый товар\n";
				list.insertAfter(num,str);
				}
			break;
		}
	case 4:
		{
			cout<<"Сделать заказ \n";
			cout<<"Введите наименование товара: ";
			SetConsoleCP(1251);
			cin>>str;
			SetConsoleCP(866);
			cout << "Введите количество: "; 
			cin>>num;
			
			if (num<=0)
			{cout<<"Выполнение заказа невозможно, Вы неправильно ввели данные \n";
			break;
			}
			
						
			if ((list.findEl(str) != NULL) &&(list.getData()>=num))
			{	cout <<  "Заказ выполнен.  \n"; 
				list.subOrder(num);			
				if (list.getData()==0) list.deleteEl();
				}
			else cout << "Заказ не может быть выполнен. Данного товара нет на складе. \n";
			break;
		}
	case 6: 
		{
		cout<<" Выход из программы "<<endl;
		ofstream fout("put_in.txt");
		if (fout.is_open())
		{	
		if (!list.null())
		{
		
			list.goBegin();
//		
			while ( list.getCurrentElement().next !=NULL)
			{
			fout<<list.getCurrentElement().data<<list.getCurrentElement().field << endl;
			//cout<<list.getCurrentElement().data<<" "<<list.getCurrentElement().field << endl;
			list.goNext();
			}
			fout<<list.getCurrentElement().data<<list.getCurrentElement().field;
		//	cout<<list.getCurrentElement().data<<" "<<list.getCurrentElement().field << endl;
		}
			
		fout.close();
		}
		else cout<<"No";
		
		 if (!list.null()) list.clearList();
		 if (!order.null()) order.clearList();
		
		break;
		}
	case 5:
		{
		if(order.null()) //если работаем с заказом первоначально
		{					// список заказов не сформирован
		ifstream fin("put_out.txt");
		if (!fin.is_open()) // если файл не открыт
			{cout << "Файл не может быть открыт!\n"; // сообщить об этом
			break;
			}
		else
		while(!fin.eof())
		{
			fin>>num;
			fin.getline(str, MAX_STR_LEN);
			order.insertAfter(num,str);
		}
		fin.close();
		}
		
		cout<<" Заказ "<<endl;
		order.Show();
		order.goBegin();
		int flag=0;
		while ( !order.endOfList() )
		{	flag=0;	
		
			list.goBegin();
			while (!list.endOfList() )
			{ 
				if ( list.findEl(order.getCurrentElement().field) != NULL)
				{	
					if(list.getData()>=order.getData())
					{
					cout <<"Товар "<< order.getCurrentElement().field<< " есть.\n";
					flag=1; }
					else
					cout <<"Количество товара "<< order.getCurrentElement().field<< " не достаточно \n";
					
					break;	// если товар есть в списке, то нужно выйти из цикла
				}
				else
				cout << order.getCurrentElement().field<<"- этого товара нет на складе: \n";
			
			list.goNext();
			
			}
			
			if (flag==0) {
				
				cout << "\nЗаказ не может быть выполнен. Данного товара нет на складе: \n";
				cout<<order.getCurrentElement().field<< " в количестве " << order.getData()<<endl;
				break;
			}
			order.goNext();
		}
		if (flag==1)  //код когда заказ выполняется
		{
		order.goBegin();
		while ( !order.endOfList() )
		{	
			list.goBegin();
			while (! list.endOfList() )
			{ 
				if ((list.findEl(order.getCurrentElement().field) != NULL))
				{	
					list.subOrder(order.getCurrentElement().data);
					if (list.getData()==0) list.deleteEl();
					break;
				}
			list.goNext();
			}
			order.goNext();
		}
		cout <<" Заказ выполнен.  \n";
		unlink("put_out.txt");// удалить файл put_out.txt
		order.clearList();
		} 

		break;
		}
		
	default: cout<<"Выбранная операция не найдена"<<endl;
	}	
	}
}
