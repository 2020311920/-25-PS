#include <bits/stdc++.h>

using namespace std;

bool check4(int a, int b, int c, int d){
    if(a==b && b==c && c==d) return true;
    return false;
}

int main() {
    int N,M;
    cin>>N>>M;
    vector<vector<int>> v(N,vector<int>(M,0));
    
    cin.clear();
    
    for(int i=0;i<N;i++){
        string str;
        cin>>str;
        for(int j=0;j<M;j++) v[i][j]=str[j]-'0';
    }
    
    int maxLine = min(N,M);
    int result = 0;
    for(int i=1;i<maxLine;i++){//maxLine이 3이니까 2까지 빠질 수 있게 설정, 그리고 
    //애초에 i=0이면 무조건 만족이니까 ㄴㄴ
        for(int j=0;j<N-i;j++){
            for(int k=0;k<M-i;k++){
                if(check4(v[j][k],v[j+i][k],v[j][k+i],v[j+i][k+i])) result = i;
            }
        }
    }
    
    cout<<(result+1)*(result+1);
}

