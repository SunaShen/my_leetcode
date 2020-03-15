// @File   : 29_spiralOrder.cpp
// @Source : https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/
// @Title  : 面试题29. 顺时针打印矩阵
// @Auther : sun_ds
// @Date   : 2020/3/13

/**  题目描述：
    输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

     

    示例 1：

    输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
    输出：[1,2,3,6,9,8,7,4,5]
    示例 2：

    输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
    输出：[1,2,3,4,8,12,11,10,9,5,6,7]
     

    限制：

    0 <= matrix.length <= 100
    0 <= matrix[i].length <= 100
    注意：本题与主站 54 题相同：https://leetcode-cn.com/problems/spiral-matrix/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 模拟边界法
 *
 * 使用left，right,top和bottom来控制边界。
 * 在外圈执行从左到右，从上到下，从右到左，从下到上，逆时针循环。
 * 注意结束条件，是边界越界。
 * 即，当l==r时，还是有一列值的。
 *
 *
 *
 *
 */


class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.size()==0) return {};
        //模拟边界法
        int top = 0, bottom =  matrix.size()-1;
        int left = 0, right = matrix[0].size()-1;
        vector<int> res;
        while(1){
            for(int i=left;i<=right;i++) res.push_back(matrix[top][i]);
            top++;  if(top>bottom) break;
            for(int i=top;i<=bottom;i++) res.push_back(matrix[i][right]);
            right--; if(right<left) break;
            for(int i=right;i>=left;i--) res.push_back(matrix[bottom][i]);
            bottom--; if(bottom<top) break;
            for(int i=bottom;i>=top;i--) res.push_back(matrix[i][left]);
            left++;   if(left>right) break;
        }
        return res;
    }
};

