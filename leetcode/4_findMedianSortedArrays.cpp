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
 * 2.划分数组
 * 使用 i 将数组 A 划分成两部分 A[0,i-1]和 A[i,m-1]
 * 使用 j 将数组 B 划分成两部分 B[0,j-1]和 B[j,n-1]
 *
 * 将A[0,i-1]和B[0,j-1]组成 left_part
 * 将A[i,m-1]和B[j,n-1]组成 right_part
 *
 * 2.1 若 m+n 为偶数
 *  当 len(left_part) == len(right_part) 且 max(left_part) <= min(right_part) 时。
 *  中位数 = (max(left_part) + min(right_part)) / 2;
 * 2.2 若 m+n 为奇数
 *  当 len(left_part) == len(right_part) + 1 且 max(left_part) <= min(right_part) 时。
 *  中位数 = max(left_part);
 *
 * 其中 i 的取值范围为[0,m], j 的取值范围为[0,n]
 * 保证长度之间的关系。 有 i + j = m - i + n - j 或 i + j = m - i + n - j + 1
 * 统一起来，当 i = [0,m] 时， j 有 j = (i+j+1)/2 - i;
 * 由于 max(left_part) = max(A[i-1],B[j-1]) min(right_part) = min(A[i],B[j])
 * 所以需要有 A[i-1] <= B[j] 且 B[j-1] <= A[i]
 *
 * 问题转换为求满足上述条件的 i 的最大值。
 * 条件简化为A[i-1] <= B[j]。
 * 因为若此时 i 为可取的最大值，则表示 A[i] > B[j]
 * 则有 A[i] > B[j] >= B[j-1].也满足了第二个条件。
 *
 * 使用二分法在[0,m]之间搜索 i 最大的可取位置。
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


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        //保证 nums1 的长度小于 nums2
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size();
        int n = nums2.size();
        int left = 0, right = m, ansi = -1;
        // median1：前一部分的最大值
        // median2：后一部分的最小值
        int median1 = 0, median2 = 0;

        while (left <= right) {
            // 前一部分包含 nums1[0 .. i-1] 和 nums2[0 .. j-1]
            // 后一部分包含 nums1[i .. m-1] 和 nums2[j .. n-1]
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 - i;

            // nums_im1, nums_i, nums_jm1, nums_j 分别表示 nums1[i-1], nums1[i], nums2[j-1], nums2[j]
            int nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);
            int nums_i = (i == m ? INT_MAX : nums1[i]);
            int nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);
            int nums_j = (j == n ? INT_MAX : nums2[j]);

            if (nums_im1 <= nums_j) {
                ansi = i;
                median1 = max(nums_im1, nums_jm1);
                median2 = min(nums_i, nums_j);
                left = i + 1;
            }
            else {
                right = i - 1;
            }
        }

        return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
    }
};

