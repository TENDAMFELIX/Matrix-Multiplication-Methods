#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> Dimensions = {5, 4, 6, 2, 7};
    int N = Dimensions.size();
    vector<vector<int>> Dp(N, vector<int>(N, 0));
    for (int i = 1; i < N; i++)
        Dp[i][i] = 0;
    for (int L = 2; L < N; L++)
    {
        for (int i = 1; i < N - L + 1; i++)
        {
            int j = i + L - 1;
            Dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
                Dp[i][j] = min(Dp[i][j], Dp[i][k] + Dp[k + 1][j] + Dimensions[i - 1] * Dimensions[k] * Dimensions[j]);
        }
    }
    cout << Dp[1].back() << endl;
}