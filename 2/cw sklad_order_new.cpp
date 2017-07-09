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
{	//������ 
   TData  data; 
   TDataName field;
    
   Node *next; 
};
class List 
{ private:
      Node *head; // ������ ������
      Node *curr, // ������� ������� 
           *predCurr; // �������, �������������� ��������

   public:
      // �����������
      List(){head=curr=predCurr=NULL;};
	  // ������������� ��������� ������ 
    int null() {return head == NULL;};
    int endOfList(){return curr==NULL;};
    
											// ���������� ������ �� ������
											TData getData(){return curr->data;	};
											Node getCurrentElement() { return *curr; }
										    
	  
	void insertAfter (TData item, TDataName name); 
	Node* addNode( TData item, TDataName name );  
			
									void addNumber( TData item) { curr->data+=item;};// ��������� ���������� ������
									void subOrder (TData item) {curr->data-=item;} ; //������ ���������� ������	
	void Show();
    
     Node* findEl( TDataName name);
    // ������� ��������� ������
    void goBegin ();
    void goNext ();
   											 void goLast();
											 void deleteEl();
    										 void clearList();	
}; 
void List::Show() //������� ����������� ������ �� ������
{
  curr=head; //���������� ���������, ������� ���������� �� ����� ������ ������ ������
  while (!endOfList())//�� ��� ��� ���� �� �������� ������ ��������
 {
 	printf(" %-10s%5d\n",curr->field,curr->data);//������� ������� x �� ������
  //cout<<curr->field<<"  "<<curr->data<<endl; 
  curr=curr->next; //���������, ��� ����� ��� ����� ��������� �������
 	
 }
 cout<<endl;
}

void List::insertAfter(TData item,TDataName name) 
{
   Node *newNode;
   if (null()||endOfList())
   // �������� � ������ ������ ��� � ������ ������
   { 
      newNode = addNode(item, name);
      predCurr= head = curr = newNode;
   }
   else
   // �������� ������ ������ ��� � ��� �����
   {  predCurr=curr;  // ���������� �������
      newNode = addNode(item,name);
      predCurr -> next = newNode;
      // ����������� ������� ���������� �������
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
 	 if (null()) return NULL;    // ������ ����
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
   // �����, ���� ������ � ��������� Null ��� EOList
   if (null()||endOfList()) return;
   // ������� ������� ��������� ������� ������
      predCurr = curr;
      curr = curr->next; 
}
void List::goLast()
{
   // �����, ���� ������ � ��������� Null ��� EOList
   if (null() ||endOfList()) return;
         curr=head; //���������� ���������, ������� ���������� �� ����� ������ ������ ������
		  while (getCurrentElement().next!=NULL)//�� ��� ��� ���� �� �������� ������ ��������
		 {
		   curr=curr->next; //���������, ��� ����� ��� ����� ��������� �������
		 }
	//	cout<<"Last "<<curr->field<<"   "<<curr->data<<"  "<< endl; // ����� ��� �������
}

 void List::deleteEl()
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
void List::clearList() 
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
		
	cout<<"��������� �������\n";
	cout<<"\n������ � ����� ������:\n";
	cout<<"1. �������� ������\n";
	cout<<"2. ����������� ��������� �����\n";
	cout<<"3. ���������� ������� \n";
	cout<<"\n���������� �������\n";
	cout<<"4. ������� ����� ������ ������\n";
	cout<<"5. ������� ����� ���������� ������� \n";
	cout<<"\n6. �����\n";
	
	

	TData num;
	TDataName str;
	List list;
	List order;
	int operation=0;
	while(operation!=6)
	{  
	cout<<endl<<"�������� �������� �� ������������: ";
	cin>>operation;
		
	switch(operation)
	{
	case 1: 
		{cout<<" �������� ������ "<<endl;
		if(list.null()) {
		ifstream fin("put_in.txt");
		if (!fin.is_open()) // ���� ���� �� ������
			cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
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
		cout<<" ����������� ��������� ����� "<<endl;
		list.Show();
		break;
		}
	case 3: 
    	{	
			cout<<" ���������� ������� "<<endl;
    		
			cout<<"������� ������������ ������: ";
			SetConsoleCP(1251);
			cin>>str;
			SetConsoleCP(866);
			
			cout << "������� ����������: "; 
			cin>>num;
			
			if (num<=0)
			{cout<<"���������� ������ ����������, �� ����������� ����� ������ \n";
			break;
			}
			
			
			if (list.findEl(str)!= NULL)                  
			{cout << "��������� ���������� ������\n"; 
			list.addNumber(num);
			}
			else { 
				list.goLast();
				cout << "��������� ����� �����\n";
				list.insertAfter(num,str);
				}
			break;
		}
	case 4:
		{
			cout<<"������� ����� \n";
			cout<<"������� ������������ ������: ";
			SetConsoleCP(1251);
			cin>>str;
			SetConsoleCP(866);
			cout << "������� ����������: "; 
			cin>>num;
			
			if (num<=0)
			{cout<<"���������� ������ ����������, �� ����������� ����� ������ \n";
			break;
			}
			
						
			if ((list.findEl(str) != NULL) &&(list.getData()>=num))
			{	cout <<  "����� ��������.  \n"; 
				list.subOrder(num);			
				if (list.getData()==0) list.deleteEl();
				}
			else cout << "����� �� ����� ���� ��������. ������� ������ ��� �� ������. \n";
			break;
		}
	case 6: 
		{
		cout<<" ����� �� ��������� "<<endl;
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
		if(order.null()) //���� �������� � ������� �������������
		{					// ������ ������� �� �����������
		ifstream fin("put_out.txt");
		if (!fin.is_open()) // ���� ���� �� ������
			{cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
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
		
		cout<<" ����� "<<endl;
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
					cout <<"����� "<< order.getCurrentElement().field<< " ����.\n";
					flag=1; }
					else
					cout <<"���������� ������ "<< order.getCurrentElement().field<< " �� ���������� \n";
					
					break;	// ���� ����� ���� � ������, �� ����� ����� �� �����
				}
				else
				cout << order.getCurrentElement().field<<"- ����� ������ ��� �� ������: \n";
			
			list.goNext();
			
			}
			
			if (flag==0) {
				
				cout << "\n����� �� ����� ���� ��������. ������� ������ ��� �� ������: \n";
				cout<<order.getCurrentElement().field<< " � ���������� " << order.getData()<<endl;
				break;
			}
			order.goNext();
		}
		if (flag==1)  //��� ����� ����� �����������
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
		cout <<" ����� ��������.  \n";
		unlink("put_out.txt");// ������� ���� put_out.txt
		order.clearList();
		} 

		break;
		}
		
	default: cout<<"��������� �������� �� �������"<<endl;
	}	
	}
}
