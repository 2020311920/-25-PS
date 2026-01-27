#include <bits/stdc++.h>

using namespace std;

string s, t;
bool answer = false;

void input(){
    cin>>s>>t;
}

bool compareStrdq(string str, deque<char> dq){
    int length = str.length();
    int size = dq.size();
    if(length==size){
        for(int i=0;i<length;i++){
            if(str[i]!=dq[i]){
                //cout<<str<<"의 "<<i<<"번쨰에 "<<str[i]<<"랑 "<<dq[i]<<"랑 다르기에\n";   
                return false;
            }
        }
        return true;
    }
    else return false;
}

void func(deque<char> dq){
    if(dq.size()<=s.length()) return;
    
    if(dq.back()=='A'){
        auto change = dq;
        change.pop_back();
        if(compareStrdq(s, change)) answer = true;
        else func(change);
    }
    
    if(dq.front()=='B'){
        deque<char> change2;
        //일단 뒤집어
        int length = dq.size();
        for(int i=length-1;i>=0;i--){
            change2.push_back(dq[i]);
        }
        change2.pop_back();
        if(compareStrdq(s, change2)) answer = true;
        else func(change2);
    }

}

void solution(){
    //t에서
    //1. 뒤에 A가 있다면 뺼 수 있따
    //2. 뒤집어서 B가 있다면 뒤집고 B를 뺸다.
    //이렇게 해서 최종 한글자 남을 때까지 돌리면서 s가 나오는지 판단
    deque<char> dq;
    for(auto i : t) dq.push_back(i); 
    func(dq);

    cout<<answer;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}