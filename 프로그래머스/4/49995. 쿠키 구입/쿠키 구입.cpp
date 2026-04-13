#include <string>
#include <vector>

using namespace std;

int solution(vector<int> cookie) {
    int answer = -1;
    int cookieN = cookie.size();
    
    for(int m=0; m<cookieN-1; m++){
        //m이 정해지고 나서, 좌우를 하나씩 이동해가면서 같을 때마다 체크
        int l = m; int r = m+1;
        int sumL = cookie[l];
        int sumR = cookie[r];
        //l,r을 한칸씩 밀면서 체크
        while(l>=0 && r<cookieN){
            if(sumL<sumR){
                //sumL이 더 작으니, l을 한칸 줄여서 sumL을 늘려야겠다
                l--;
                if(l>=0) sumL+=cookie[l];//일단 줄여놓고, 되는 놈이면 더해줘, while문에서 알아서 걸리겠지 ㅇㅇ;
            }
            else if(sumL>sumR){
                //sumR이 더 작으니, r을 한칸 늘려서 sumR을 늘린다.
                r++;
                if(r<cookieN) sumR+=cookie[r];
            }
            else{
                //같으면
                answer = max(answer, sumL);
                //이러고 아무거나 하나 간격을 넓혀
                r++;
                if(r<cookieN) sumR+=cookie[r];
                //l--;
            }
        }
    }
    if(answer!=-1) return answer;
    else return 0;
}