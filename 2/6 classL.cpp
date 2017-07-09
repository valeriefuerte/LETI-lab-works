#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
typedef  int TData;
struct Node
{
   TData  data;  // ���������� ������ 
   Node *next; 
};
class L1List 
{ private:
      Node *head; // ������ ������
      Node *curr, // ������� ������� 
           *predCurr; // �������, �������������� ��������

   public:
      // �����������
      L1List(){head=curr=predCurr=NULL;};
      // ����������
      ~L1List() {c1earList();};
	  // ������������� ��������� ������ 
    int null() {return head == NULL;};
    int endOfList(){return curr==NULL;};
      
    void insertAfter (TData item);
    Node* addNode( TData item, Node *ptrNext );  
	   
    void Show();
    int find (TData item);
       
    void deleteEl();
    void c1earList();
    
}; 
void L1List::Show() //������� ����������� ������ �� ������
{
  curr=head; //���������� ���������, ������� ���������� �� ����� ������ ������ ������
  while (!endOfList()) //�� ��� ��� ���� �� �������� ������ ��������
 {
  cout<<curr->data<<"   "; //������� ������� x �� ������
  curr=curr->next; //���������, ��� ����� ��� ����� ��������� �������
 }
 cout<<endl;
}
void L1List::insertAfter(TData item) 
{
	
   Node *newNode;
   if (null()||endOfList())
   // �������� � ������ ������ ��� � ����-�� ������
   { 
      newNode = addNode(item, head);
      predCurr= head = curr = newNode;
   }
   else
   // �������� ������ ������ ��� � ��� �����
   { 
      newNode = addNode(item, curr);
      predCurr -> next = newNode;
      // ����������� ������� ���������� �������
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
   if (null( )) return 0;    // ������ ����
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
   // �����, ���� ������ � ��������� Null ��� EOList
      if (null()||endOfList()) return;
   if (curr == head)
   // ������� ������ �������
   {  head = head -> next;
      delete curr;
      curr = head;
      return;
   }
   else {
   // ������� ���������� ��� ��������� ���� 
      predCurr -> next = curr -> next;
      delete curr;
      curr = predCurr -> next;
   }
}
void L1List::c1earList() 
{
   if (null()) return; // ������ ��� ����
      curr = head;
      while (!null())
   // ������� ������� (������) ������� ������
         deleteEl();
}

int main()
{
	setlocale(LC_ALL, "rus"); // ���������� ����������� ���������
	L1List olist;
	TData i;

	int operation=0;
	cout<<"�������� �� �������:\n";
	cout<<"1. �������� ������\n";
	cout<<"2. �����\n";
	cout<<"3. �������� ������ \n";
	cout<<"4. ����� ������ �� �����\n";
	cout<<"5. �����\n";
	
	
	while(operation!=5)
	{  cout<<endl<<"�������� �������� �� ������������: ";
		cin>>operation;
		
	switch(operation)
	{
	case 1: 
	{
	
	cout<<" �������� ������ "<<endl;
	ifstream fin("putin.txt");
 	if (!fin.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
	else
	{ while(!fin.eof())
		{fin>>i;
		olist.insertAfter(i);
		}
	fin.close(); //�������� �����
	}
	break;
	}
	case 2:
		
		cout<<" ����� ������ ���� ��������� � �������� ��������� "<<endl;
		cout<<"������� ������� ��� ������  ";
		cin >>i;
		cout<<endl<<"����� � ������: "<<endl;
		if (olist.find(i)==0) cout<<"������� �� ������\n";
		break;
		
    case 3: 
    cout<<" �������� ������ "<<endl;
	olist.c1earList(); 	break;
	
	case 4: 
	cout<<" ����� ������ �� ����� "<<endl;
	olist.Show(); break;
	
	case 5: 
	cout<<" ����� �� ��������� "<<endl;
	break;
	default: cout<<"��������� �������� �� �������"<<endl;
	}	
	}
	return 1;
}
