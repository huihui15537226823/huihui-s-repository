class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        auto check=[&](long long x)->bool{
            long long sum=0;
            for(int t:time){
                sum+=x/t;
                if(sum>=totalTrips){
                    return true;
                }
            }
            return false;
        };

        int min_t=ranges::min(time);
        long long l=min_t-1;
        long long r=1LL *min_t*totalTrips;
        while(l+1<r){
            long long mid=l+(r-l)/2;
            (check(mid)?r:l)=mid;

        }
        return r;
    }
};