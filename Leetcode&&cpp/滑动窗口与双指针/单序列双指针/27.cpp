#include <vector>
using namespace std;
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int stack_size = 0;
        for (int x : nums) {
            if (x != val) {
                nums[stack_size++] = x; // 把 x 入栈
            }
        }
        return stack_size;
    }
};