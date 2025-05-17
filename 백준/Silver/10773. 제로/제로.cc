#include <bits/stdc++.h>
using namespace std;

stack<int> s;
int result=0;

int main(){
    ios::sync_with_stdio(false);
	cin.tie(0);

    int N;
    cin >>N;

    for(int i=0;i<N;i++){
        int num;
        cin>>num;
        if(num==0){
            result -= s.top();
            s.pop();
        }
        else{
            s.push(num);
            result+=num;
        }
    }

    cout<<result<<"\n";
}