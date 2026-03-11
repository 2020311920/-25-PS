#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N,m,M,T,R;
    cin>>N>>m>>M>>T>>R;
    int lowLimit = m;
    if(lowLimit+T>M){
        //처음부터 이래버리면 못함
        cout<<-1;
        return 0;
    }
    int time = 0;
    while(1){
        if(N==0) break;
        time++;
        if(m+T<=M){
            N--;
            m+=T;
        }
        else if(m+T>M){
            //이럼 운동 못해. 휴식
            m -= R;
            if(m<=lowLimit) m = lowLimit;
        }
    }

    cout<<time;
}