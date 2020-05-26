// @File   : 287_findDuplicate.cpp
// @Source : https://leetcode-cn.com/problems/find-the-duplicate-number/
// @Title  : 287. 寻找重复数
// @Auther : sun_ds
// @Date   : 2020/5/26

/**  题目描述：
    给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。假设只有一个重复的整数，找出这个重复的数。

    示例 1:

    输入: [1,3,4,2,2]
    输出: 2
    示例 2:

    输入: [3,1,3,4,2]
    输出: 3
    说明：

    不能更改原数组（假设数组是只读的）。
    只能使用额外的 O(1) 的空间。
    时间复杂度小于 O(n2) 。
    数组中只有一个重复的数字，但它可能不止重复出现一次。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/find-the-duplicate-number
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.改变原数组的元素
 * 元素范围 1-n 位置时 0-n 足够放的下每个元素。
 * 目的是将各个元素放到对应的位置上去，满足 nums[i] = i+1
 * 遍历，若不满足条件，则判断应该放置的位置是否满足条件，若满足条件，则说明已经有该元素，直接返回。否则将该数字放到正确的位置。
 * 时间复杂度 O(N)
 * 空间复杂度 O(1)
 * 但是改变了原数组的元素,不符合要求.
 *
 * 2.二分法
 * l=1,r=n 使用二分法搜索重复的元素.
 * 每次得到 mid 这个候选值就遍历数组,看有多少个元素小于等于 mid.
 * 若个数小于等于(其中小于出现在一个元素重复多次占用其他元素的情况) mid,是正常的,说明 mid 之前都没有重复元素,重复元素应该在后半段.
 * 否则,若大于 mid, 则表示重复元素就在前半段。
 * 最终得到结果。
 *
 * 时间复杂度 O(Nlog(N))
 * 空间复杂度 O(1)
 *
 * 使用时间换空间。在每次二分循环中都要遍历整个数组。
 *
 *
 * 3.快慢指针
 * 将数组当做链表。即当前 i 位置，下一次要去的位置为 nums[i].
 * 由于有重复数字，所以总会遇到情况，两个指针需要到同一位置去，此时该位置就是重复的元素。
 *
 * 即等效于环形链表找入口
 *
 * 时间复杂度O(N)
 * 空间复杂度O(1)
 *
 *
 *
 */


//改变了原数组的元素
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int i=0;
        while(i<nums.size()){
            if(nums[i]!=i+1){
                if(nums[nums[i]-1] == nums[i]){
                    return nums[i];
                }else{
                    swap(nums[i],nums[nums[i]-1]);
                }
            }else{
                i++;
            }
        }
        return -1;
    }
};


//二分查找 时间换空间
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int l = 1, r = nums.size()-1;
        //搜索范围 1-n 其中 nums.size() 是等于 n+1 的
        while(l<r){
            int mid = l + ((r - l)>>1);
            int cnt = 0;
            //统计小于等于 mid 的值的个数。
            //如果个数等于 mid，表示重复的值在右半部分，否则在左半部分。
            for(auto i:nums){
                if(i<=mid) cnt++;
            }
            if(cnt > mid){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        return l;
    }
};

//快慢指针
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        //有重复值表示肯定有环
        //有重复值肯定会相遇
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        //找环的入口
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
