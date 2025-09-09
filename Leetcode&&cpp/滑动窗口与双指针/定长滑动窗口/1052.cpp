#include <vector>
using namespace std;
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int a=0;
        int b=0;
        int max_b=0;
        for(int i=0;i<customers.size();i++){
            if(grumpy[i]==0){
                a+=customers[i];
            }else if(grumpy[i]==1){
                b+=customers[i];
            }
            if(i<minutes-1){
                continue;
            }
            max_b=max(max_b,b);
            if(grumpy[i-minutes+1]==1){
                b-=customers[i-minutes+1];
            }
        }
        return a+max_b;
    }
};