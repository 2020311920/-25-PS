#include <bits/stdc++.h>

using namespace std;

int n;
string s;
int cnt=1;

void isPalindrome(int l, int r){
    if(l>=r){
        cout<<1<<" "<<cnt<<"\n";
        cnt=1;
        return;
    }
    else if(s[l]!=s[r]){
        cout<<0<<" "<<cnt<<"\n";
        cnt=1;
        return;
    }
    else{
        cnt++;
        isPalindrome(l+1, r-1);
    }
}

int main(){
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>s;

        isPalindrome(0, s.length()-1);
    }
}