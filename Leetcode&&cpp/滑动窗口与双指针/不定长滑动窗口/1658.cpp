#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int target=reduce(nums.begin(),nums.end())-x;//求和-x

        if(target<0){
            return -1;
        }
        int result=-1,left=0,sum=0,n=nums.size();
        for(int right=0;right<n;right++){
            sum+=nums[right];
            while(sum>target){
                sum-=nums[left];
                left++;
            }
            if(sum==target){
                result=max(result,right-left+1);
            }
        }
        return result<0?-1:n-result;
    }
};