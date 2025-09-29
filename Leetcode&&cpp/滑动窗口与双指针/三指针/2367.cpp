#include <vector>
#include <unordered_set>
using namespace std;
class Solution {
public:
    int arithmeticTriplets(vector<int> &nums, int diff) {
        int result = 0;
        unordered_set<int> s{nums.begin(), nums.end()};
        for (int x: nums)
            if (s.count(x - diff) && s.count(x + diff))
                ++result;
        return result;
    }
};