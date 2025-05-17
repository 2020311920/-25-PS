#include <bits/stdc++.h>

using namespace std;

int n;
int cnt=1;
vector<char> v;

int main(){
    //ios::sync_with_stdio(0);
    //cin.tie(0);

    cin>>n;
    stack<int> s;
    s.push(0);
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;

        while(num!=s.top() && cnt<=n){
            s.push(cnt);
            //cout<<cnt<<"를 푸쉬함\n";
            cnt++;
            v.push_back('+');
        }
        
        if(cnt>n+1){
            break;
        }
        if(num==s.top()){
            //cout<<s.top()<<"이랑 "<<num<<"이 같아서 pop\n";
            s.pop();
            v.push_back('-');
        }
        else{
            break;
        }

    }

    if(s.top()==0){
        for(auto i : v) cout<<i<<"\n";
    }
    else cout<<"NO";
}