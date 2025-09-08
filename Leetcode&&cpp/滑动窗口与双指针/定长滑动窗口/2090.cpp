
class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int> avgs(n,-1);
        long long sum=0;
        

        for(int i=0;i<n;i++){
            sum+=nums[i];
            if(i<k*2){
                continue;
            }
            avgs[i-k]=sum/(k*2+1);
            sum-=nums[i-k*2];
        }
        return avgs;
    }
};