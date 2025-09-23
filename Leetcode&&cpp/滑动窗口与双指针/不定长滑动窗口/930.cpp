#include <vector>
using namespace std;
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        auto f = [&](int k) -> int {
            int left = 0, sum = 0, re = 0;
            for (int i = 0; i < nums.size(); i++) {
                sum += nums[i];
                while (left <= i && sum >= k) sum -= nums[left++];
                re += left;
            }
            return re;
        };
        return f(goal) - f(goal + 1);
    }
};