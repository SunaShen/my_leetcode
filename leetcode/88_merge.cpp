// @File   : 88_merge.cpp
// @Source : https://leetcode-cn.com/problems/merge-sorted-array/
// @Title  : 合并两个有序数组
// @Auther : sun_ds
// @Date   : 2019/12/17

/**  题目描述：
    给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。

    说明:

    初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
    你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
    示例:

    输入:
    nums1 = [1,2,3,0,0,0], m = 3
    nums2 = [2,5,6],       n = 3

    输出: [1,2,2,3,5,6]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/merge-sorted-array
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 合并两个有序数组
 *
 * 1.先合并后整体排序
 *
 * 2.双指针，从前往后。
 * 使用两个指针,i,j分别指向两数组的头部，比较nums1[i],nums2[j]。将小的值写入nums1[i+j]中(nums1正序写入)。
 * 注意可能会覆盖nums1中的为并入的数据，因此，先保存nums1的数据。
 * 为节省空间，使用nums1后半部分存储前半部分的值。
 *
 * 3.双指针，从后往前。
 * 使用两个指针,i,j分别指向两数组的尾部，比较nums1[i],nums2[j]。将大的值写入nums1[i+j-1]中(nums1倒序写入)。
 * 从后往前，不需要考虑合并值覆盖为合并的nums1的值。
 *
 */

//双指针，从前往后
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(int i=m+n-1;i>=n;--i){
            nums1[i] = nums1[i-n];
        }
        int i=0;
        int j=0;
        while(j<n&&i<m){
            if(nums1[n+i]<=nums2[j]){
                nums1[i+j] = nums1[n+i];
                ++i;
            }else{
                nums1[i+j] = nums2[j];
                ++j;
            }
        }
        for(;j<n;++j){
            nums1[i+j] = nums2[j];
        }
    }
};

//双指针，从后往前
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=m-1;
        int j=n-1;
        while(j>=0&&i>=0){
            if(nums1[i]>=nums2[j]){
                nums1[i+j+1] = nums1[i];
                --i;
            }else{
                nums1[i+j+1] = nums2[j];
                --j;
            }
        }
        for(;j>=0;--j){
            nums1[i+j+1] = nums2[j];
        }
    }
};