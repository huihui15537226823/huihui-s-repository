#include <vector>
using namespace std;
class Solution {
public:
    int maxArea(vector<int>& height) {
        int leng=0;
        int r=height.size()-1;
        int h=0;
        int s=0;
        while(leng<r){
            h=min(height[leng],height[r]);
            int news=h*(r-leng);
            s=max(s,news);
            if(height[leng]<=height[r]){
                ++leng;
            }else{
                --r;
            }
        }
        return s;
    }
};