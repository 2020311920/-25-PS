import java.util.*;

public class Main {
    
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        // 3x + 5y = N이니 y를 기준으로
        
        for(int i = N/5;i>=0;i--){
            if((N - i*5)%3==0){
                System.out.print(i+(N-i*5)/3);
                return;
            }
        }
        System.out.print(-1);
    }
}