#include <bits/stdc++.h>

using namespace std;

int n;
string word;
vector<string> v;

bool mycompare(string str1, string str2){
    if(str1.length()==str2.length()) return str1<str2;
    else return str1.length()<str2.length();
}

int main(){
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>word;

        v.push_back(word);
    }

    sort(v.begin(), v.end(), mycompare);

    cout<<v[0]<<"\n";

    for(int i=1;i<n;i++){
        if(v[i].compare(v[i-1])!=0) cout<<v[i]<<"\n";
    }
}