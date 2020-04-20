// @File   : 17-16_massage.cpp
// @Source : https://leetcode-cn.com/problems/the-masseuse-lcci/
// @Title  : 面试题 17.16. 按摩师
// @Auther : sun_ds
// @Date   : 2020/3/24

/**  题目描述：
    一个有名的按摩师会收到源源不断的预约请求，每个预约都可以选择接或不接。在每次预约服务之间要有休息时间，因此她不能接受相邻的预约。给定一个预约请求序列，替按摩师找到最优的预约集合（总预约时间最长），返回总的分钟数。

    注意：本题相对原题稍作改动

     

    示例 1：

    输入： [1,2,3,1]
    输出： 4
    解释： 选择 1 号预约和 3 号预约，总时长 = 1 + 3 = 4。
    示例 2：

    输入： [2,7,9,3,1]
    输出： 12
    解释： 选择 1 号预约、 3 号预约和 5 号预约，总时长 = 2 + 9 + 1 = 12。
    示例 3：

    输入： [2,1,4,5,3,1,1,3]
    输出： 12
    解释： 选择 1 号预约、 3 号预约、 5 号预约和 8 号预约，总时长 = 2 + 4 + 3 + 3 = 12。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/the-masseuse-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * dp
 * 不能连续
 * 当前最长时长 = 当前不选(i-1的长度) 或 当前选 (i-2的长度+i的时间)
 * dp[i] = max(dp[i-2]+nums[i],dp[i-1])
 *
 *
 */

class Solution {
public:
    int massage(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+2,0);
        for(int i=2;i<=n+1;i++){
            dp[i] = max(dp[i-2]+nums[i-2],dp[i-1]);
        }
        return dp[n+1];
    }
};

class Solution {
public:
    int massage(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        vector<int> dp(n,0);
        dp[0] = nums[0];
        dp[1] = max(dp[0],nums[1]);
        for(int i=2;i<n;i++){
            dp[i] = max(dp[i-2]+nums[i],dp[i-1]);
        }
        return dp[n-1];
    }
};
