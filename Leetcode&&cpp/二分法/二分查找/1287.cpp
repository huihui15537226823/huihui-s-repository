class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        unordered_map<int,int> a;
        for(auto i:arr){
            a[i]++;
            if(a[i]*4>arr.size()){
                return i;
            }
        }
        return 0;
    }
};