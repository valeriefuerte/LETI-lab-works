//4)	�������� �������� ����� ��������� ����� ��������, �������� �������� ��������.
#include <string.h>
#include <iostream>
typedef  int TData;
struct list // ���������� ���������
{
	TData field;    // ���� ������
  	list *ptr; // ��������� �� ��������� �������
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
	list *MyList = new list; // �������� ������ �� ������
	MyList=NULL;

 	MyList=	listcreate(MyList);// �������� ������

	listprint(MyList);	// ������ ������
	
	cout<<endl<<"Vvedite elemnt ";
	cin>>digit;
	cout<<"Vvedite count ";
	cin>>count;
	insert(MyList, count, digit);//������� ����� �������� digit
										//count ���������
	
	listprint(MyList);	// ������ ������
	
}
list* listcreate(list *lst) //�������� ������
{
int count, item;	
	cout<<"Count ";//  ���������� ��������� � ������
	cin>>count;
	cout<<endl<<"Spisok"<<endl;
	list *newlist = new list;
	lst=newlist;// ������ �� ������ ������ ������
	list *currPtr= newlist;
	cin>>item;            // ������ ������� 
   	newlist-> field = item;
	
	for (int i=1; i<count; i++){
		list *newlist = new list; // ��������� ��������
		 cin>>item;            
   		newlist-> field = item;           
   		currPtr-> ptr= newlist;
		currPtr= newlist;
	}
	currPtr-> ptr =NULL;   // ����� ������
  
  return lst;
}

void listprint(list *lst) //����� ��������� ������
{
	cout<<endl<<"Rezult "<<endl;
  list *p;
  p = lst;
  do  {
	  printf("%d ",p->field); // ����� �������� �������� p
      p = p->ptr; // ������� � ���������� ����
    }while(p != NULL);
    cout<<endl;
}

void insert(list *firstPtr, int nb,   TData item)
{
   if (NULL==firstPtr|| nb<=0) return; // ���� ������ ���� ��� ���������� ��� ���������� �������������, =0
 
  list *currPtr = addressElNb(firstPtr,item); //����� ������ �������� item
 
   if (currPtr==NULL) // ���� �����������
      {cout<<endl<<"Elementa net"<<endl;
	  return;
	  }
	  
  	for (int i=0; i<nb; i++)
	  {// ��������� nb ��������� �� ��������� item
  		list *newlist = new list;           // 1 
   		newlist-> field = item;           // 2
   		newlist-> ptr = currPtr-> ptr; 	// 3
   		currPtr -> ptr = newlist;      	 // 4
		}
   return;
}
/*����� �������� � �������� �������
 ����������:
- ��������� �� ������� � ����� item, 
- NULL - ���� ������� �� ������ */
list* addressElNb (list *firstPtr, TData item) 
{
	 
   if (firstPtr==NULL ) 
   // ������ ����,
       return NULL;
   // �������� �� ����� ������, �.�. ���� currPtr -> ptr!=NULL
   // � ���� ���� �� ��������� item
   list *currPtr = firstPtr;
   while((currPtr-> field != item) && (currPtr -> ptr!=NULL)) 
   {	
         currPtr = currPtr -> ptr;
   }
   
   if (currPtr -> ptr!=NULL) // ���� ������ 
      return currPtr;
   else  if (currPtr-> field == item)  return currPtr; // ��������� ����  ��������� � ������
   			else    return NULL; // ���� �� ������
}
