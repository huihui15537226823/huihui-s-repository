#include <vector>
using namespace std;
class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int result=0;
        int a=capacityA,b=capacityB;
        int i=0,j=plants.size()-1;
        while(i<j){
            if(a<plants[i]){
                result++;
                a=capacityA;
            }
            a-=plants[i++];
            if(b<plants[j]){
                result++;
                b=capacityB;
            }
            b-=plants[j--];
        }
        if(i==j && max(a,b)<plants[i]){
            result++;
        }
        return result;
    }
};