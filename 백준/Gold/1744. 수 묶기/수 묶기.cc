#include <bits/stdc++.h>

using namespace std;
//1744BOJ


int main() {
    int T;
    cin>>T;
    //구분할 게, 음수, 0, 1, 양수이다.
    //음수는 음수끼리 묶는다, 양수도 양수끼리 묶는다
    //음수가 홀수개라면 하나는 0과 묶는다.
    //1은 절대 묶지 않는다.
    vector<int> one;
    vector<int> minus;
    vector<int> zero;
    vector<int> plus;
    
    for(int i=0;i<T;i++){
        int num;
        cin>>num;
        if(num==1) one.push_back(num);
        else if(num==0) zero.push_back(num);
        else if(num<0) minus.push_back(num);
        else plus.push_back(num);
    }
    
    sort(minus.begin(), minus.end());
    sort(plus.begin(), plus.end());
    
    //cout<<plus.size();
    
    int sum=0;
    
    if(minus.size()%2==0){
        for(int i=0;i<minus.size();i+=2) sum+=minus.at(i)*minus.at(i+1);
    }
    else{
        if(minus.size()>=3) for(int i=0;i<minus.size()-1;i+=2) sum+=minus.at(i)*minus.at(i+1);
        if(zero.size()==0){//0이 없다면
            sum+=minus.at(minus.size()-1);
        }
        //0이 있었다면 안 더해도 됐겠지
    }
    
    if(plus.size()%2==0) for(int i=plus.size()-1;i>=0;i-=2) sum+=plus.at(i)*plus.at(i-1);
    else{
        for(int i=plus.size()-1;i>=1;i-=2) sum+=plus.at(i)*plus.at(i-1);
        sum+=plus.at(0);
    }
    
    sum+=one.size();
    cout<<sum;
    
}