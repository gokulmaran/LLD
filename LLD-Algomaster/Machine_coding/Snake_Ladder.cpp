#include <bits/stdc++.h>
using namespace std;
/*Snake and ladder (Requirement flow(all-code))
1. Multiple players can play
2. Dice generates random number (1–6)
3. Player moves based on dice roll
4. Snakes move player down, ladders move player up
5. Player must reach exactly last cell (100) to win
6. Game handles turn rotation and declares winner

class Player:
  - string name
  - int position
  + move(int steps)

class Dice:
  + roll()

class Board:
  - int size
  - unordered_map<int,int> snakes
  - unordered_map<int,int> ladders
  + addSnake()
  + addLadder()
  + getFinalPosition()

class Game:
  - queue<Player*>
  - Board
  - Dice
  + setup()
  + startGame()
*/
class Player{
  public:
    string name;
    int position;
    
    Player(string n):name(n),position(0){}
};
class Dice{
   public:
    int roll(){
      return rand()%6+1;
    } 
};
class Board{
  public:
     int size;
     unordered_map<int,int>snakes,ladders;
     
     Board(int s):size(s){}
     
     void addSnakes(int start,int dest){
       snakes[start]=dest;
     }
     void addLadders(int start,int end){
       ladders[start]=end;
     }
     int getPosition(int pos){
       if(snakes.count(pos)){
         return snakes[pos];
       }
       if(ladders.count(pos)){
         return ladders[pos];
       }
       return pos;
     }
};
class Game{
  public:
     Board board;
     queue<Player*>q;
     Dice dice;
     Game(vector<string>players,int boardSize):board(boardSize){
       for(int i=0;i<players.size();i++){
         q.push(new Player(players[i]));
       }
     }
     void setUp(){
       board.addSnakes(90,45);
       board.addLadders(42,85);
     }
     void initialise(){
       while(true){
       auto curr=q.front();
       q.pop();
       
       int move=dice.roll();
       int newPos=curr->position+move;
       
       if(newPos<=board.size){
         int finalPos=board.getPosition(newPos);
         curr->position=finalPos;
       }
       cout<<curr->name << " rolled at "<<curr->position<<endl;
       if(curr->position==board.size){
         cout<<curr->name<<" wins"<<endl;
         break;
       }
       q.push(curr);
     }
    }
};

int main() 
{
   vector<string>names={"A","B"};
   Game g(names,100);
   
   g.setUp();
   g.initialise();
}