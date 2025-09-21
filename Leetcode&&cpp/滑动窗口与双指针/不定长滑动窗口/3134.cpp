//先考虑数组个数,依次,n个数的有一个,以此为n-1,n-2 ......1;
//和为sum=(1+n)*n/2 ,然后中位数是n为偶数则是第sum/2个,n为奇数就是第(sum+1)/2个
//然后考虑重复元素怎么办或者说怎么确定这个中位数的数是啥
//这个使num_sum和超过sum的最小不重复元素数应该就是这个值吧,现在就是考虑怎么算不重复元素数,哈希?
class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n=nums.size();
        long long sum = 1LL * n * (n + 1) / 2;
        long long k = (sum % 2 == 0 ? sum / 2 : (sum + 1) / 2);//中位数是第k个

        unordered_set<int> st(nums.begin(), nums.end());
        int m = st.size();//也就是说最大的数也就是m,这个中位数值result肯定是小于m
        //去算不重复元素小于d的每一个N(d),然后S(d)大于k了就是d
        int l = 1, r = m, result = m;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (Count(nums, mid) >= k) {
                result = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return result;

    }
    long long Count(vector<int>& nums, int d){
        unordered_map<int,int> f;
        int left=0,distinct=0;
        long long count=0;
        for(int right=0;right<nums.size();right++){
            if(++f[nums[right]]==1){
                distinct++;
            }
            while(distinct>d){
                if(--f[nums[left]]==0){
                    distinct--;
                }
                left++;
            }
            count+=(right-left+1);
        }
        return count;
    }
};