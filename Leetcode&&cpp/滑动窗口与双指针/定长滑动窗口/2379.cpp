#include <string>
using namespace std;
#define W 1
#define B 0
class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int w=0;
        for(int i=0;i<k;i++){
            w+=blocks[i]&W;
        }
        int result=w;
        for(int i=k;i<blocks.length();i++){
            w+=(blocks[i]&W)-(blocks[i-k]&W);
            result=min(w,result);
        }
        return result;
    }
};