// @File   : 260_singleNumber.cpp
// @Source : https://leetcode-cn.com/problems/single-number-iii/solution/
// @Title  : 只出现一次的数字 III
// @Auther : sun_ds
// @Date   : 2019/12/21

/**  题目描述：
    给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。

    示例 :

    输入: [1,2,1,3,2,5]
    输出: [3,5]
    注意：

    结果输出的顺序并不重要，对于上面的例子， [5, 3] 也是正确答案。
    你的算法应该具有线性时间复杂度。你能否仅使用常数空间复杂度来实现？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/single-number-iii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。
 *
 * 1.哈希表
 *   使用map存储各数字出现的次数
 *   找到两个只出现一次的数字
 *
 *   时间复杂度O(n) 空间复杂度O(n)
 *
 * 2.位操作
 *   与163一样，遍历执行res = res ^ nums;
 *   最终得到res = a ^ b;
 *   需要分别得到a和b;
 *   已知a!=b; res中各位也反映a和b在哪些位上不同(res中位为1的表示不同).
 *
 *   取res中的一个位为1，其他的都为0，设为flag(flag二进制中只有一个1)作为分类标准。
 *
 *   使用nums & flag =？flag将nums分为两类。
 *   第一类:一对一对的值和a;第二类一对一对的值和b;
 *   对这两类执行163程序。即全部异或。即两列分别得a和b(一对一对的值抵消了)。
 *
 */

//hash表
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int,int> m;
        for(auto i:nums){
            m[i]++;
        }
        vector<int> ans;
        for(auto iter=m.begin();iter!=m.end();++iter){
            if(iter->second == 1){
                ans.push_back(iter->first);
            }
        }
        return ans;
    }
};

//位操作
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int res = 0;
        for(auto i:nums){
            res = res ^ i;
        }
        //flag是res保留最右边的一个1其他都为0.
        //flag二进制中只有一个1.
        //不一定要是最右边。a!=b。res中为1的位都是不同的。用于分类。分两类。
        //第一类:一对一对的值和a;第二类一对一对的值和b;
        //对这两类执行163程序。即全部异或。即两列分别得a和b(一对一对的值抵消了)。
        int flag = res & -res;
        int a = 0, b = 0;
        for(auto i:nums){
            if((i & flag) == flag){
                a ^= i;
            }else{
                b ^= i;
            }
        }
        return {a,b};
    }
};


