// @File   : 1217_minCostToMoveChips.cpp
// @Source : https://leetcode-cn.com/problems/play-with-chips/
// @Title  : 玩筹码
// @Auther : sun_ds
// @Date   : 2019/10/7


/*  题目描述：
    数轴上放置了一些筹码，每个筹码的位置存在数组 chips 当中。

    你可以对 任何筹码 执行下面两种操作之一（不限操作次数，0 次也可以）：

    将第 i 个筹码向左或者右移动 2 个单位，代价为 0。
    将第 i 个筹码向左或者右移动 1 个单位，代价为 1。
    最开始的时候，同一位置上也可能放着两个或者更多的筹码。

    返回将所有筹码移动到同一位置（任意位置）上所需要的最小代价。

     

    示例 1：

    输入：chips = [1,2,3]
    输出：1
    解释：第二个筹码移动到位置三的代价是 1，第一个筹码移动到位置三的代价是 0，总代价为 1。
    示例 2：

    输入：chips = [2,2,2,3,3]
    输出：2
    解释：第四和第五个筹码移动到位置二的代价都是 1，所以最小总代价为 2。
     

    提示：

    1 <= chips.length <= 100
    1 <= chips[i] <= 10^9

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/play-with-chips
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/


/*
 * 最小代价移动筹码
 * 规则：
 * 将第 i 个筹码向左或者右移动 2 个单位，代价为 0。
 * 将第 i 个筹码向左或者右移动 1 个单位，代价为 1。
 *
 * 简化：
 * 即奇数与奇数位置，偶数与偶数位置移动代价为0
 * 奇偶位置互换代价为1
 * 统计奇数个数与偶数个数，那个少就把少的换到多的，代价也为少的个数
 * 复杂度O(n)
 *
 * 麻烦方法，遍历
 * 复杂度O(n^2)
 *
 */

#include <iostream>
#include <vector>

using namespace std;



class Solution {
public:
    int minCostToMoveChips(vector<int>& chips) {
        int count[2] = {0,0};
        for(int i:chips) count[i&1]++;
        return min(count[0],count[1]);
    }
};

//直接强行遍历。。
//class Solution {
//public:
//    int minCostToMoveChips(vector<int>& chips) {
//        int n = chips.size();
//        int fei[n];
//        int res = INT_MAX;
//        for(int i=0;i<n;i++)
//        {
//            fei[i] = 0;
//            for(int j=0;j<n;j++)
//            {
//                if(abs(chips[j]-chips[i])%2 == 1)
//                    fei[i] += 1;
//            }
//            if(res > fei[i])
//                res = fei[i];
//        }
//        return res;
//    }
//};

int main()
{
    vector<int> chips = {2,2,2,3,3};
    Solution su;
    auto res = su.minCostToMoveChips(chips);

    cout << res << endl;
    cout << "finish" << endl;
    return 0;
}
