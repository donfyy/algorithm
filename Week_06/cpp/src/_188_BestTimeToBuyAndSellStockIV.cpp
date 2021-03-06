#include <vector>
using namespace std;
class Solution
{
public:
    // 需要注意六个点 O(n*min(n, k)) O(min(n, k))
    int maxProfit(int k, vector<int> &prices)
    {
        const int n = prices.size();
        if (!n)
            return 0;
        k = min(k, n >> 1) + 1;
        vector<vector<int>> dp(2, vector<int>(k, INT_MIN >> 1));
        dp[0][0] = 0;
        dp[1][0] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            dp[1][0] = max(dp[1][0], dp[0][0] - prices[i]);
            for (int j = 1; j < k; j++)
            {
                dp[1][j] = max(dp[1][j], dp[0][j] - prices[i]);
                dp[0][j] = max(dp[0][j], dp[1][j - 1] + prices[i]);
            }
        }
        return *max_element(dp[0].begin(), dp[0].end());
    }
};
class Solution2
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        // f(i, k, s) s in {0, 1} 表示第i天结束后已经完成了k笔交易时手中持股状态为s时的最大利润
        // f(i, k, 0) = max(f(i - 1, k, 0), f(i - 1, k - 1, 1) + prices[i])
        // f(i, k, 1) = max(f(i - 1, k, 1), f(i - 1, k, 0) - prices[i])
        // f(0, 0, 0) = 0
        // f(0, 0, 1) = -prices[0]
        // f(0, k, s) k > 0 无效状态 因为求最大值 可以将无效状态初始化为一个较小值
        // 需要注意无效值会减去负值，需要注意负数溢出的情况，初始值不能是整数最小值
        // 交易次数的上限也取决于交易天数
        const int n = prices.size();
        if (!n)
            return 0;
        k = min(k, n >> 1) + 1;
        vector<vector<int>> dp(2, vector<int>(k, INT_MIN >> 1));
        dp[0][0] = 0;
        dp[1][0] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                dp[1][j] = max(dp[1][j], dp[0][j] - prices[i]);
                if (j)
                {
                    dp[0][j] = max(dp[0][j], dp[1][j - 1] + prices[i]);
                }
            }
        }
        return *max_element(dp[0].begin(), dp[0].end());
    }
};