#include <vector>
#include <climits>
using namespace std;
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int result = INT_MAX, l = 0, s = 0;
        for (int r = 0; r < nums.size(); r++) {
            s += nums[r];
            while (s >= target) {
                result = min(result, r - l + 1);
                s -= nums[l];
                l++;
            }
        }
        return (result == INT_MAX) ? 0 : result;
    }
};
