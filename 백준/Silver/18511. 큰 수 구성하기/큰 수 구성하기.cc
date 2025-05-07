#include <iostream>
#include <vector>
using namespace std;
int N, lenK, answer;
vector<int> K;
void recur(int num)
{
    if (N < num) // N보다 큰 경우
    {
        return;
    }
    answer = max(answer, num);

    num *= 10; // 자리 늘리기

    for (int i = 0; i < lenK; ++i)
    {
        recur(num + K[i]);
    }
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> N >> lenK;
    K = vector<int>(lenK);
    for (int &k : K)
    {
        cin >> k;
    }

    recur(0);
    cout << answer;
    return 0;
}