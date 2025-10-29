class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        auto check=[&](int mx)->bool{
            int cnt=1,s=0;
            for(int x:nums){
                if(s+x<=mx){
                    s+=x;
                    continue;
                }
                if(cnt==k){
                    return false;
                }
                cnt++;
                s=x;
            }
            return true;
        };

        int l=ranges::max(nums)-1;
        int r=reduce(nums.begin(),nums.end());
        while(l+1<r){
            int mid=l+(r-l)/2;
            (check(mid)?r:l)=mid;
        }
        return r;
    }
};