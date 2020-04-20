// @File   : 4_findMedianSortedArrays.cpp
// @Source : https://leetcode-cn.com/problems/median-of-two-sorted-arrays/
// @Title  : 4. 寻找两个有序数组的中位数
// @Auther : sun_ds
// @Date   : 2020/3/26

/**  题目描述：
    给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。

    请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

    你可以假设 nums1 和 nums2 不会同时为空。

    示例 1:

    nums1 = [1, 3]
    nums2 = [2]

    则中位数是 2.0
    示例 2:

    nums1 = [1, 2]
    nums2 = [3, 4]

    则中位数是 (2 + 3)/2 = 2.5

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.二分法
 * 假设中位数为第k个数
 * 二分法每次排除k/2个数。
 * 分别比较两个序列的 nums1[min(len1,k/2)]和nums2[min(len2,k/2)]的大小
 * 小的值的前k/2个数可以不用考虑了
 *
 *
 *  nums1 = [1,3,4,9]
 *  nums2 = [1,2,3,4,5,6,7,8,9,10]
 *
 * 假设我们要找第 7 小的数字
 * 我们比较两个数组的第 k/2 个数字，如果 k 是奇数，向下取整。也就是比较第 3 个数字，上边数组中的 4 和下边数组中的3，如果哪个小，就表明该数组的前 k/2 个数字都不是第 k 小数字，所以可以排除。
 * 也就是 1，2，3 这三个数字不可能是第 7 小的数字，我们可以把它排除掉。将 1349 和 45678910 两个数组作为新的数组进行比较。
 * 更一般的情况 A[1] ，A[2] ，A[3]，A[k/2] ... ，B[1]，B[2]，B[3]，B[k/2] ... ，如果 A[k/2]<B[k/2] ，那么A[1]，A[2]，A[3]，A[k/2]都不可能是第 k 小的数字。
 * A 数组中比 A[k/2] 小的数有 k/2-1 个，B 数组中，B[k/2] 比 A[k/2] 小，假设 B[k/2] 前边的数字都比 A[k/2] 小，也只有 k/2-1 个，所以比 A[k/2] 小的数字最多有 k/2-1+k/2-1=k-2个，所以 A[k/2] 最多是第 k-1 小的数。而比 A[k/2] 小的数更不可能是第 k 小的数了，所以可以把它们排除
 *
 * 作者：windliang
 * 链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-2/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 *
 *
 *
 */


class Solution {
public:
    int func(vector<int>& nums1,int start1,int end1,vector<int>& nums2,int start2,int end2,int k){
        int len1 = end1 - start1 + 1;
        int len2 = end2 - start2 + 1;

        //使得1的长度小于2，方便处理
        if(len1>len2) return func(nums2,start2,end2,nums1,start1,end1,k);
        if(len1==0) return nums2[start2+k-1];
        if(k==1) return min(nums1[start1],nums2[start2]);

        int i = start1 + min(len1,k/2) - 1;
        int j = start2 + min(len2,k/2) - 1;

        if(nums1[i] > nums2[j]){
            return func(nums1,start1,end1,nums2,j+1,end2,k - (j - start2 + 1));
        }else{
            return func(nums1,i+1,end1,nums2,start2,end2,k - (i - start1 + 1));
        }
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int l1 = nums1.size(), l2 = nums2.size();
        int left = (l1+l2+1)/2;
        int right = (l1+l2+2)/2;
        //奇数偶数放一起处理
        return (func(nums1,0,l1-1,nums2,0,l2-1,left)+func(nums1,0,l1-1,nums2,0,l2-1,right))*0.5;
    }
};


