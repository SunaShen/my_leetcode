// @File   : 55_canJump.cpp
// @Source : https://leetcode-cn.com/problems/jump-game/
// @Title  : 跳跃游戏
// @Auther : sun_ds
// @Date   : 2019/11/28

/**  题目描述：
    给定一个非负整数数组，你最初位于数组的第一个位置。

    数组中的每个元素代表你在该位置可以跳跃的最大长度。

    判断你是否能够到达最后一个位置。

    示例 1:

    输入: [2,3,1,1,4]
    输出: true
    解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。
    示例 2:

    输入: [3,2,1,0,4]
    输出: false
    解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/jump-game
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 *
 *
 *
 *
 *
 *
 */


//回溯法,超时
class Solution {
public:
    vector<int> num;
    int n;
    int min(int a, int b){
        return a<b?a:b;
    }
    bool func(int k){
        if(k>=n-1){
            return true;
        }
        for(int i=min(k+num[k],n-1);i>=k+1;--i){
            bool f = func(i);
            if(f) return true;
        }
        return false;
    }
    bool canJump(vector<int>& nums) {
        n = nums.size();
        num = nums;
        return func(0);
    }
};

//dp
class Solution {
public:
    int min(int a,int b){
        return a<b?a:b;
    }
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n<=1) return true;
        bool *dp = new bool[n]();
        if(nums[0]!=0) dp[0] = true;
        else return false;
        for(int i=0;i<n;++i){
            if(dp[i]){
                for(int j=i+1;j<min(i+1+nums[i],n);++j){
                    dp[j] = true;
                    if(dp[n-1]) return true;
                }
            }
        }
        return dp[n-1];
    }
};

//贪心
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int k = 0;
        for(int i=0;i<n;++i){
            if(i>k)
                return false;
            k = max(k,i+nums[i]);
            if(k>=n-1)
                return true;
        }
        return true;
    }
};