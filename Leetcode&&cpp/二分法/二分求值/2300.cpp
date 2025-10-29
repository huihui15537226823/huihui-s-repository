#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        ranges::sort(potions);
        vector<int> result;
        for(auto& x:spells){
            result.emplace_back(potions.end()-ranges::lower_bound(potions,success*1.0/x));
        }
        return result;
    }
};