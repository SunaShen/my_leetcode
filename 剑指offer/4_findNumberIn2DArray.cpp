// @File   : 4_findNumberIn2DArray.cpp
// @Source : https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/
// @Title  : 面试题04. 二维数组中的查找
// @Auther : sun_ds
// @Date   : 2020/2/19

/**  题目描述：
    在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

     

    示例:

    现有矩阵 matrix 如下：

    [
      [1,   4,  7, 11, 15],
      [2,   5,  8, 12, 19],
      [3,   6,  9, 16, 22],
      [10, 13, 14, 17, 24],
      [18, 21, 23, 26, 30]
    ]
    给定 target = 5，返回 true。

    给定 target = 20，返回 false。

     

    限制：

    0 <= n <= 1000

    0 <= m <= 1000

     

    注意：本题与主站 240 题相同：https://leetcode-cn.com/problems/search-a-2d-matrix-ii/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * 在二维矩阵中搜索某个数target
 * 暴力搜索复杂度为O(M*N)
 *
 * 矩阵满足条件：每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序
 * 引入标志数。此类矩阵中左下角和右上角元素有特殊性，称为标志数。
 *  左下角元素： 为所在列最大元素，所在行最小元素。
 *  右上角元素： 为所在行最大元素，所在列最小元素。
 *
 * 标志数性质： 将 matrix 中的左下角元素（标志数）记作 flag ，则有:
 *  若 flag > target ，则 target 一定在 flag 所在行的上方，即 flag 所在行可被消去。
 *  若 flag < target ，则 target 一定在 flag 所在列的右方，即 flag 所在列可被消去。
 * 本题解以左下角元素为例，同理，右上角元素 也具有行（列）消去的性质
 *
 * 算法流程： 根据以上性质，设计算法在每轮对比时消去一行（列）元素，以降低时间复杂度。
 * 从矩阵 matrix 左下角元素（索引设为 (i, j) ）开始遍历，并与目标值对比：
 *  当 matrix[i][j] > target 时： 行索引向上移动一格（即 i--），即消去矩阵第 i 行元素；
 *  当 matrix[i][j] < target 时： 列索引向右移动一格（即 j++），即消去矩阵第 j 列元素；
 *  当 matrix[i][j] == target 时： 返回true 。
 *  若行索引或列索引越界，则代表矩阵中无目标值，返回false
 *
 *
 *  时间复杂度 O(M+N) ：其中N和M分别为矩阵行数和列数，此算法最多循环M+N 次。
 *  空间复杂度O(1) : i, j 指针使用常数大小额外空间。
 *
 *  作者：jyd
 *  链接：https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/solution/mian-shi-ti-04-er-wei-shu-zu-zhong-de-cha-zhao-zuo/
 *  来源：力扣（LeetCode）
 *  著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 */


class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0||matrix[0].size()==0) return false;
        int m = matrix.size(), n = matrix[0].size();
        int i = m-1, j = 0;
        while(i>=0&&j<n){
            if(matrix[i][j] == target) return true;
            else if(matrix[i][j] > target) i--;
            else j++;
        }
        return false;
    }
};


