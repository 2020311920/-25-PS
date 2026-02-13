#include <bits/stdc++.h>

using namespace std;

int n, m, l, k;

struct star{
    int x;
    int y;
};
vector<star> stars;

vector<int> xs;
vector<int> ys;

void solution(){
    //x좌표들만 모으고, y좌표들만 모아서, 경계를 k^2개로 구해. 그다음 만든 경계로 k개의 별을 체크
    //이런 전략은 k개가 적을 때 가능한데, k개도 많으면 어떡하지?
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());

    //이제 꼭지점을 하나씩 정하면서 그 경우 포함되는 별의 개수를 체크하자
    int maxCnt=0;
    for(auto i : xs){
        for(auto j : ys){
            //i,j를 시작으로 l만큼씩의 경계가 생김
            int cnt=0;
            for(auto s : stars){
                if(s.x>=i && s.x<=i+l && s.y>=j && s.y<=j+l){
                    cnt++;
                }
            }

            if(cnt>maxCnt) maxCnt=cnt;
        }
    }

    cout<<k-maxCnt;
}

void input(){
    cin>>n>>m>>l>>k;

    for(int i=1;i<=k;i++){
        int x, y;
        cin>>x>>y;

        stars.push_back(star{x,y});
        xs.push_back(x);
        ys.push_back(y);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}