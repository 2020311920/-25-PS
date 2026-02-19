#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> v;

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        v.push_back(num);
    }
}

int INTMIN = -2100000000;
int INTMAX = 2100000000;

void solution(){
    int maxCnt=0;
    for(int i=0;i<n;i++){
        //현재 기준 v[i]
        //cout<<"현재 기준 : "<<v[i]<<" 이고 후보는 : \n";
        int tempCnt = 0;
        double tilt=INTMAX;
        for(int j=i-1;j>=0;j--){
            double tempTilt = double(v[i]-v[j])/double(i-j);
            if(tempTilt<tilt){
                //이러면 엇 볼 수 있음
                //cout<<tempTilt<<"의 기울기 "<<j<<"가 후보\n";
                tilt = tempTilt;
                tempCnt++;
            }
        }

        tilt = INTMIN;
        for(int j=i+1;j<n;j++){
            double tempTilt = double(v[i]-v[j])/double(i-j);
            if(tempTilt>tilt){
                //cout<<tempTilt<<"의 기울기 "<<j<<"가 후보\n";
                tilt = tempTilt;
                tempCnt++;
            }
        }

        if(tempCnt>maxCnt) maxCnt=tempCnt;
    }

    cout<<maxCnt;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    input();
    solution();
}