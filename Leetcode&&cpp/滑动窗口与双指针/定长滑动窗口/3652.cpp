class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        long long result=0;
        long long add=0,max_add=0;
        for(int i=0;i<prices.size();i++){
            result+=(prices[i]*strategy[i]);
            add+=(prices[i]*(1-strategy[i]));

            if(i<k-1){
                if(i>=k/2-1){
                    add-=prices[i-k/2+1];//将设为1的改回0
                }
                continue;
            }
            max_add=max(max_add,add);

            add=add-prices[i-k/2+1]+prices[i-k+1]*strategy[i-k+1];
        }
        return result+max_add;
    }
};