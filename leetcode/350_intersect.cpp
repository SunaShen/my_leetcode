// @File   : 350_intersect.cpp
// @Source : https://leetcode-cn.com/problems/intersection-of-two-arrays-ii/
// @Title  : 350. 两个数组的交集 II
// @Auther : sun_ds
// @Date   : 2020/7/13

/**  题目描述：
    给定两个数组，编写一个函数来计算它们的交集。

     

    示例 1：

    输入：nums1 = [1,2,2,1], nums2 = [2,2]
    输出：[2,2]
    示例 2:

    输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
    输出：[4,9]
     

    说明：

    输出结果中每个元素出现的次数，应与元素在两个数组中出现次数的最小值一致。
    我们可以不考虑输出结果的顺序。
    进阶：

    如果给定的数组已经排好序呢？你将如何优化你的算法？
    如果 nums1 的大小比 nums2 小很多，哪种方法更优？
    如果 nums2 的元素存储在磁盘上，磁盘内存是有限的，并且你不能一次加载所有的元素到内存中，你该怎么办？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/intersection-of-two-arrays-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.哈希
 * 使用 map 存储第一个数组的各个数字出现的次数
 * 遍历第二个数组，若 map 中有与之对应的数字，则加入结果，并在 map 中减一。
 * 最终得到结果。
 *
 * 使用较短的做哈希，减少空间复杂度
 * 时间复杂度 O(M+N)
 * 空间复杂度 O(min(M,N))
 *
 * 2.排序+双指针
 * 将两个数组排序，然后双指针进行比较
 * 若当前两个元素相等，同时向后一位，加入结果。
 * 若不相等，小的数后移一位。
 * 若移到末尾则结束。
 *
 * 时间复杂度 O(MlogM + NlogN)
 * 空间复杂度 O(1)
 *
 *
 */

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size()){
            return intersect(nums2, nums1);
        }
        unordered_map<int,int> m1;
        vector<int> res;
        for(auto i:nums1) m1[i]++;
        for(auto i:nums2){
            if(m1.count(i) != 0 && m1[i] != 0){
                m1[i]--;
                res.push_back(i);
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int length1 = nums1.size(), length2 = nums2.size();
        vector<int> res;
        int index1 = 0, index2 = 0;
        while (index1 < length1 && index2 < length2) {
            if (nums1[index1] < nums2[index2]) {
                index1++;
            } else if (nums1[index1] > nums2[index2]) {
                index2++;
            } else {
                res.push_back(nums1[index1]);
                index1++;
                index2++;
            }
        }
        return res;
    }
};

