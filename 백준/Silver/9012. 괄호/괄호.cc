#include <bits/stdc++.h>
using namespace std;

int N;

int main(){
    ios::sync_with_stdio(false);
	cin.tie(0);

    cin>>N;

    for(int i=0;i<N;i++){
        stack<char> s;
        string str;

        cin>>str;
        for(int i=0;i<str.length();i++){
            if(str[i]=='(') s.push(str[i]);
            else if(s.empty() && str[i]==')'){
                s.push(')');//비어있지 않게 하고 break
                break;
            }
            else if(str[i]==')' && s.top()=='(') s.pop();
            
        }
        if(s.empty()) cout<<"YES\n";
        else cout<<"NO\n";
    }
    
}