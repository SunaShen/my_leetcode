// @File   : 240_searchMatrix.cpp
// @Source : https://leetcode-cn.com/problems/search-a-2d-matrix-ii/
// @Title  : 搜索二维矩阵 II
// @Auther : sun_ds
// @Date   : 2019/12/3

/**  题目描述：
    编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：

    每行的元素从左到右升序排列。
    每列的元素从上到下升序排列。
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

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/search-a-2d-matrix-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 查找矩阵中是否存在某数
 * 矩阵中，行列分别升序
 *
 * 1.暴力法
 *  遍历m*n个数，查看是否有与target相等的数
 *  复杂度O(mn)
 * 2.对角线行列二分搜索
 *  沿矩阵对角线分别对行和列进行二分查找目标值
 *  对角线 matrix[i][i]。分别使用二分法搜索该行i后面的和该列i后面的数。
 *  其中i = min(col,row)
 *  复杂度O(lg(n!))
 * 3.递归法 划分成四个格子
 *  当前矩阵，列数取中间，mid = (left + right) / 2
 *  以mid列，从第一行到最后一行，遍历，找到第一个大于target的位置的行row。以该位置划分四个新的矩阵。
 *  其中，有矩阵排列规则知道， 左上矩阵所有数小于target，右下矩阵所有数大于target
 *  因此，递归搜索，左下和右上。
 *  结束条件。左右或者上下边界交叉、当前矩阵左上角(矩阵中最小值)大于target、当前矩阵右上角(矩阵中最大值)小于target。
 *
 * 4.副对角线
 * 对于矩阵的左上角或者是右下角，如果目标值target比左上角的某个元素大，则它可以在右侧，也可以在下侧，判断不了它的位置，
 * 同理，对于右下角的元素，如果目标值比它小，则可以在左侧，也可以在上侧，
 * 但是如果每一次比较的是右上角或者左下角的元素
 * 如果目标值比右上角的元素大，则右上角的这一行都可以排除，如果比右上角的元素小，则右上角的这一列都可以排除
 * 同理，对于左下角，如果目标值比左下角的元素大，则左下角的这一列排除，相反，左下角的这一行排除，这样每次排除一列或者一行，就可以完成对目标值的检索。
 *
 * 复杂度O(m+n)
 *
 */


//对角线行列二分搜索
//复杂度 O(lg(n!))
//会超时。
class Solution {
public:
    bool binarySearch(vector<vector<int>> mat,int target,int start,bool flag){
        int s = start;
        int e = flag ? mat.size() -1 : mat[0].size() - 1;
        while(s<=e){
            int mid = s + (e - s >> 1);
            if(flag){
                if(mat[mid][start] < target){
                    s = mid + 1;
                }else if(mat[mid][start] > target){
                    e = mid - 1;
                }else{
                    return true;
                }
            }else{
                if(mat[start][mid] < target){
                    s = mid + 1;
                }else if(mat[start][mid] > target){
                    e = mid - 1;
                }else{
                    return true;
                }
            }
        }
        return false;
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0||matrix[0].size()==0) return false;
        int m = matrix.size(),n = matrix[0].size();
        for(int i=0;i<min(m,n);++i){
            if(binarySearch(matrix,target,i,true)) return true;
            if(binarySearch(matrix,target,i,false)) return true;
        }
        return false;
    }
};

//递归
//田字格？
//超内存
class Solution {
public:
    vector<vector<int>> mat;
    int tar;
    bool search(int left, int up, int right, int down){
        if(left>right||up>down) return false;
        else if(mat[up][left] > tar || mat[down][right] < tar) return false;

        int mid = left + (right - left >> 1);
        int row = up;
        while(row<=down&&mat[row][mid]<=tar){
            if(mat[row][mid] == tar) return true;
            ++row;
        }
        return search(left,row,mid - 1, down) || search(mid + 1,up,right,row - 1);
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0||matrix[0].size()==0) return false;
        int m = matrix.size(),n = matrix[0].size();
        mat = matrix;
        tar = target;
        return search(0,0,n - 1,m - 1);
    }
};


//左下角到右上角
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0||matrix[0].size()==0) return false;
        int m = matrix.size(),n = matrix[0].size();
        int col = 0, row = m-1;
        while(row>=0&&col<=n-1){
            if(matrix[row][col] > target){
                --row;
            }else if(matrix[row][col] < target){
                ++col;
            }else{
                return true;
            }
        }
        return false;
    }
};