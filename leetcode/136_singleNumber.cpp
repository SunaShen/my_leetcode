// @File   : 136_singleNumber.cpp
// @Source : https://leetcode-cn.com/problems/single-number/
// @Title  : 只出现一次的数字
// @Auther : sun_ds
// @Date   : 2019/12/21

/**  题目描述：
    给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

    说明：

    你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

    示例 1:

    输入: [2,2,1]
    输出: 1
    示例 2:

    输入: [4,1,2,1,2]
    输出: 4

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/single-number
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
 *
 * 1.哈希表map
 *   使用map存储各数字出现的次数
 *   找到只出现一次的数字
 *
 *   时间复杂度O(n) 空间复杂度O(n)
 *
 * 2.集合set
 *   对于序列 [a,a,b,b,c]
 *   c = 2*(a+b+c) - (a+a+b+b+c);
 *   即2*sum(set) - sum(nums)
 *   但求和有溢出的危险!!
 *
 *   时间复杂度O(n)(求和) 空间复杂度O(n)
 *
 * 3.位操作(异或)
 *   利用异或的性质。
 *   a ^ 0 = a;
 *   a ^ a = 0;
 *   满足交换律和结合律
 *   a ^ b ^ a = (a ^ a) ^ b = 0 ^ b = b;
 *
 *   使用0与nums中所有数字异或，最终结果即为只出现一次的元素。
 *
 *   时间复杂度O(n) 空间复杂度O(1)
 *
 */

//hash表
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int,int> m;
        for(auto i:nums){
            m[i]++;
        }
        for(auto iter=m.begin();iter!=m.end();++iter){
            if(iter->second == 1){
                return iter->first;
            }
        }
        return 0;
    }
};
//set
//求和有溢出的危险
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_set<int> s(nums.begin(),nums.end());
        return 2*accumulate(s.begin(),s.end(),0) - accumulate(nums.begin(),nums.end(),0);
    }
};
//位操作(异或)
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(auto i:nums){
            res = res ^ i;
        }
        return res;
    }
};

