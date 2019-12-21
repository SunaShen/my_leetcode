// @File   : 137_singleNumber.cpp
// @Source : https://leetcode-cn.com/problems/single-number-ii/
// @Title  : 只出现一次的数字 II
// @Auther : sun_ds
// @Date   : 2019/12/21

/**  题目描述：
    给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。

    说明：

    你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

    示例 1:

    输入: [2,2,3,2]
    输出: 3
    示例 2:

    输入: [0,1,0,1,0,1,99]
    输出: 99

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/single-number-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。
 *
 * 1.哈希表map
 *   使用map存储各数字出现的次数
 *   找到只出现一次的数字
 *
 *   时间复杂度O(n) 空间复杂度O(n)
 *
 * 2.位操作 模拟三进制加法(不包含进位)
 *   需要在136题中进行改进。
 *   136中，将各个数看做2进制形式，执行异或操作。利用异或特性，两两相消(两个1变0)，即为二进制加法(不包含进位)
 *   本题目中，三个相同的数字出现需要清零。即三个相消(三个1变0)，即为三进制加法(不包含进位)
 *   最终的数即为单独的数字。
 *
 *   需要定义三个变量。one,two,three。
 *   one: one中位为1代表，当前位置出现1的次数为1或3
 *   one = one ^ nums; 与136中一样。
 *   two: two中位为1代表，当前位置出现1的次数2次
 *   two |= one & nums; 记录进位。即当前one位为1，新数该位也为1.
 *   three: three中位为1代表，当前位置出现1的次数3次
 *   three = one & two; one中和two中对应位置都为1，则代表出现了三次。
 *
 *   出现了3次的需要清零。清零one和two的对应位置。重新计数循环。
 *   one &= ~three;
 *   two &= ~three;
 *
 *   最终得到的one即为单独的数字。
 *
 *   时间复杂度O(n) 空间复杂度O(1)
 *
 *   疯狂数电知识。
 */

//map
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

//位操作
//模拟三进制不包含进位的加法
//消消乐?三个清零。
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one = 0, two = 0, three = 0;
        for(auto i:nums){
            two |= one & i;
            one ^= i;
            three = one & two;
            one &= ~three;
            two &= ~three;
        }
        return one;
    }
};