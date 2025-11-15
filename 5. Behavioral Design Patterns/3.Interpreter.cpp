#include <iostream>
using namespace std;
/*
client--> Interface
            ||-->concrete interfaces(Number class, additon class)
*/
//INterface
class Expression{
  public:
    virtual int interpret()=0;     
};
//Number class
class Number:public Expression{
  public:
  int value;
     Number(int v):value(v){};
     int interpret(){
       return value;
     }
};
//Add Expression
class AddExpression:public Expression{
  public:
     Expression*left;
     Expression*right;
     
     AddExpression(Expression*l,Expression*r): left(l),right(r) {};
     
     int interpret(){
       return left->interpret()+right->interpret();
     }
};
int main() 
{
     Number a(3);
     Number b(4);
     AddExpression e(&a,&b);
     cout<<e.interpret();
     
    return 0;
}