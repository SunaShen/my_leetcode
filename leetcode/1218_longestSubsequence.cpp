// @File   : 1218_longestSubsequence.cpp
// @Source : https://leetcode-cn.com/problems/longest-arithmetic-subsequence-of-given-difference/
// @Title  : 最长定差子序列
// @Auther : sun_ds
// @Date   : 2019/10/7


/*  题目描述：
    给你一个整数数组 arr 和一个整数 difference，请你找出 arr 中所有相邻元素之间的差等于给定 difference 的等差子序列，并返回其中最长的等差子序列的长度。

     

    示例 1：

    输入：arr = [1,2,3,4], difference = 1
    输出：4
    解释：最长的等差子序列是 [1,2,3,4]。
    示例 2：

    输入：arr = [1,3,5,7], difference = 1
    输出：1
    解释：最长的等差子序列是任意单个元素。
    示例 3：

    输入：arr = [1,5,7,8,5,3,4,2,1], difference = -2
    输出：4
    解释：最长的等差子序列是 [7,5,3,1]。
     

    提示：

    1 <= arr.length <= 10^5
    -10^4 <= arr[i], difference <= 10^4

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-arithmetic-subsequence-of-given-difference
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 *
 * 最长定差子序列--动态规划问题
 * dp使用map结构
 * dp为当前最长等差子序列中的末尾元素和当前最长子序列长度
 * 则该元素的前一个元素必为i-difference(如果有的话)
 * 更新方程：dp[i] = max(dp[i], dp[i-difference]+1);
 *
 * dp设的很讲究
 *
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        map<int,int> dp;
        dp.clear();
        int res = INT_MIN;
        for(auto i:arr)
        {
            int temp = max(dp[i],dp[i - difference] + 1);
            res = max(res,temp);
            dp[i] = temp;
        }
        return res;
    }
};

int main()
{
    vector<int> arr = {1,5,7,8,5,3,4,2,1};
    int diff = -2;
    Solution su;
    auto res = su.longestSubsequence(arr,diff);

    cout << res << endl;
    cout << "finish" << endl;
    return 0;
}


