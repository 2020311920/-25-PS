//대박이다 이 풀이...

#include <bits/stdc++.h>
using namespace std;

struct Coin { int price, num; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int tc = 0; tc < 3; tc++) {
        int n; 
        cin >> n;
        vector<Coin> coins(n);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> coins[i].price >> coins[i].num;
            sum += coins[i].price * coins[i].num;
        }

        if (sum % 2) {
            cout << 0 << "\n";
            continue;
        }
        int target = sum / 2;

        vector<int> dp(target + 1, -1);
        dp[0] = 0; // 0원은 만들 수 있고, "현재 코인 남은 개수" 의미는 이후에 세팅됨

        for (auto &c : coins) {
            for (int j = 0; j <= target; j++) {
                if (dp[j] >= 0) dp[j] = c.num;               // 이전 코인들로 j 가능 -> 이번 코인 num개로 리셋
                else if (j >= c.price && dp[j - c.price] > 0) // j-price가 가능했고 이번 코인 남아있으면
                    dp[j] = dp[j - c.price] - 1;
            }
        }

        cout << (dp[target] >= 0 ? 1 : 0) << "\n";
    }
}
