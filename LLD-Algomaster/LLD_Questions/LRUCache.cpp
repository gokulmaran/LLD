#include <bits/stdc++.h>
using namespace std;

/*
Design a LRU Cache

LRU Cache-->LRU Cache need to be designed with doubly LL and hashmap ,where using get and put methos

main -->call get and put method
*/
class LRUCache{
  public:
     class Node{
       public:
         int key;
         int val;
         Node*prev;
         Node*next;
         
         Node(int data,int v){
           key=data;
           val=v;
         }
     };
     
     Node*head=new Node(-1,-1);
     Node*tail=new Node(-1,-1);
     
     int cap;
     unordered_map<int,Node*>m;
     LRUCache(int capacity){
       cap=capacity;
       head->next=tail;
       tail->prev=head;
     }
     
     int get(int key){
       if(m.find(key)!=m.end()){
          Node*res=m[key];
          int ans=res->val;
          
          m.erase(key);
          deleteNode(res);
          addNode(res);
          
          m[key]=head->next;
          return ans;
       }
       return -1;
     }
     void put(int key,int val){
       if(m.find(key)!=m.end()){
         Node*curr=m[key];
         m.erase(key);
         deleteNode(curr);
       }
       
       if(m.size()==cap){
         m.erase(tail->prev->key);
         deleteNode(tail->prev);
       }
       addNode(new Node(key,val));
       m[key]=head->next;
     }
  private:
     void addNode(Node*newNode){
       Node*temp=head->next;
       
       newNode->next=temp;
       newNode->prev=head;
       
       head->next=newNode;
       temp->prev=newNode;
     }
     void deleteNode(Node*node){
       Node*prevv=node->prev;
       Node*nextt=node->next;
       
       prevv->next=nextt;
       nextt->prev=prevv;
     }
};
int main() 
{
    LRUCache*lru=new LRUCache(2);
    lru->put(1,1);
    lru->put(1,2);
    
    cout<<lru->get(1)<<endl;
    return 0;
}