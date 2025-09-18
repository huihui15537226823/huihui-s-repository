#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        sort(tiles.begin(),tiles.end());
        int result=0,left=0,cur=0;
        for(int r=0;r<tiles.size();r++){
            cur+=tiles[r][1]-tiles[r][0]+1;
            while(tiles[r][1]-carpetLen+1>tiles[left][1]){
                cur-=tiles[left][1]-tiles[left][0]+1;
                left++;
            }
            result=max(result,cur-max(0,tiles[r][1]-carpetLen+1-tiles[left][0]));
        }
        return result;
    }
};