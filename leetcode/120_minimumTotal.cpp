// @File   : 120_minimumTotal.cpp
// @Source : https://leetcode-cn.com/problems/triangle/
// @Title  : 三角形最小路径和
// @Auther : sun_ds
// @Date   : 2019/11/29

/**  题目描述：
    给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

    例如，给定三角形：

    [
         [2],
        [3,4],
       [6,5,7],
      [4,1,8,3]
    ]
    自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

    说明：

    如果你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题，那么你的算法会很加分。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/triangle
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。
 *  dp问题
 *
 *  最优子结构
 *  每一个顶点最优可以看成是其下一行相邻节点中的最优(路径最短)
 *
 *  dp[i][j] = min(dp[i+1][j],dp[i+1][j+1]) + dp[i][j]
 *  自底向上
 *  从最后一行开始
 *  得到最短路径为dp[0][0]
 *
 *  为了节省空间，重写triangle本身充当dp
 *
 *
 */


class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        for(int i=triangle.size()-2;i>=0;--i){
            for(int j=0;j<i+1;++j){
                triangle[i][j] = triangle[i][j] + min(triangle[i+1][j],triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];
    }
};



