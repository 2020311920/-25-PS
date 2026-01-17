#include <bits/stdc++.h>

using namespace std;

int alphabet[26];
string str;

int maxV=0;
int maxCnt=0;
int duplicate = 0;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>str;

    for(auto i : str){
        int num = char(i) - 'A';
        if(num>26) num-= ('a'-'A');

        alphabet[num]++;

        if(alphabet[num]>maxCnt){
            maxCnt = alphabet[num];
            maxV = num;
            duplicate=0;
        }
        else if(alphabet[num]==maxCnt) duplicate++;
    }

    if(duplicate>0) cout<<"?";
    else cout<<char('A'+maxV);

    
}