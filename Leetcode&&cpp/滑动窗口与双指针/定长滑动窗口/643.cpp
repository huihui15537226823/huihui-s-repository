#include <vector>     // std::vector
#include <climits>    // INT_MIN
#include <algorithm>  // std::max
using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n=nums.size();
        int result=INT_MIN;
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=nums[i];
            if(i<k-1){
                continue;
            }
            result=max(sum,result);
            sum-=nums[i-k+1];
        }
        return 1.0*result/k;
    }
};

//在k很大时会遇到超时
// class Solution {
// public:
//     double findMaxAverage(vector<int>& nums, int k) {
//         int n=nums.size();
//         int result=-1000000000;
//         int l=0,r=0,av=0;
//         while(r<n){
//             if(r-l+1>=k){
//                 av=0;
//                 for(int i=0;i<k;i++){
//                     av+=nums[i+l];
//                 }
//                 result=max(result,av);
//                 l++;
//             }
//             r++;
//         }
//         return 1.0*result/k;
//     }
// };