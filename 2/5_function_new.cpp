//4)	¬ставить заданное число элементов после элемента, имеющего заданное значение.
#include <string.h>
#include <iostream>
typedef  int TData;
struct list // объ€вление структуры
{
	TData field;    // поле данных
  	list *ptr; // указатель на следующий элемент
};
list* listcreate(list *lst);
void listprint(list *lst);
list* addressElNb (list *firstPtr, TData item);
void insert(list *firstPtr, int nb, TData item);
using namespace std;
int main()
{
	setlocale(0, "");
	TData digit;
	int count;
	list *MyList = new list; // создание ссылки на список
	MyList=NULL;

 	MyList=	listcreate(MyList);// создание списка

	listprint(MyList);	// печать списка
	
	cout<<endl<<"Vvedite elemnt ";
	cin>>digit;
	cout<<"Vvedite count ";
	cin>>count;
	insert(MyList, count, digit);//вставка после значени€ digit
										//count элементов
	
	listprint(MyList);	// печать списка
	
}
list* listcreate(list *lst) //создание списка
{
int count, item;	
	cout<<"Count ";//   оличество элементов в списке
	cin>>count;
	cout<<endl<<"Spisok"<<endl;
	list *newlist = new list;
	lst=newlist;// ссылка на начало нового списка
	list *currPtr= newlist;
	cin>>item;            // первый элемент 
   	newlist-> field = item;
	
	for (int i=1; i<count; i++){
		list *newlist = new list; // следующие элементы
		 cin>>item;            
   		newlist-> field = item;           
   		currPtr-> ptr= newlist;
		currPtr= newlist;
	}
	currPtr-> ptr =NULL;   // конец списка
  
  return lst;
}

void listprint(list *lst) //вывод элементов списка
{
	cout<<endl<<"Rezult "<<endl;
  list *p;
  p = lst;
  do  {
	  printf("%d ",p->field); // вывод значени€ элемента p
      p = p->ptr; // переход к следующему узлу
    }while(p != NULL);
    cout<<endl;
}

void insert(list *firstPtr, int nb,   TData item)
{
   if (NULL==firstPtr|| nb<=0) return; // если список пуст или количество дл€ добавлени€ отрицательное, =0
 
  list *currPtr = addressElNb(firstPtr,item); //поиск адреса элемента item
 
   if (currPtr==NULL) // узел отсутствует
      {cout<<endl<<"Elementa net"<<endl;
	  return;
	  }
	  
  	for (int i=0; i<nb; i++)
	  {// добавл€ем nb элементов со значением item
  		list *newlist = new list;           // 1 
   		newlist-> field = item;           // 2
   		newlist-> ptr = currPtr-> ptr; 	// 3
   		currPtr -> ptr = newlist;      	 // 4
		}
   return;
}
/*ѕоиск элемента с заданным номером
 ¬озвращает:
- указатель на элемент с полем item, 
- NULL - если элемент не найден */
list* addressElNb (list *firstPtr, TData item) 
{
	 
   if (firstPtr==NULL ) 
   // список пуст,
       return NULL;
   // проходим по всему списку, т.е. пока currPtr -> ptr!=NULL
   // и ищем поле со значением item
   list *currPtr = firstPtr;
   while((currPtr-> field != item) && (currPtr -> ptr!=NULL)) 
   {	
         currPtr = currPtr -> ptr;
   }
   
   if (currPtr -> ptr!=NULL) // узел найден 
      return currPtr;
   else  if (currPtr-> field == item)  return currPtr; // провер€ем узел  последний в списке
   			else    return NULL; // узел не найден
}
