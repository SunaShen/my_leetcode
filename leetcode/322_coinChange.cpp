// @File   : 322_coinChange.cpp
// @Source : https://leetcode-cn.com/problems/coin-change/
// @Title  : 零钱兑换
// @Auther : sun_ds
// @Date   : 2020/1/10

/**  题目描述：
    给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

    示例 1:

    输入: coins = [1, 2, 5], amount = 11
    输出: 3
    解释: 11 = 5 + 5 + 1
    示例 2:

    输入: coins = [2], amount = 3
    输出: -1
    说明:
    你可以认为每种硬币的数量是无限的。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/coin-change
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 不同面值组成固定金额，使得硬币数最小
 *
 * 1.dp
 *  转移方程
 *    dp[0] = 0;
 *    dp[amount] = 1 + min(dp[amount - coins[k]])
 *
 *  使用dp[i] = -1;代表不可到达。
 *
 *  使用for循环，自底向上更新dp数组。
 *  即得结果dp[amount]
 *
 */

//dp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int *dp = new int[amount+1];
        dp[0] = 0;
        for(int i=1;i<=amount;++i){
            int temp = INT_MAX;
            for(auto iter=coins.begin();iter!=coins.end();++iter){
                if((i-*iter>=0)&&(dp[i-*iter]!=-1)){
                    temp = temp < dp[i-*iter]+1 ? temp : dp[i-*iter]+1;
                }
            }
            if(temp != INT_MAX)
                dp[i] = temp;
            else
                dp[i] = -1;
        }
        return dp[amount];
    }
};

//当前的回头找前面的来给自己更新 (可不可达都不知道)
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1,INT_MAX-1);
        dp[0] = 0;
        //i即为当前值，i需要他之前的以确定好的值来确定
        for(int i=1;i<=amount;i++){
            for(int j=0;j<coins.size();j++){
                if(coins[j] <= i){
                    //无法到达使用INT_MAX-1表示,防止其dp[i - coins[j]]+1时溢出
                    dp[i] = min(dp[i],dp[i - coins[j]]+1);
                }
            }
        }
        return dp[amount] == INT_MAX-1 ? -1 : dp[amount];
    }
};

//当前的更新后面可达的 (默认都保证了可达)
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1,INT_MAX);
        //i为当前值，但是他是一只在更新他加一个硬币后的值。
        dp[0] = 0;
        for(int i=0;i<amount;i++){
            //只有当前位置可达他后面的位置才可达
            if(dp[i]!=INT_MAX){
                for(int j=0;j<coins.size();j++){
                    //会有INT_MAX大的金币，防止溢出
                    long index = (long)i + coins[j];
                    //超过总金额的不需要更新
                    if(index <= amount){
                        //dp[i]+1不会溢出，因为确定dp[i]!=INT_MAX
                        dp[index] = min(dp[index],dp[i]+1);
                    }
                }
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};
