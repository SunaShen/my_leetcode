// @File   : 977_sortedSquares.cpp
// @Source : https://leetcode-cn.com/problems/squares-of-a-sorted-array/
// @Title  : 977. 有序数组的平方
// @Auther : sun_ds
// @Date   : 2020/10/16

/**  题目描述：
    给定一个按非递减顺序排序的整数数组 A，返回每个数字的平方组成的新数组，要求也按非递减顺序排序。

     

    示例 1：

    输入：[-4,-1,0,3,10]
    输出：[0,1,9,16,100]
    示例 2：

    输入：[-7,-3,2,3,11]
    输出：[4,9,9,49,121]
     

    提示：

    1 <= A.length <= 10000
    -10000 <= A[i] <= 10000
    A 已按非递减顺序排序。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/squares-of-a-sorted-array
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 双指针
 *  A 数组有序排列
 *  分别计算数组两端的平方和，大的值首先放到结果的末尾。
 *  继续向中间靠拢。
 *  若 A 数组中全是正数或负数，朝一个方向遍历。
 *  若 A 数组中有正有负，双指针向中间靠拢至 0 附近。
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(1)
 *
 */

class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        int n = A.size();
        vector<int> res(n, 0);
        int l = 0, r = n - 1, pos = n - 1;
        while(l <= r){
            if(A[l] * A[l] > A[r] * A[r]){
                res[pos] = A[l] * A[l];
                l++;
            }else{
                res[pos] = A[r] * A[r];
                r--;
            }
            pos--;
        }
        return res;
    }
};