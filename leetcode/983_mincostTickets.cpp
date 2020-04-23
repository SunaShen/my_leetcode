// @File   : 983_mincostTickets.cpp
// @Source : https://leetcode-cn.com/problems/minimum-cost-for-tickets/
// @Title  : 983. 最低票价
// @Auther : sun_ds
// @Date   : 2020/4/22

/**  题目描述：
    在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行。在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出。每一项是一个从 1 到 365 的整数。

    火车票有三种不同的销售方式：

    一张为期一天的通行证售价为 costs[0] 美元；
    一张为期七天的通行证售价为 costs[1] 美元；
    一张为期三十天的通行证售价为 costs[2] 美元。
    通行证允许数天无限制的旅行。 例如，如果我们在第 2 天获得一张为期 7 天的通行证，那么我们可以连着旅行 7 天：第 2 天、第 3 天、第 4 天、第 5 天、第 6 天、第 7 天和第 8 天。

    返回你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费。

     

    示例 1：

    输入：days = [1,4,6,7,8,20], costs = [2,7,15]
    输出：11
    解释：
    例如，这里有一种购买通行证的方法，可以让你完成你的旅行计划：
    在第 1 天，你花了 costs[0] = $2 买了一张为期 1 天的通行证，它将在第 1 天生效。
    在第 3 天，你花了 costs[1] = $7 买了一张为期 7 天的通行证，它将在第 3, 4, ..., 9 天生效。
    在第 20 天，你花了 costs[0] = $2 买了一张为期 1 天的通行证，它将在第 20 天生效。
    你总共花了 $11，并完成了你计划的每一天旅行。
    示例 2：

    输入：days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
    输出：17
    解释：
    例如，这里有一种购买通行证的方法，可以让你完成你的旅行计划：
    在第 1 天，你花了 costs[2] = $15 买了一张为期 30 天的通行证，它将在第 1, 2, ..., 30 天生效。
    在第 31 天，你花了 costs[0] = $2 买了一张为期 1 天的通行证，它将在第 31 天生效。
    你总共花了 $17，并完成了你计划的每一天旅行。
     

    提示：

    1 <= days.length <= 365
    1 <= days[i] <= 365
    days 按顺序严格递增
    costs.length == 3
    1 <= costs[i] <= 1000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/minimum-cost-for-tickets
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 * dp[i]表示第i天需要的最小花费
 *
 * 两种情况：
 * 1）当天不需要出去，则花费等于前一天  dp[i] = dp[i-1]
 * 2) 当天需要出去，则花费等于 min(dp[i-1]+cost[0],dp[i-7]+cost[1],dp[i-30]+cost[2]);
 *    若i-1，i-7，i-30小于0了那么就是0
 *
 * 最终得到dp[days.back()]就是最终结果
 *
 */

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int max = days[days.size()-1];
        vector<int> dp(max+1,INT_MAX);
        vector<bool> flag(max+1,false);
        vector<int> p = {1,7,30};
        dp[0] = 0;
        for(auto i:days){
            flag[i]=true;
        }
        for(int i=1;i<=max;i++){
            if(flag[i]){
                for(int j=0;j<costs.size();j++){
                    if(i - p[j]<0){
                        dp[i] = min(dp[i],costs[j]);
                    }else{
                        dp[i] = min(dp[i],dp[i - p[j]]+costs[j]);
                    }
                }
            }else{ //这一天不需要出去，则花销等于前一天
                dp[i] = dp[i-1];
            }
        }
        return dp[max];
    }
};