#include <vector>
using namespace std;
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(k<=1){
            return 0;
        }

        int result=0,sum=1,l=0;
        for(int r=0;r<nums.size();r++){
            sum*=nums[r];
            while(sum>=k){
                sum/=nums[l];
                l++;
            }
            result+=r-l+1;//加上每一个r时的所有项
        }
        return result;
    }
};