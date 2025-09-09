#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long result=0;
        long long sum=0;
        unordered_map<int,int> cnt;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            cnt[nums[i]]++;
            int left=i-k+1;
            if(left<0){
                continue;
            }
            if(cnt.size()==k){
                result=max(result,sum);
            }

            int j=nums[left];
            sum-=j;
            if(--cnt[j]==0){
                cnt.erase(j);
            }
        }
        return result;
    }
};