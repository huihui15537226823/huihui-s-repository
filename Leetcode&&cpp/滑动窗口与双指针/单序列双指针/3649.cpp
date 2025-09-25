#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;
class Solution {
public:
    long long perfectPairs(vector<int>& nums) {
        for(int &x:nums){
            x=abs(x);
        }

        sort(nums.begin(),nums.end());

        long long result=0;
        int l=0;
        for(int j=0;j<nums.size();j++){
            int b=nums[j];
            while(nums[l]*2<b){
                l++;
            }
            result+=j-l;
        }
        return result;
    }
};