#include <bits/stdc++.h>

using namespace std;

int findSum(string str){
    int sum=0;
    for(auto i : str){
        if(i>=48 && i<=57) sum+=(i-48);
    }
    return sum;
}

bool compare(string str1, string str2){
    if(str1.length()!=str2.length()) return str1.length()<str2.length();
    else if(str1.length()==str2.length() && findSum(str1)!=findSum(str2)) return findSum(str1)<findSum(str2);
    return str1<str2;
}

int main() {
    int T;
    
    cin>>T;
    vector<string> v;
    cin.clear();
    while(T--){
        string str;
        cin>>str;
        //cout<<str<<"\n";
        v.push_back(str);
        cin.clear();
    }
    
    sort(v.begin(), v.end(), compare);
    
    for(auto i : v) cout<<i<<"\n";
    
}

