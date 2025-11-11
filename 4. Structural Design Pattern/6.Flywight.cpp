/*
client--> TreeFactory (map<string,TreeType*>) (getTreeType())
              ||
          TreeTypes (name)(draw(x,y))
 
*/
#include <bits/stdc++.h>
using namespace std;
class TreeType{
  public:
    string name;
      TreeType(string n){
        name=n;
      }
      void draw(int x,int y){
        cout<<"Drawing a tree type: "<<name << "of values "<<x<<" "<<y<<endl;
      }
};
class TreeFactory{
  public:
      unordered_map<string,TreeType*>m;
      
      TreeType* getTreeType(string name){
          if(m.find(name)==m.end()){
            m[name]=new TreeType(name);
          }
          return m[name];
      }
};
int main() 
{
    TreeFactory factory;
    
    int x1=10,y1=20;
    
    TreeType*pine=factory.getTreeType("pine");
    TreeType*oak=factory.getTreeType("oak");
    
    pine->draw(x1,y1);
    oak->draw(x1,y1);
  
}

