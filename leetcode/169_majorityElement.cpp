// @File   : 169_majorityElement.cpp
// @Source : https://leetcode-cn.com/problems/majority-element/
// @Title  : 求众数
// @Auther : sun_ds
// @Date   : 2019/9/4

/*  题目描述：
    给定一个大小为 n 的数组，找到其中的众数。众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

    你可以假设数组是非空的，并且给定的数组总是存在众数。

    示例 1:

    输入: [3,2,3]
    输出: 3
    示例 2:

    输入: [2,2,1,1,1,2,2]
    输出: 2

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/majority-element
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/



/*
 *  求众数，个数大于n/2的数。
 *
 *  万能map，统计个数。
 *  map速度优于unordered_map。
 *
 *
 *  排序：
 *  排序取中间，索引n/2即为众数
 *
 *
 *  投票法：(贪心?)
 *  第一个当做众数，作为候选，后面与候选相同计数count加1否则减1.
 *  如count为0，当前值当做众数，作为候选。输出候选即为众数
 *
 */


#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;



//40ms

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> count;
        for(int i=0; i<nums.size(); i++)
        {
            if(++count[nums[i]]>nums.size()/2)
                return nums[i];
        }
        return INT_MIN;
    }
};


//精选题解
//O(n),贪心？

//class Solution {
//public:
//    int majorityElement(vector<int>& nums) {
//        int count = 0;
//        int candidate;
//        for(int i=0; i<nums.size(); i++)
//        {
//            if(count==0)
//                candidate = nums[i];
//            count += nums[i]==candidate ? 1:-1;
//        }
//        return candidate;
//    }
//};



int main()
{
    vector<int> nums = {1,2,3,2,2,1,3,2,2};

    Solution su;
    auto res = su.majorityElement(nums);

    cout << res << endl;

    cout << "finish" << endl;
    return 0;
}
