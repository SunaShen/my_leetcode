// @File   : 122_maxProfit.cpp
// @Source : https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/
// @Title  : 122. 买卖股票的最佳时机 II
// @Auther : sun_ds
// @Date   : 2020/3/20

/**  题目描述：
    给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

    设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

    注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

    示例 1:

    输入: [7,1,5,3,6,4]
    输出: 7
    解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
         随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。
    示例 2:

    输入: [1,2,3,4,5]
    输出: 4
    解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
         注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
         因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
    示例 3:

    输入: [7,6,4,3,1]
    输出: 0
    解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
*/

/**
 *
 * 1.贪心
 *  涨了就卖，跌了就当没买。
 *
 * 2.单调栈
 * 单调递增栈
 * 一插入打破递增关系，则回头卖一手。
 *
 */

//贪心
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int res = 0;
        for(int i=1;i<n;i++){
            res += prices[i] - prices[i-1] > 0 ? prices[i] - prices[i-1] : 0;
        }
        return res;
    }
};

//单调栈
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        vector<int> s; //使用vector，当一个单调递增栈，因为要取栈底，用vector方便点
        prices.push_back(0); //末尾添加0，使得前面都可以出栈被更新
        for (int i = 0; i < prices.size(); ++ i){
            while (!s.empty() && s.back() > prices[i]){
                ans += s.back() - s.front();
                s.clear();
            }
            s.push_back(prices[i]);
        }
        return ans;
    }
};

