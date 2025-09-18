#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        // 按起点排序
        sort(coins.begin(), coins.end(), [](auto &a, auto &b){ return a[0] < b[0]; });
        long long result = 0, sum = 0;
        int l = 0;
        int n = coins.size();

        // 正序滑窗：右端对齐
        for (int r = 0; r < n; ++r) {
            sum += 1LL * (coins[r][1] - coins[r][0] + 1) * coins[r][2];
            int left = coins[r][1] - k + 1;
            while (coins[l][1] < left) {
                sum -= 1LL * (coins[l][1] - coins[l][0] + 1) * coins[l][2];
                ++l;
            }
            long long uncover = max(0LL, 1LL * (left - coins[l][0]) * coins[l][2]);
            result = max(result, sum - uncover);
        }

        // 倒序滑窗：左端对齐
        sum = 0;
        int r = n - 1;
        for (int l = n - 1; l >= 0; --l) {
            sum += 1LL * (coins[l][1] - coins[l][0] + 1) * coins[l][2];
            int right = coins[l][0] + k - 1;
            while (coins[r][0] > right) {
                sum -= 1LL * (coins[r][1] - coins[r][0] + 1) * coins[r][2];
                --r;
            }
            long long uncover = max(0LL, 1LL * (coins[r][1] - right) * coins[r][2]);
            result = max(result, sum - uncover);
        }

        return result;
    }
};
