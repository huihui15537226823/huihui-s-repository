class Solution {
public:
    long long mod=1e9+7;
    bool check(const vector<int>& inventory,long long x,long long orders){
        long long res=0;
        for(int v :inventory){
            if(v>x){
                res+=(v-x);
                if(res>=orders){
                    return true;
                }
            }
        }
        return res>=orders;
    }
    int maxProfit(vector<int>& inventory, int orders) {
        sort(inventory.begin(), inventory.end(), greater<int>());
        long long l=0,r=inventory[0];
        while(l<r){
            long long mid=(l+r)>>1;
            if(check(inventory,mid,orders)){
                l=mid+1;
            }else{
                r=mid;
            }
        }
        long long x=l;

            long long res=0,remain=orders;
            for(int v:inventory){
                if(v>x){
                    long long a=v-x;
                    long long sum=((v+(x+1))*a/2)%mod;
                    res=(res+sum)%mod;
                    remain-=a;
                }
            }
        res=(res+remain*x)%mod;
        return (int)res; 
    }
};