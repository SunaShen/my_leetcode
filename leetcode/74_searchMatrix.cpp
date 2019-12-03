// @File   : 74_searchMatrix.cpp
// @Source : https://leetcode-cn.com/problems/search-a-2d-matrix/
// @Title  : 搜索二维矩阵
// @Auther : sun_ds
// @Date   : 2019/12/2

/**  题目描述：
    编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

    每行中的整数从左到右按升序排列。
    每行的第一个整数大于前一行的最后一个整数。
    示例 1:

    输入:
    matrix = [
      [1,   3,  5,  7],
      [10, 11, 16, 20],
      [23, 30, 34, 50]
    ]
    target = 3
    输出: true
    示例 2:

    输入:
    matrix = [
      [1,   3,  5,  7],
      [10, 11, 16, 20],
      [23, 30, 34, 50]
    ]
    target = 13
    输出: false

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/search-a-2d-matrix
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 矩阵中查找目标值
 * 该矩阵按升序排列
 *
 * 1.循环找到最后一列中，第一个大于目标值的行。
 * 遍历该行
 * 是否有目标值
 * 2.使用二分查找
 * 将矩阵看成一个一维数组。通过坐标运算取值
 *
 *
 */

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0||matrix[0].size()==0)
            return false;
        int m = matrix.size(), n = matrix[0].size();
        int i=0;
        for(i=0;i<m;++i){
            if(matrix[i][n-1]>target)
                break;
            else if(matrix[i][n-1]==target)
                return true;
        }
        if(i>=m) return false;
        for(int j=0;j<n;++j){
            if(matrix[i][j]==target)
                return true;
        }
        return false;
    }
};


//二分法
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0||matrix[0].size()==0)
            return false;
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = m*n-1;
        while(left<=right){
            int mid = left + (right - left >> 1);
            int val = matrix[mid/n][mid%n];
            if(target==val) return true;
            else{
                if(target>val){
                    left = mid + 1;
                }else{
                    right = mid - 1;
                }
            }
        }
        return false;
    }
};