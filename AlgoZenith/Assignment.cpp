#include <bits/stdc++.h>
using namespace std;

void solve(){
  string s;
  cin>>s;
  
  int m=s.size();
  int cnt=0;
  if(m>10){
     cout<<s[0];
     int cnt=0;
     for(int i=1;i<s.size()-1;i++){
         cnt++;
     }
     cout<<cnt;
     cout<<s[s.size()]<<endl;
     return;
  }

  cout<<s<<endl;

}

signed main(){
    //Fast Io
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int t;
    cin>>t;
    while(t--){
        solve();
    }
}