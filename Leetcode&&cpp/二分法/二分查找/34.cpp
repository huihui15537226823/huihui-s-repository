class Solution {
public:
    int lower_bound(vector<int>& nums,int target){
        int left=-1,right=nums.size();
        while(left+1<right){
            int mid=left+(right-left)/2;
            if(nums[mid]>=target){
                right=mid;
            }else{
                left=mid;
            }
        }
        return right;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int start=lower_bound(nums,target);
        if(start==nums.size()||nums[start]!=target){
            return {-1,-1};

        }
        int end=lower_bound(nums,target+1)-1;
        return{start,end};
    }
};