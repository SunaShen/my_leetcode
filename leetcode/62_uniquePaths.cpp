// @File   : 62_uniquePaths.cpp
// @Source : https://leetcode-cn.com/problems/unique-paths/
// @Title  : 不同路径
// @Auther : sun_ds
// @Date   : 2019/12/9

/**  题目描述：
    一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

    机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

    问总共有多少条不同的路径？



    例如，上图是一个7 x 3 的网格。有多少可能的路径？

    说明：m 和 n 的值均不超过 100。

    示例 1:

    输入: m = 3, n = 2
    输出: 3
    解释:
    从左上角开始，总共有 3 条路径可以到达右下角。
    1. 向右 -> 向右 -> 向下
    2. 向右 -> 向下 -> 向右
    3. 向下 -> 向右 -> 向右
    示例 2:

    输入: m = 7, n = 3
    输出: 28

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/unique-paths
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 不同路径
 * m为列，n为行
 * 1.组合数
 * m*n的区域，从左上到右下，共(m+n-2)步，其中竖直方向n-1步，水平方向m-1步
 * 因此不同的路径即，C(m+n-2,n-1) = C(m+n-2,m-1)种路径
 *
 * C(n,m) = n!/((m!)*(n-m)!)
 * 化简 C(n,m) = n*(n-1)*(n-2)*...*(n-m+1) / m!
 * float c。int i=1;
 * c *= (n--)/(float)(i++)
 * 会出错。时不时差点数。
 * 分两步，就行了！！
 * long c; int i=1;
 *  c *= (n--);
 *  c /= i++;
 *  why???????
 *
 *  2.dp
 *  只能向左或向下。所以到达当前位置路径数为左和上路径数之和
 *
 *  dp[i,j] = dp[i-1][j] + dp[i][j-1];
 *  起始条件：
 *  dp[0][j] = dp[i][0] = 1;
 *  结果：
 *  dp[n-1][m-1]
 *  从dp[1,1]行扫描实现
 *
 *  使用列扫描，可以减少存储复杂度。使用dp[n]
 *  dp[j] = dp[j] + dp[j-1];
 *  当前 = 左边 + 上边
 *  执行m次。
 *
 *
 * ！！！
 * 注意：memset只能将数字置0或-1
 * 按照字节赋值
 *
 *
 *
 */

//组合数
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m==0||n==0) return 0;
        n = n - 1;
        m = m - 1;
        int M = min(m,n);
        int N = m + n;
        long  res = 1;
        for(int i=1;i<=M;++i){
            res *= (N--);
            res /= i;
        }
        return res;
    }
};


//dp
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m==0||n==0) return 0;
        vector<vector<long long>> dp(n,vector<long long>(m,1));
        for(int i=1;i<n;++i){
            for(int j=1;j<m;++j){
                dp[i][j] = dp[i-1][j] + dp[i][j - 1];
            }
        }
        return dp[n-1][m-1];
    }
};

class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m==0||n==0) return 0;
        vector<long long> dp(n,1);
        for(int i=1;i<m;++i){
            for(int j=1;j<n;++j){
                dp[j] = dp[j] + dp[j-1];
            }
        }
        return dp[n-1];
    }
};


class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m==0||n==0) return 0;
        long long dp[n];
        // memset只能置0或-1.是按照自己赋值的。
        // memset(dp,1, sizeof(dp));
        for(int i=0;i<n;++i) dp[i] = 1;
        for(int i=1;i<m;++i){
            for(int j=1;j<n;++j){
                dp[j] = dp[j] + dp[j-1];
            }
        }
        return dp[n-1];
    }
};