// @File   : 121_maxProfit.cpp
// @Source : https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/
// @Title  : 121. 买卖股票的最佳时机
// @Auther : sun_ds
// @Date   : 2020/3/9

/**  题目描述：
    给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

    如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。

    注意你不能在买入股票前卖出股票。

    示例 1:

    输入: [7,1,5,3,6,4]
    输出: 5
    解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
         注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
    示例 2:

    输入: [7,6,4,3,1]
    输出: 0
    解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.逆序统计每个位置右边的最大值
 *  right_max[i] = max(prices[i+1],right_max[i+1]);
 * 2.正序统计每个位置左边的最小值min_price
 *
 * 3.单调栈
 *  维护一个单调递增栈
 *  插入元素大于栈顶直接插入。
 *  插入元素小于栈顶，则栈顶出栈，并计算栈顶位置最多赚的钱 = 栈顶 - 栈底。
 *  在price末尾添加哨兵0，这样使得所有元素都能出栈被更新。
 *
 *
 *
 */



class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        //每个位置右边的最大值
        vector<int> right_max(n,0);
        for(int i=n-2;i>=0;i--){
            right_max[i] = max(prices[i+1],right_max[i+1]);
        }
        int res = 0;
        //计算当前元素与其右边最大值差值的最大值
        for(int i=0;i<n;i++){
            res = max(res,right_max[i] - prices[i]);
        }
        return res;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int res = 0, min_price = INT_MAX;
        for(int i=0;i<n;i++){
            //计算今日卖掉能赚多少钱
            res = max(res, prices[i] - min_price);
            //当前位置之前的最小值(假设是此时买入)
            min_price = min(min_price,prices[i]);
        }
        return res;
    }
};

//单调递增栈
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        vector<int> s; //使用vector，当一个单调递增栈，因为要取栈底，用vector方便点
        prices.push_back(0); //末尾添加0，使得前面都可以出栈被更新
        for (int i = 0; i < prices.size(); ++ i){
            while (!s.empty() && s.back() > prices[i]){
                ans = max(ans, s.back() - s.front());
                s.pop_back();
            }
            s.push_back(prices[i]);
        }
        return ans;
    }
};

