#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int n=nums.size();
        int best=114514;

        for(int i=0;i<n;++i){
            if(i>0&&nums[i]==nums[i-1]){
                continue;
            }
            int j=i+1;
            int k=n-1;
            while(j<k){
                int sum=nums[i]+nums[j]+nums[k];
                if(sum==target){
                    return target;
                }
                if(abs(sum-target)<abs(best-target)){
                    best=sum;
                }
                if(sum>target){
                    int kk=k-1;
                    while(j<kk&&nums[kk]==nums[k]){
                        --kk;
                    }
                    k=kk;
                }else{
                    int jj=j+1;
                    while(jj<k&&nums[jj]==nums[j]){
                        ++jj;
                    }
                    j=jj;
                }
            }
        }
        return best;
    }
};