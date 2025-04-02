import java.util.*;

public class Main {
    
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        
        /*
        순간 떠오른건 당연히 무식한 방법인 브루트포스인데
        시간제한이 2초가 아닌 1초인걸 보면 분명 그렇게 풀게될 시 
        걸리는 듯 하다.
        심지어 N장 중에 3장이면 무려 3중 for문이 나오게 되므로 상당히 
        무섭다....
        */
        
        int N = sc.nextInt(), target = sc.nextInt();
        int[] cardArr = new int[N];
        for(int i=0;i<N;i++){
            cardArr[i] = sc.nextInt();
        }
        /*
        좋아 일단, 카드를 다 담았다. 여기서 3장을 골라 target에 가장 가깝게 하라.....
        솔직히 떠오르지 않기에 일단 무식하게 해보자///
        ///
        이게 되네...?
        다른 더 말끔한 방법은 없을까...? 다른 문제들 다 풀고 고민해보자.
        */
        
        //브루트포스
        int Max = 0, result=0;
        for(int i=0;i<N;i++){
            for(int j=i+1;j<N;j++){
                for(int k = j+1;k<N;k++){
                    int tempResult = cardArr[i]+cardArr[j]+cardArr[k];
                    if(tempResult<=target && tempResult>Max){
                        result = tempResult;
                        Max = tempResult;
                    }
                }
            }
        }
        
        
        System.out.print(result);
    }
    
}