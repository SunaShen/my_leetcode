// @File   : 48_rotate.cpp
// @Source : https://leetcode-cn.com/problems/rotate-image/
// @Title  : 旋转图像
// @Auther : sun_ds
// @Date   : 2019/11/20

/**  题目描述：
    给定一个 n × n 的二维矩阵表示一个图像。

    将图像顺时针旋转 90 度。

    说明：

    你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。

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
    链接：https://leetcode-cn.com/problems/rotate-image
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/** 顺时针旋转矩阵90度
 *
 *  找规律题
 *
 * 1.转置+反转
 *   转置+反转 = 矩阵顺时针旋转90度
 *   反转+转置 = 矩阵逆时针旋转90度
 *
 * 2.4个数一组。共((n+1)/2) * (n/2)组 左上角。
 *   以四个角为例。旋转90度。
 *   当前点列数->旋转后行数
 *   旋转后列数=n-1-当前点行数
 *
 *   以此以左上角((n+1)/2) * (n/2)个点为起始点，执行旋转。
 *
 *   注意为(n+1)/2,而不是n/2.
 *   当n为偶数时，没有区别。但当n为奇数时，n/2就少遍历了中心点左边的数字。
 *
 *
 *
 */

//转置+反转
//4ms
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if(matrix.size()==0||matrix.size()!=matrix[0].size()) return;
        int n = matrix.size();
        //转置
        for(int i=0;i<n;++i){
            for(int j=i;j<n;++j){
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
        //反转
        for(int i=0;i<n;++i){
            for(int j=0;j<n/2;j++){
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][n - 1 - j];
                matrix[i][n - 1 - j] = temp;
            }
        }
    }
};


//四个数一组，旋转。
//8ms
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if(matrix.size()==0||matrix.size()!=matrix[0].size()) return;
        int n = matrix.size();
        for(int i=0;i<(n+1)/2;++i){
            for(int j=0;j<n/2;++j){
                int temp = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - j - 1];
                matrix[n - 1 - i][n - j - 1] = matrix[j][n - 1 -i];
                matrix[j][n - 1 - i] = matrix[i][j];
                matrix[i][j] = temp;
//                int row = i, col = j;
//                int tmp[4] = {0};
//                for(int k=0;k<4;++k){
//                    tmp[k] = matrix[row][col];
//                    int t = row;
//                    row = col;
//                    col = n - 1 -t;
//                }
//                for(int k=0;k<4;++k){
//                    matrix[row][col] = tmp[(k+3)%4];
//                    int t = row;
//                    row = col;
//                    col = n - 1 - t;
//                }
            }
        }
    }
};
