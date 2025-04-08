#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long N, M;
long long num_arr[10001]={0,};
long long sum_arr[10001]={0,};
int cnt = 0;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>N>>M;
    int sum = 0;
	int num;
	    
    for(int i=1;i<=N;i++){
    	cin>>num;
    	num_arr[i] = num;
    	sum+=num;
    	sum_arr[i] = sum;
	}
	
	/*아, 이거지
	다른 배열 하나에다가, 이전까지의 합을 넣어주는 배열을 넣자*/
	
	/*이제, i에서 l까지의 합은 sum_arr[l]-sum_arr[i]*/
	for(int i=0, l=1;i<=l && l<=N;){
		int result = sum_arr[l]-sum_arr[i];
		if(result == M){
			cnt++;
			l++;
		}
		else if(result>M) i++;
		else l++;
		
	}
	
	cout<<cnt;
    
}