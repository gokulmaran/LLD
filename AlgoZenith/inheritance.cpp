//INterview Set -->DSA,OOPS,Multithreading, OS, DBMS, CN
#include <bits/stdc++.h>
using namespace std;

/*
Hierarchical inheritance = One base class → Multiple derived classes
*/

class A{
  public:
     void showA(){
        cout<<"A class has been called"<<endl;
     }
};
class B:public A{
    public:
      void showB(){
        cout<<"B class has been called"<<endl;
     }
};
class C:public A{
    public:
      void showC(){
        cout<<"C class has been called"<<endl;
     }
};

int main(){
    B b;
    b.showB();
    b.showA();
}
////////////////////////
#include <bits/stdc++.h>
using namespace std;

/*
      A (single shared)
     / \
    B   C
     \ /
      D
A virtual base class is a base class that is inherited using virtual so that only one shared instance exists in the entire inheritance hierarchy.
*/

class A{
 public: 
    void show(){
        cout<<"A constructor called"<<endl;
    }
};
class B:virtual public A{};
class C:virtual public A{};
class D:public B,public C{};

int main(){
   D obj;
   obj.show();
}
////////////////////////////
#include <bits/stdc++.h>
using namespace std;
/*
Multilevel: chain A->B->C
*/

class A{
public:
    void showA(){
         cout<<"A constructor has been called"<<endl;
    }
};
class B:public A{

};
class C:public B{

};
int main(){
   C obj;
   obj.showA();
}
//operator overloading
#include <bits/stdc++.h>
using namespace std;

class Complex{
  public:
    int real,img;
    Complex(int r,int c){
        real=r;
        img=c;
    }

    Complex operator+(const Complex &c){
        return Complex(real+c.real,img+c.img);
    }

    void print(){
        cout<<real<<" + i"<<img<<endl;
    }
};

int main(){
    Complex c1(2,3),c2(4,5);
    Complex c3=c1+c2;
    c3.print();
}
////////////////////
#include <bits/stdc++.h>
using namespace std;

/*
✅ Deep Copy (Definition)

Deep copy creates a new object by allocating separate memory and copying the actual data, 
so the objects are independent of each other.
*/
class A{
  public:
     char*data;

     A(const char*str){
        data=new char[strlen(str)+1];
        strcpy(data,str);
     }

     A(const A &a){
        data=new char[strlen(a.data)+1];
        strcpy(data,a.data);
     }

     void print(){
        cout<<data<<endl;
     }
};

int main(){
   A a("Hello");
   A b=a;

    a.print();
   b.print();
   a.data[0]='L';
   a.print();
   b.print();
}
/////////////////////////////////
#include <bits/stdc++.h>
using namespace std;

/*
✅ Shallow Copy (Definition)

Shallow copy creates a new object by copying the memory addresses of the original object, so both objects share the same underlying data.
*/
class A{
   public:
      char*data;

      A(const char* str){
        data=new char[strlen(str)+1];
        strcpy(data,str);
      }

      void print(){
        cout<<data<<endl;
      }
};

int main(){
    A a("Hello");
    A b=a;

   a.print();
   b.print();

    a.data[0]='L';
    a.print();
    b.print();
}
/////////////////////////
#include <bits/stdc++.h>
using namespace std;

/*
Static variable: “Shared data across all objects of a class.”
Static function: “Function that operates on static data without needing objects.”

“Static functions don’t require objects because they are not associated with any instance and do not use the this pointer.”
*/

class A{
  public:
    static int cnt;

    A(){
        cnt++;
    }

    static void showCnt(){
        cout<<"Total cnt: "<<cnt<<endl;
    }
};

int A::cnt=0;

int main(){
   A a,a1,a2;
   A::showCnt();
}
///////////////////
#include <bits/stdc++.h>
using namespace std;

/*
Smart pointers are objects that manage memory automatically (no manual delete).

Pointer Type	Use case
unique_ptr	Default choice (safe + fast)
shared_ptr	When multiple ownership needed
weak_ptr	Avoid circular references

“make_unique and make_shared provide exception safety and efficient memory allocation, avoiding raw new.”
*/

int main(){
    //unique ptr
    unique_ptr<int>p1=make_unique<int>(10);

    cout<<*p1<<endl;

    unique_ptr<int>p2=move(p1);
    if(!p1){
        cout<<"p1 is empty"<<endl;
    }
    cout<<*p2<<endl;
    
    //shared_ptr
    shared_ptr<int>p3=make_shared<int>(20);
    shared_ptr<int>p4=p3;

    cout<<p3.use_count()<<endl;

    p4.reset();
    cout<<p3.use_count()<<endl;

    //weak ptr
    weak_ptr<int>w=p3;

    if(auto temp=w.lock()){
        cout<<*temp<<endl;
    }
}
///////////////////////////
#include <bits/stdc++.h>
using namespace std;

class Node{
  public:
      int data;
      Node*next;

      Node(int d){
        data=d;
        next=NULL;
      }
};

Node*reverseLL(Node*head){
   Node*prev=NULL;
   Node*curr=head;

   while(curr){
    Node*temp=curr->next;
    curr->next=prev;
    prev=curr;
    curr=temp;
   }
   
   return prev;
}

void print(Node*head){
    Node*temp=head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}
int main(){
    Node*head=new Node(20);
    head->next=new Node(30);
    head->next->next=new Node(40);
    
    print(head);

    Node*rHead=reverseLL(head);
    print(rHead);
}
////////////////////