// @File   : 914_hasGroupsSizeX.cpp
// @Source : https://leetcode-cn.com/problems/x-of-a-kind-in-a-deck-of-cards/
// @Title  : 914. 卡牌分组
// @Auther : sun_ds
// @Date   : 2020/3/27

/**  题目描述：
    给定一副牌，每张牌上都写着一个整数。

    此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成 1 组或更多组：

    每组都有 X 张牌。
    组内所有的牌上都写着相同的整数。
    仅当你可选的 X >= 2 时返回 true。

     

    示例 1：

    输入：[1,2,3,4,4,3,2,1]
    输出：true
    解释：可行的分组是 [1,1]，[2,2]，[3,3]，[4,4]
    示例 2：

    输入：[1,1,1,2,2,2,3,3]
    输出：false
    解释：没有满足要求的分组。
    示例 3：

    输入：[1]
    输出：false
    解释：没有满足要求的分组。
    示例 4：

    输入：[1,1]
    输出：true
    解释：可行的分组是 [1,1]
    示例 5：

    输入：[1,1,2,2,2,2]
    输出：true
    解释：可行的分组是 [1,1]，[2,2]，[2,2]

    提示：

    1 <= deck.length <= 10000
    0 <= deck[i] < 10000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/x-of-a-kind-in-a-deck-of-cards
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.最大公约数
 *  均匀分组，且分组内数字相同(没有要求一个数字不可以分成好几组。。)
 *  首先，统计各数字出现次数。
 *  然后，计算各个数字个数之间的最大公约数。若最大公约数大于2，则返回true。
 *
 *
 */

class Solution {
public:
    int gcd(int a,int b){
        if(a%b==0) return b;
        return gcd(b,a%b);
    }
    bool hasGroupsSizeX(vector<int>& deck) {
        vector<int> count(10000,0);
        for(auto i:deck){
            count[i]++;
        }
        int temp = -1;
        for(int i=0;i<10000;i++){
            if(count[i]!=0){
                if(temp==-1) temp = count[i];
                temp = gcd(count[i],temp);
                if(temp <= 1) return false;
            }
        }
        return temp>=2;
    }
};
