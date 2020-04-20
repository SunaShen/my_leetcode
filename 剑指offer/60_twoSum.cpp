// @File   : 60_twoSum.cpp
// @Source : https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof/
// @Title  : 面试题60. n个骰子的点数
// @Auther : sun_ds
// @Date   : 2020/4/5

/**  题目描述：
    把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。

     

    你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。

     

    示例 1:

    输入: 1
    输出: [0.16667,0.16667,0.16667,0.16667,0.16667,0.16667]
    示例 2:

    输入: 2
    输出: [0.02778,0.05556,0.08333,0.11111,0.13889,0.16667,0.13889,0.11111,0.08333,0.05556,0.02778]
     

    限制：

    1 <= n <= 11

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 * dp[i]表示 i点数的概率
 *
 * n表示n轮。
 * 当前轮的值只能由上一轮的值更新。
 * 第n轮的取值范围为[n,6*n];
 * 每一轮更新时要倒序并且将当前位置置零。
 * 倒序的原因当前轮可取值范围和上一轮可取值范围有交叉
 * 如果，正序的话更新当前轮时用的值可能不是上一轮的，而是这一轮更新过的值。
 * dp[j]要置零。当前点数代表的是当前轮的点数的概率，要重新算的。
 * 如果使用二维数组应该方便点，不用考虑这么多。每个轮次不影响
 *
 *
 */

class Solution {
public:
    vector<double> twoSum(int n) {
        const double p = 1.0/6;
        vector<double> dp(6*n+1,0);
        for(int i=1;i<=6;i++){
            dp[i] = p;
        }
        for(int i=2;i<=n;i++){ //轮次
            for(int j=6*i;j>=i;j--){ //当前轮次可取得值  必须倒序更新
                dp[j] = 0;
                for(int k=j-1;k>=i-1&&k>=j-6;k--){ //当前值需要前6个来更新 k>=i-1是上一轮最小值就是i-1了
                    dp[j] += p*dp[k];
                }
            }
        }
        return vector<double>(dp.begin()+n,dp.end());
    }
};


class Solution {
public:
    vector<double> twoSum(int n) {
        const double p = 1.0/6;
        vector<double> dp(6*n+1,0);
        for(int i=1;i<=6;i++){
            dp[i] = p;
        }
        for(int i=2;i<=n;i++){ //轮次
            for(int j=6*i;j>=i;j--){
                // 核心   倒序并且将当前位置置零。
                // 倒序的原因当前轮可取值范围和上一轮可取值范围有交叉
                // 如果，正序的话更新当前轮时用的值可能不是上一轮的，而是这一轮更新过的值。
                // dp[j]要置零。当前点数代表的是当前轮的点数的概率，要重新算的。
                // 如果使用二维数组应该方便点，不用考虑这么多。每个轮次不影响
                dp[j] = 0;
                for(int k=1;k<=6;k++){
                    int index = j - k;
                    if(index<=(i-1)*6&&index>=(i-1)) //在上一轮范围内。
                        dp[j] += p*dp[index];
                }
            }
        }
        return vector<double>(dp.begin()+n,dp.end());
    }
};
