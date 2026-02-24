#include <bits/stdc++.h>

using namespace std;

int n,m,k;
struct sticker{
    int r;
    int c;
    int shape[11][11];
};

vector<sticker> stickers;
int field[41][41];

void input(){
    cin>>n>>m>>k;

    for(int i=1;i<=k;i++){
        //int shape[11][11];
        int r,c;
        cin>>r>>c;

        sticker s;
        s.r = r;
        s.c = c;

        for(int a=1;a<=r;a++){
            for(int b=1;b<=c;b++){
                int num;
                cin>>num;
                s.shape[a][b] = num;
            }
        }

        stickers.push_back(s);

        //왜 s.shape = shape가 안될까...
    }
}

void rotateSticker(int ind){
    sticker temp;
    temp.r = stickers[ind].c;
    temp.c = stickers[ind].r;

    for(int i=1;i<=stickers[ind].r;i++){
        for(int j=1;j<=stickers[ind].c;j++){
            temp.shape[j][stickers[ind].r+1-i] = stickers[ind].shape[i][j];
        }
    }

    stickers[ind] = temp;
}

bool isFit(int ind){
    //시작점을 기준으로 다 확인해봐 그냥
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            //field의 i,j를 좌측 상단으로 하였을 때 들어맞는지!
            bool check = true;
            int r = stickers[ind].r; int c = stickers[ind].c;
            //cout<<ind+1<<"번 스티커를 "<<i<<","<<j<<"에 붙여보려합니다\n";
            for(int a = 1;a<=r;a++){
                for(int b=1; b<=c; b++){
                    if(stickers[ind].shape[a][b]==1){
                        if(i+a-1>=1 && i+a-1<=n && j+b-1>=1 && j+b-1<=m){
                            if(field[i+a-1][j+b-1]!=0){
                                //이러면 스티커는 존재하는데, 못놓는 거지
                                check = false;
                                break;
                            }
                        }
                        else{
                            //해당 i,j에서는 스티커를 놓을만큼의 공간이 애초에 없는거니까
                            check = false;
                            break;
                        }
                    }
                }
                if(check==false) break;
            }
            if(check==true){
                //해당 i,j를 시작으로 하여 ind인 스티커를 넣을 수 있는거야
                for(int a = 1; a<=r;a++){
                    for(int b=1; b<=c; b++){
                        if(stickers[ind].shape[a][b]==1){
                            field[i+a-1][j+b-1] = 1;
                        }
                    }
                }
                return true;
            }

            if(check==false) continue;
        }
    }

    return false;
}

void testPrint(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<field[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void solution(){
    for(int i=0;i<k;i++){
        //s가 스티커
        //cout<<i+1<<"번 스티커 붙일 준비\n";
        for(int rotateCnt=1;rotateCnt<=4;rotateCnt++){
            //cout<<"시도\n";
            bool check = isFit(i);
            if(check) break;
            rotateSticker(i);
        }
        //testPrint();
        //isFit에서 true이면 바로 field에 적용하는 식으로
    }

    int ansCnt=0;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(field[i][j]==0) ansCnt++;
        }
    }

    cout<<n*m-ansCnt;
}

int main(){
    // ios::sync_with_stdio(0);
    // cin.tie(0);

    input();
    solution();
}