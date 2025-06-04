#include <bits/stdc++.h>

using namespace std;

//입력받는 정수는 -4000 ~ 4000이니까
int forFreq[8002];
vector<int> forMiddle;
double sum=0;
int n;


int main(){
    cin>>n;

    for(int i=1;i<=n;i++){
        int num;
        cin>>num;

        sum+=num;
        forFreq[num+4000]++;
        forMiddle.push_back(num);
    }

    double avg = sum/n;

    sort(forMiddle.begin(), forMiddle.end());
    int middleV = forMiddle[n/2];

    int maxV=-1;
    vector<int> freqList;
    for(int i=0;i<=8001;i++){
        if(forFreq[i]>maxV){
            freqList.clear();
            freqList.push_back(i-4000);
            maxV = forFreq[i];
        }
        else if(forFreq[i]==maxV) freqList.push_back(i-4000);
    }

    int freqV;
    if(freqList.size()==1) freqV = freqList[0];
    else{
        sort(freqList.begin(), freqList.end());
        freqV = freqList[1];
    } 
    
    cout<<floor(avg+0.5)<<"\n"<<middleV<<"\n"<<freqV<<"\n"<<forMiddle[n-1]-forMiddle[0];
}