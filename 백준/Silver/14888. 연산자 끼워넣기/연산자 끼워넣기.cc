#include <bits/stdc++.h>

using namespace std;

int n;
int numbers[101];
int oper[5]; //1 +, 2 - , 3 *, 4 /

int oper_blank[101];
int ans_max=-1000000001;
int ans_min=1000000001;

int calc(){
    int ans = numbers[1];

    for(int i=1;i<=n-1;i++){
        switch(oper_blank[i]){
            case 1:
                ans += numbers[i+1];
                break;
            case 2:
                ans -= numbers[i+1];
                break;
            case 3:
                ans *= numbers[i+1];
                break;
            case 4:
                ans /= numbers[i+1];
                break;
        }
        //이렇게 기호에 따라 계산...
    }


    return ans;
}

void f(int k){
    //이 함수는 n번째 기호칸에 어떤 것을 넣느냐로 돌리는 백트래킹 함수
    //그래서 n번째 기호칸에 oper[1~4]를 넣을 수 있음 차례대로 넣는거임ㅇㅇ
    if(k==n){
        //기호를 전부 넣었단 소리, 그럼 계산을 하고 그걸 max, min이랑 비교해서 넣음 됨

        //식 출력 - 디버그용
        // cout<<numbers[1];
        // for(int i=1;i<=n-1;i++){
        //     switch(oper_blank[i]){
        //         case 1:
        //             cout<<"+";
        //             break;
        //         case 2:
        //             cout<<"-";
        //             break;
        //         case 3:
        //             cout<<"*";
        //             break;
        //         case 4:
        //             cout<<"/";
        //             break;
        //     }
        //     cout<<numbers[i+1];
        // }
        // cout<<"\n";
        int temp = calc();

        if(temp > ans_max) ans_max = temp;
        if(temp <ans_min) ans_min = temp;

        return;
    }

    int i=1;
    while(i<=4){
        if(oper[i]>0){
            //oper[i]를 k번째 기호칸(=oper_blank[k])에 넣을 수 있습니다.
            oper_blank[k] = i;
            //넣었으니까, oper[i]를 하나 줄여야지
            oper[i]--;
            f(k+1);
            oper[i]++; //원상복구
        }
        i++;
    }

}

int main(){
    /*생각의 흐름
    사실 상 중요한 것은 기호들을 어떻게 배치할 것이냐.
    그래서 그냥 무식하게 모든 경우 다 해버릴거다. 왜? 해봤자 10개의 기호인데,
    10! 해봤자 한참 작음
    
    근데 이제 어떻게 배치할건데? 어떻게 코드로 변환하는데? 몇개인줄 알고 이게 
    다중 for문으로 해결될 게 아니거덩요
    
    그래서 이럴 땐 역시 백트래킹 아니겠습니꽈
    */

    cin>>n;

    for(int i=1;i<=n;i++) cin>>numbers[i];
    for(int i=1;i<=4;i++) cin>>oper[i];


    f(1);

    cout<<ans_max<<"\n"<<ans_min;
}