// @File   : 01.07_rotate.cpp
// @Source : https://leetcode-cn.com/problems/rotate-matrix-lcci/
// @Title  : 面试题 01.07. 旋转矩阵
// @Auther : sun_ds
// @Date   : 2020/4/7

/**  题目描述：
    给你一幅由 N × N 矩阵表示的图像，其中每个像素的大小为 4 字节。请你设计一种算法，将图像旋转 90 度。

    不占用额外内存空间能否做到？

     

    示例 1:

    给定 matrix =
    [
      [1,2,3],
      [4,5,6],
      [7,8,9]
    ],

    原地旋转输入矩阵，使其变为:
    [
      [7,4,1],
      [8,5,2],
      [9,6,3]
    ]
    示例 2:

    给定 matrix =
    [
      [ 5, 1, 9,11],
      [ 2, 4, 8,10],
      [13, 3, 6, 7],
      [15,14,12,16]
    ],

    原地旋转输入矩阵，使其变为:
    [
      [15,13, 2, 5],
      [14, 3, 4, 1],
      [12, 6, 8, 9],
      [16, 7,10,11]
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/rotate-matrix-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 *
 * 1.四分之一
 *
 * 使用左上角四分之一为基准。进行旋转。
 * 每次交换四个值。
 *
 * 注意n为偶数时，四分之一取值为 [0,n/2) 和 [0,n/2) 完美的四分之一
 * 当n为奇数时，四分之一取值为 [0,n/2] 和 [0,n/2) 不是完美四分之一
 *
 * 统一起来。
 *        for(int i=0;i<(n+1)/2;i++)
 *           for(int j=0;j<n/2;j++)
 *
 *
 * 2.先转置，后行反转
 *
 *
 */


class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if(matrix.size()==0) return;
        int n = matrix.size();
        //for循环控制左上角
        for(int i=0;i<(n+1)/2;i++){
            for(int j=0;j<n/2;j++){
                //四个角旋转
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n-j-1][i];
                matrix[n-j-1][i] = matrix[n-i-1][n-j-1];
                matrix[n-i-1][n-j-1] = matrix[j][n-i-1];
                matrix[j][n-i-1] = temp;
            }
        }
    }
};

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if(matrix.size()==0) return;
        int n = matrix.size();
        //转置
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
        //行反转
        for(int i=0;i<n;i++){
            for(int j=0;j<n/2;j++){
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][n-j-1];
                matrix[i][n-j-1] = temp;
            }
        }
    }
};