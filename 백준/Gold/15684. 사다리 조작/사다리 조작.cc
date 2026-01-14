#include <bits/stdc++.h>

using namespace std;

int n,m,h;

int arr[31][11]; //1<=H<=30 H개의 row, 2<=N<=10 N개의 col
//arr[i][j]=1이다? 는 곧 i번째 위치에서 j->j+1로의 통로가 존재한다.
//근데 그럼 i, j+1에게도 역으로 가는 길이 있다 알려줘야지.
//arr[i][j+1] = -1이라고 하자.

int minSum=4;

int travel(int startCol){
    //arr의 1, startCol부터 해서 h, 몇으로 떨어지는 지
    int row = 1;
    while(row<=h){
        if(arr[row][startCol]==1){
            startCol++;
        }
        else if(arr[row][startCol]==-1){
            startCol--;
        }
        row++;
    }

    return startCol;
    
}


void dfs(int k, int x, int y){

    if(k>3 || minSum==0){
        return;
    }

    int check= true;
    for(int i=1;i<=n;i++){
        if(i!=travel(i)) check=false;
    }

    if(check){
        // cout<<"성공 케이스!! "<<k<<"개를 선택하였구용\n";

        // for(int i=1;i<=h;i++){
        //     for(int j=1;j<=n;j++){
        //         cout<<arr[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }

        if(k<minSum){
            minSum=k;
        }

        return;
    }
    else{
        if(k==minSum-1) return;
    }

    
    for(int i=x;i<=h;i++){
        for(int j=y;j<=n-1;j++){
            if(arr[i][j]==0 && arr[i][j+1]==0){
                //여기 선 추가 가능하다
                arr[i][j]=1;
                arr[i][j+1]=-1;

                dfs(k+1, i,j);

                arr[i][j]=0;
                arr[i][j+1]=0;
            }
        }
        y=1;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>h;

    for(int i=1;i<=m;i++){
        int a, b;
        cin>>a>>b;

        arr[a][b] = 1;
        arr[a][b+1] = -1;
    }

    // for(int i=1;i<=n;i++){
    //     cout<<i<<"번은 ";
        
    //     cout<<travel(i)<<"로 도착\n";
    // }

    /*여기까지는 문제없고, travel함수도 문제 없음 확인
    이제부터는 가로선을 어떻게 추가할 것이냐 입니다.
    뭐.. dfs로 여러번 추가해보면서
    추가할 때마다 travel 다 조져서 조건이 맞는지, 그리고 추가한게 3개가 넘는지 */

    // cout<<"기초 상태\n";

    // for(int i=1;i<=h;i++){
    //     for(int j=1;j<=n;j++){
    //         cout<<arr[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }

    dfs(0,1,1);

    if(minSum>3) cout<<-1;
    else cout<<minSum;


}