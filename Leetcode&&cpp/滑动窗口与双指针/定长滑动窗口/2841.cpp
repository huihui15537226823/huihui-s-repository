class Solution {
public:
    long long maxSum(vector<int>& nums, int m, int k) {
        long long ans = 0, s = 0;
        unordered_map<int, int> cnt;
        for (int i = 0; i < nums.size(); i++) {
            // 1. 进入窗口
            s += nums[i];
            cnt[nums[i]]++;

            int left = i - k + 1;
            if (left < 0) { // 窗口大小不足 k
                continue;
            }

            // 2. 更新答案
            if (cnt.size() >= m) {
                ans = max(ans, s);
            }

            // 3. 离开窗口
            int out = nums[left];
            s -= out;
            if (--cnt[out] == 0) {
                cnt.erase(out);
            }
        }

        return ans;
    }
};