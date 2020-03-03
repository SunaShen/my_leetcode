// @File   : 496_nextGreaterElement.cpp
// @Source : https://leetcode-cn.com/problems/next-greater-element-i/
// @Title  : 496. 下一个更大元素 I
// @Auther : sun_ds
// @Date   : 2020/3/1

/**  题目描述：
    给定两个没有重复元素的数组 nums1 和 nums2 ，其中nums1 是 nums2 的子集。找到 nums1 中每个元素在 nums2 中的下一个比其大的值。

    nums1 中数字 x 的下一个更大元素是指 x 在 nums2 中对应位置的右边的第一个比 x 大的元素。如果不存在，对应位置输出-1。

    示例 1:

    输入: nums1 = [4,1,2], nums2 = [1,3,4,2].
    输出: [-1,3,-1]
    解释:
        对于num1中的数字4，你无法在第二个数组中找到下一个更大的数字，因此输出 -1。
        对于num1中的数字1，第二个数组中数字1右边的下一个较大数字是 3。
        对于num1中的数字2，第二个数组中没有下一个更大的数字，因此输出 -1。
    示例 2:

    输入: nums1 = [2,4], nums2 = [1,2,3,4].
    输出: [3,-1]
    解释:
        对于num1中的数字2，第二个数组中的下一个较大数字是3。
        对于num1中的数字4，第二个数组中没有下一个更大的数字，因此输出 -1。
    注意:

    nums1和nums2中所有元素是唯一的。
    nums1和nums2 的数组大小都不超过1000。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/next-greater-element-i
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 找到 nums1 中每个元素在 nums2 中的下一个比其大的值。
 *
 * 1.暴力解
 *  先遍历找到nums1中元素在nums2中的位置，然后依次向后比较。若更大则存入vector并继续nums1中的下一个元素。
 *
 * 2.单调栈+map
 * 遍历nums2，构造单调递减栈，当不满足递减规则时，栈内的元素需要出栈，代表该出栈元素第一个右边的更大的值为当前的值。
 * 单调栈中存储的就是元素值。
 * 使用map<int,int>结构存储，各元素与其右边下一个更大的值。
 * 利用构造好的map，遍历nums1，分别检索出nums1中元素的下一个最大的值，将这些值依次存入vector中。
 *
 *
 *
 * 单调栈特性：找到当前值向左或向右的第一个最大或最小值。
 *
 */

//暴力解
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        for(int n: nums1){
            int i = 0;
            while(nums2[i] != n) i++;
            i++;
            for(;i<nums2.size();i++){
                if(nums2[i] > n){
                    res.push_back(nums2[i]);
                    break;
                }
            }
            if(i == nums2.size()) res.push_back(-1);
        }
        return res;
    }
};

//单调栈
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        map<int,int> mp;
        for(int i=0;i<m;++i){
            mp[nums1[i]] = -1;
        }
        stack<int> s;//递减
        for(int i=0;i<n;i++){
            while(!s.empty()&&s.top()<=nums2[i]){
                mp[s.top()] = nums2[i];
                s.pop();
            }
            s.push(nums2[i]);
        }
        vector<int> res;
        for(int i=0;i<m;i++){
            res.push_back(mp[nums1[i]]);
        }
        return res;
    }
};