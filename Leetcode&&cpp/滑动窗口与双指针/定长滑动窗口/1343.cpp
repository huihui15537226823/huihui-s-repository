class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int result=0;
        int sum=0;
        for(int i=0;i<arr.size();i++){
            sum+=arr[i];
            if(i<k-1){
                continue;
            }
            int a=(sum>=k*threshold);
            result+=a;

            sum-=arr[i-k+1];
        }
        return result;
    }
};