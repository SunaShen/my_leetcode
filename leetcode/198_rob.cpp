// @File   : 198_rob.cpp
// @Source : https://leetcode-cn.com/problems/house-robber/
// @Title  : 打家劫舍
// @Auther : sun_ds
// @Date   : 2019/12/4

/**  题目描述：
    你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

    给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。

    示例 1:

    输入: [1,2,3,1]
    输出: 4
    解释: 偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
         偷窃到的最高金额 = 1 + 3 = 4 。
    示例 2:

    输入: [2,7,9,3,1]
    输出: 12
    解释: 偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
         偷窃到的最高金额 = 2 + 9 + 1 = 12 。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/house-robber
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 每两个数不能相邻，求最大值
 *
 * 动态规划
 * k处的最大值，等于不选nums[i],采用i-1处最大值dp[i-1]或者选nums[i]与dp[i-2]的和，不选用dp[i-1];
 * dp[k] = max(dp[i-2]+nums[i],dp[i-1])
 *
 */

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n==0) return 0;
        int dp[n+1];
        memset(dp,0,sizeof(dp));
        dp[1] = nums[0];
        for(int i=2;i<=n;i++){
            dp[i] = max(dp[i-2]+nums[i-1], dp[i-1]);
        }
        return dp[n];
    }
};