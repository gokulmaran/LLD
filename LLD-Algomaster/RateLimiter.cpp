#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
/*
Design Rate Limiter

Rate limiter-Implement sliding window algorithm
main-- call the algorithm
*/
class RateLimiter{
  public:
    int windowSizeInSec;
    int maxReq;
   unordered_map<string, deque<long long>> m;
    
    long long getCurrentTime(){
      return duration_cast<seconds>(
            steady_clock::now().time_since_epoch()
        ).count();
    }
    
    RateLimiter(int maxReq,int windowInSec): maxReq(maxReq),windowSizeInSec(windowInSec) {}
    bool allowRequest(string userId){
      long long currentTime=getCurrentTime();
      long long windowStart= currentTime-windowSizeInSec;
      
      deque<long long>& timestamps = m[userId];

        // Remove expired timestamps
        while (!timestamps.empty() && timestamps.front() <= windowStart) {
            timestamps.pop_front();
        }
      
      if(timestamps.size()<maxReq){
        timestamps.push_back(currentTime);
        return true;
      }
      return false;
    }
};
int main() 
{
    RateLimiter limiter(3,10);
    
    string user="gokul";
    for(int i=0;i<5;i++){
      if(limiter.allowRequest(user)){
        cout<<i<<" Request allowed"<<endl;
      }
      else{
        cout<<i<<" Rate limit exceeded"<<endl;
      }
    }
}