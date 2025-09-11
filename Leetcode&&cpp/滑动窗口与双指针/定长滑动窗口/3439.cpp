class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        int n=startTime.size();
        vector<int> free(n+1);
        free[0]=startTime[0];
        for(int i=1;i<n;i++){
            free[i]=startTime[i]-endTime[i-1];
        }
        free[n]=eventTime-endTime[n-1];

        int result=0;
        int sum=0;
        for(int i=0;i<=n;i++){
            sum+=free[i];
            if(i<k){
                continue;
            }
            result=max(result,sum);
            sum-=free[i-k];
        }
        return result;
    }
};