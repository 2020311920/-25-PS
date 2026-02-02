//비트 연산으로 해결할 건데,
//일단은 어떻게든 풀어보고, 나중에 비트 연산할 때, 2진수로 표현 한 거를 배열처럼 접근해서
//서로다른 비트의 개수를 구하는 방법이 따로 있는지 알아보자 

//일단은 혼자 힘으로 풀기
#include <bits/stdc++.h>

using namespace std;

int n,k,p,x;

// int digital[10][7]={
//     {1,1,1,0,1,1,1},//0
//     {0,0,1,0,0,1,0},//1
//     {1,0,1,1,1,0,1},//2
//     {1,0,1,1,0,1,1},//3
//     {0,1,1,1,0,1,0},//4
//     {1,1,0,1,0,1,1},//5
//     {1,1,0,1,1,1,1},//6
//     {1,0,1,0,0,1,0},//7
//     {1,1,1,1,1,1,1},//8
//     {1,1,1,1,0,1,1}//9
// };
int digital[10]={
    /*0*/ 0b1110111,
    /*1*/ 0b0100100,
    /*2*/ 0b1011101,
    /*3*/ 0b1101101,
    /*4*/ 0b0101110,
    /*5*/ 0b1101011,
    /*6*/ 0b1111011,
    /*7*/ 0b0100101,
    /*8*/ 0b1111111,
    /*9*/ 0b1101111
};

int myPow(int a, int k){
    //a의 k승
    int ans = 1;
    for(int i=1;i<=k;i++){
        ans *= a;
    }
    return ans;
}

int howManyDifferent(int a, int b){
    int cnt=0;
    // for(int i=0;i<7;i++){
    //     if(digital[a][i]!=digital[b][i]) cnt++;
    // }
    int result = digital[a]^digital[b];
    //여기서 어떻게 result를 바탕으로 1인 비트의 개수를 구하지?
    while(result){
        result &= (result-1);
        cnt++;
    }
    return cnt;
}

bool check(int num){
    int sumCnt=0;
    for(int i=1;i<=k;i++){
        int num1 = (num/myPow(10, i-1))%10;
        int num2 = (x/myPow(10, i-1))%10;

        sumCnt += howManyDifferent(num1, num2);
    }
    if(sumCnt<=p){
        //cout<<num<<"\n";
        return true;
    }
    else return false;
}

int ans=0;

void solution(){
    //for(int i=0;i<=9;i++) testPrint(i);
    //총 k칸의 공간에서 p개 만큼을 조작하려 해.
    //현재는 x고
    //n 이하의 수만 허용이 돼

    //나는 시작넘버에서 변환해서 가능한 수를 찾는것이 아닌
    //k칸으로 만들 수 있는 모든 수를 하나하나 보면서 역으로 이게 원래의 x와 p개만큼 다른지를 확인할 것이다.
    //왜? x에서 k칸에 총 p개를 전환하는 게 더 힘들것같아서 

    for(int i=1;i<=n;i++){
        //i라는 수로 바꿀 때 총 몇개의 전환이 필요한가?!
        //그렇기에 일단 i라는 수는 k개의 칸으로 어떻게 나누어지며 이는 원래의 x랑 어떻게 다른지를 구하는 함수
        if(i==x) continue;
        if(check(i)) ans++;
    }

    cout<<ans;
}

void input(){
    cin>>n>>k>>p>>x;
}

int main(){
    input();
    solution();
}