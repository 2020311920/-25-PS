#include <bits/stdc++.h>
#include <string>
#include <vector>

int arr[101][101];
int targetRow, targetCol;

using namespace std;

int solution(int n, int w, int num) {
    int answer = 1;
    int cnt=1;
    int floor = n%w==0 ? n/w : n/w + 1;
    
    for(int i=1;i<=floor && cnt<=n;i++){
        if(i%2!=0){
            //층이 홀수이면
            for(int j=1;j<=w && cnt<=n;j++){
                arr[i][j] = cnt;
                if(cnt==num){
                    targetRow = i;
                    targetCol = j;
                }
                cnt++;
            }
        }
        else{
            for(int j=w;j>=1 && cnt<=n;j--){
                arr[i][j] = cnt;
                if(cnt==num){
                    targetRow = i;
                    targetCol = j;
                }
                cnt++;
            }
        }
        
    }
    
    for(int i=floor;i>=targetRow;i--){
        if(arr[i][targetCol]==0) continue; //이걸 놓쳐서 계속 틀렸네 아
        else if(arr[i][targetCol]==num) break;
        else answer++;
    }
    return answer;
}