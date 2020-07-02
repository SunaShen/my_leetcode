// @File   : 378_kthSmallest.cpp
// @Source : https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/
// @Title  : 378. 有序矩阵中第K小的元素
// @Auther : sun_ds
// @Date   : 2020/7/2

/**  题目描述：
    给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，找到矩阵中第 k 小的元素。
    请注意，它是排序后的第 k 小元素，而不是第 k 个不同的元素。

     

    示例：

    matrix = [
       [ 1,  5,  9],
       [10, 11, 13],
       [12, 13, 15]
    ],
    k = 8,

    返回 13。
     

    提示：
    你可以假设 k 的值永远是有效的，1 ≤ k ≤ n2 。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.优先队列
 * 将每一行/每一列看做有序的，顺序合并
 * 类似 k 个有序链表合并。
 * 但是每次需要保存值和坐标 x,y.
 * 小顶堆。
 *
 * 2.二分法
 * 每个元素左上角部分小于自己，右下角部分大于自己。
 * matrix[0][0]为最小值，matrix[n-1][n-1]为最大值。
 * 二分法在 matrix[0][0] ~ matrix[n-1][n-1] 之间搜索。
 * 设置 mid。左下到右上分界线，左上部分都是小于 mid 的。统计小于等于 mid 的值的个数。
 * 若小于等于 mid 的值的个数大于等于 k ,说明 mid  = [第k小，第k+1小);
 * 此时，r = mid; 只要等于 k， 右边就一直收缩。
 * 而若小于等于 mid 的值的个数小于 k，说明当前 mid 肯定不是第 k 小，l=mid+1。
 * 只要等于 k 了左边就不动了。
 * 所以最终 r == l == 第 k 小。
 *
 */

class point{
public:
    int val,x,y;
    point(int _val, int _x, int _y):val(_val),x(_x),y(_y){}
    bool operator > (const point& rhs) const {
        return this->val > rhs.val;
    }
};
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<point,vector<point>,greater<point>> q;
        int m = matrix.size();
        for(int i=0;i<m;i++){
            q.push(point(matrix[i][0],i,0));
        }
        for(int i=0;i<k-1;i++){
            point temp = q.top();
            q.pop();
            if(temp.y < m - 1){
                q.push(point(matrix[temp.x][temp.y+1],temp.x,temp.y+1));
            }
        }
        return q.top().val;
    }
};

class Solution {
public:
    int func(vector<vector<int>>& matrix,int mid){
        int i=matrix.size()-1;
        int j=0;
        int res=0; //小于等于 mid 的个数
        while(i>=0&&j<matrix.size()){
            if(matrix[i][j] <= mid){
                res += i+1;
                j++;
            }else{
                i--;
            }
        }
        return res;
    }
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int l = matrix[0][0];
        int r = matrix[m-1][m-1];
        while(l<r){
            int mid = l + ((r - l) >> 1);
            if(func(matrix,mid) >= k){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        //保证 l 必定是矩阵中的数
        //类似有序数组中找第一个等于 k 的值的解法
        return l;
    }
};


