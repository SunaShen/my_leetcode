// @File   : 73_setZeroes.cpp
// @Source : https://leetcode-cn.com/problems/set-matrix-zeroes/
// @Title  : 矩阵置零
// @Auther : sun_ds
// @Date   : 2019/11/28

/**  题目描述：
    给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用原地算法。

    示例 1:

    输入:
    [
      [1,1,1],
      [1,0,1],
      [1,1,1]
    ]
    输出:
    [
      [1,0,1],
      [0,0,0],
      [1,0,1]
    ]
    示例 2:

    输入:
    [
      [0,1,2,0],
      [3,4,5,2],
      [1,3,1,5]
    ]
    输出:
    [
      [0,0,0,0],
      [0,4,5,0],
      [0,3,1,0]
    ]
    进阶:

    一个直接的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
    一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
    你能想出一个常数空间的解决方案吗？


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/set-matrix-zeroes
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用原地算法。
 *
 * 1.使用额外空间
 *   遍历，记录每个0元素的行列
 *   再遍历，判断在该行或该列上的元素置零
 *
 *   时间复杂度O(M*N) 空间复杂度O(M+N)
 *
 * 2.使用自身第一行列记录，不使用额外空间
 *   借助M*N矩阵的第一行和第一列存储该行列是否有零元素(该行列是否该清零)
 *   一共需要存储M+N个行列，但第一行+第一列只有M+N-1个元素,(0,0)即在行又在列。
 *   所以需要一个额外的元素记录
 *
 *   将(0,0)记录第0行，第一列使用iscol记录
 *   使用for循环遍历所有元素。
 *   for i = 0:m-1
 *      判断(i,0) 第i行第一列对否为0，iscol记录
 *      for j = 1:m-1
 *      第一列判断过，从1开始遍历
 *      若(i,j) = 0
 *      则使 (i,0)和(0,j)为0，记录
 *
 *      此时(0,0)代表第0行
 *
 *   遍历，以第一行和第一列的记录，修改矩阵
 *   注意遍历都是从1开始，不是0.
 *
 *   单独判断第一行和第一列是否需要置零。
 *   若(0,0) = 0则第一行为0
 *   若iscol= true则第一列为0
 *
 *   时间复杂度O(M*N)
 *   空间复杂度O(1)
 *
 *  3.使用标记值，不使用额外空间
 *  遍历矩阵并将(i,j)=0的i行和j列中非0元素修改为标记值
 *
 *  遍历，将标记值改为0
 *
 *  对于c++这种，强类型，需要能够找一个矩阵中未出现的元素来充当标记值，这个是没有严格保证的。
 *
 *  时间复杂度O(M*N*(M+N)) 空间复杂度O(1)
 *
 *
 *
 *
 */

//使用额外空间
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if(matrix.size()==0||matrix[0].size()==0) return;
        int m = matrix.size(), n = matrix[0].size();
        set<int> col,row;
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(matrix[i][j]==0){
                    row.insert(i);
                    col.insert(j);
                }
            }
        }
        for(auto i:row){
            for(int j=0;j<n;++j){
                matrix[i][j] = 0;
            }
        }
        for(auto j:col){
            for(int i=0;i<m;++i){
                matrix[i][j] = 0;
            }
        }
    }
};

//不使用额外空间
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if(matrix.size()==0||matrix[0].size()==0) return;
        int m = matrix.size(), n = matrix[0].size();
        bool iscol = false;
        for(int i=0;i<m;++i){
            if(matrix[i][0]==0){
                iscol = true;
            }
            //注意，j从1开始。即(0,0)让给了0行。而0列使用iscol记录
            for(int j=1;j<n;++j){
                if(matrix[i][j]==0){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for(int i=1;i<m;++i){
            for(int j=1;j<n;++j){
                if(matrix[i][0]==0||matrix[0][j]==0){
                    matrix[i][j] = 0;
                }
            }
        }
        if(matrix[0][0] == 0){
            for(int j=0;j<n;++j){
                matrix[0][j] = 0;
            }
        }
        if(iscol){
            for(int i=0;i<m;++i){
                matrix[i][0] = 0;
            }
        }

    }
};