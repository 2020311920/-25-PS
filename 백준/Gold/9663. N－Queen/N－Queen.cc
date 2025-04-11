#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int N; 
int cnt=0;
int visitY[16]={0,};
int visitR[30]={0,};
int visitL[30]={0,}; 

//x번째 줄에 x번째 퀸을 놓겠다. 
void backtrack(int x){
	if(x==N+1){
		cnt++;
		return;
	}
	
	else{
		for(int i=0;i<N;i++){
			//이미 세로 x번째라고 선택한 뒤야. 우리는 가로라인을 골라야 해.
			if(visitY[i]==0&&visitR[x+i]==0 && visitL[N-x+i]==0){
				//해당 가로라인에 퀸이 없으면 일단 ㅇㅋ
				//이번엔 대각선에 있냐 없냐의 싸움인데. 저 VisitR,L좌표 생각하는게 헬이네...;;
				
				//다 비었다면, 저것들 다 1로 바꿔주고
				visitY[i]=1;
				visitR[x+i]=1;
				visitL[N-x+i]=1;
				
				backtrack(x+1);
				
				visitY[i]=0;
				visitR[x+i]=0;
				visitL[N-x+i]=0;
			} 
			
		}
	}
	
	
}

int main(){
	cin>>N;
	backtrack(1);
	
	cout<<cnt;
}