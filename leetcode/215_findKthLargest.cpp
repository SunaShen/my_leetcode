// @File   : 215_findKthLargest.cpp
// @Source : https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
// @Title  : 数组中的第K个最大元素
// @Auther : sun_ds
// @Date   : 2019/12/13

/**  题目描述：
    在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

    示例 1:

    输入: [3,2,1,5,6,4] 和 k = 2
    输出: 5
    示例 2:

    输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
    输出: 4
    说明:

    你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/kth-largest-element-in-an-array
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 数组中第K大的元素
 *
 * 1.暴力法
 *  排序
 *  取第k大元素
 *  复杂度 O(NlogN)
 *
 * 2.最小堆
 *  将各元素依次加入堆中，并保持堆的大小小于等于k。
 *  执行完后，堆顶即为第k大的数，其他数都比是比堆顶大的k-1个数。
 *
 *  复杂度O(Nlogk)
 *
 * 3.快排思想
 *  选取中枢值，将小于该数的值都放置其左边，大于该数的值都放置其右边。
 *  中枢值的位置p就表示他是第p小的元素。
 *  若p等于目标值，则找到该值，返回
 *  若p大于目标值，递归继续搜索前半部分。
 *  若p小于目标值，递归继续搜索后半部分。
 *
 *  第k大值和第k小可以相互转换
 *
 *  复杂度O(N)
 *
 *
 */

class Solution {
public:
//    int partition(vector<int>& num, int l, int r){
//        int x = num[r];
//        int i=l;
//        for(int j=l;j<r;++j){
//            if(num[j]<=x){
//                swap(num[i],num[j]);
//                ++i;
//            }
//        }
//        swap(num[i],num[r]);
//        return i;
//    }
    int partition(vector<int>& num, int l, int r){
        int i=l,j=r+1;
        int x = num[i];
        while(true){
            while((++i)<=r&&num[i]<x);
            while(num[--j]>x);
            if(i>=j) break;
            swap(num[i],num[j]);
        }
        num[l] = num[j];
        num[j] = x;
        return j;
    }
    int search(vector<int>& num, int l, int r, int k){
        if(l==r) return num[l];
        int q = partition(num,l,r);
        int k1 = q-l+1;
        if(k==k1) return num[q];
        else if(k<k1) return search(num,l,q-1,k);
        else return search(num,q+1,r,k-k1);
    }
    int findKthLargest(vector<int>& nums, int k) {
        return search(nums,0,nums.size()-1,nums.size() - k + 1);
    }
};
