#include <bits/stdc++.h>

using namespace std;

//int findNum(vector<int>& numArr, int target, int start, int end){
int findNum(int* numArr, int target, int start, int end){
    while(start<=end){
        int mid = (start+end)/2;
        if(target<numArr[mid]) end =mid-1;
        else if(target>numArr[mid]) start = mid+1;
        else return 1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    
    //vector<int> numArr;
    int numArr[T];
    for(int i=0;i<T;i++){
        int num;
        cin>>num;
        //numArr.push_back(num);
        numArr[i] = num;
    }
    //sort(numArr.begin(), numArr.end());
    sort(numArr, numArr+T);
    
    int test;
    cin>>test;
    for(int i=0;i<test;i++){
        int temp;
        cin>>temp;
        cout<<findNum(numArr, temp, 0, T-1)<<"\n";
    }
    
    
}