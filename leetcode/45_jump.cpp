// @File   : 45_jump.cpp
// @Source : https://leetcode-cn.com/problems/jump-game-ii/
// @Title  : 45. 跳跃游戏 II
// @Auther : sun_ds
// @Date   : 2020/5/4

/**  题目描述：
    给定一个非负整数数组，你最初位于数组的第一个位置。

    数组中的每个元素代表你在该位置可以跳跃的最大长度。

    你的目标是使用最少的跳跃次数到达数组的最后一个位置。

    示例:

    输入: [2,3,1,1,4]
    输出: 2
    解释: 跳到最后一个位置的最小跳跃数是 2。
         从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
    说明:

    假设你总是可以到达数组的最后一个位置。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/jump-game-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 跳跃游戏并记录最小跳跃次数
 *
 * 1.dp 超时
 * dp[i]表示到达i位置的最小跳跃次数。
 * dp[i] = min(dp[j]+1) 其中j是[0,i-1]中满足，nums[j]+j>=i的值。即从j位置能够一步到达i位置。
 * 初始条件，dp[0] = 0.
 * 则到达最后一个位置的最小跳跃次数为dp[n-1].
 *
 * 时间复杂度O(N^2)
 * 空间复杂度O(N)
 *
 * 2.贪心
 * 使用max_pos记录当前之前位置能够到达的最远位置，一直在更新。
 * 而，end记录当前轮能够到达的最远位置，即从i-end之间的位置的都是由前面一个位置一步跳到的。
 * 贪心，每次跳跃都从当前位置跳到当前轮最远的end作为跳跃一步。
 *
 *
 *
 *
 */

//暴力法，超时
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,INT_MAX);
        dp[0] = 0;
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[j]+j>=i&&dp[j]!=INT_MAX)
                    dp[i] = min(dp[i],dp[j]+1);
            }
        }
        return dp[n-1];
    }
};

//贪心
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int max_pos = 0, end = 0, step = 0;
        for(int i=0;i<n-1;i++){
            max_pos = max(max_pos,nums[i]+i);
            if(i==end){//一轮结束(类似层序遍历，一层一层。使用end作为判断条件)
                end = max_pos;
                step++;
            }
        }
        return step;
    }
};