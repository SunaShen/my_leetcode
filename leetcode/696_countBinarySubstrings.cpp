// @File   : 696_countBinarySubstrings.cpp
// @Source : https://leetcode-cn.com/problems/count-binary-substrings/
// @Title  : 696. 计数二进制子串
// @Auther : sun_ds
// @Date   : 2020/8/10

/**  题目描述：
    给定一个字符串 s，计算具有相同数量0和1的非空(连续)子字符串的数量，并且这些子字符串中的所有0和所有1都是组合在一起的。

    重复出现的子串要计算它们出现的次数。

    示例 1 :

    输入: "00110011"
    输出: 6
    解释: 有6个子串具有相同数量的连续1和0：“0011”，“01”，“1100”，“10”，“0011” 和 “01”。

    请注意，一些重复出现的子串要计算它们出现的次数。

    另外，“00110011”不是有效的子串，因为所有的0（和1）没有组合在一起。
    示例 2 :

    输入: "10101"
    输出: 4
    解释: 有4个子串：“10”，“01”，“10”，“01”，它们具有相同数量的连续1和0。
    注意：

    s.length 在1到50,000之间。
    s 只包含“0”或“1”字符。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/count-binary-substrings
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 中心扩散
 *  以每一个 01 相间的位置为中心点，从当前中心点向两边扩散。
 *  统计子串个数
 *
 *  时间复杂度 O(N^2)
 *  空间复杂度 O(1)
 *
 * 2. 分组计数
 *  将连续的 0 和 1 记为一组。
 *  得到保存各个分组的长度。
 *  则没两个连续的分组所能组成的满足要求的子串个数为 min(nums[i-1],nums[i])
 *
 *  由于每次只用到 当前nums[i]和前一个 nums[i-1]
 *  因此合并两次遍历，使用 last 代替nums[i-1]
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(1)
 *
 */


// 中心扩散
class Solution {
public:
    int countBinarySubstrings(string s) {
        int n = s.size();
        int res = 0;
        for (int i=0; i<n-1; i++) {
            if (s[i] != s[i+1]) {
                res++;
                int l = i-1;
                int r = i+2;
                while(l >= 0 && r < n && s[l] == s[i] && s[r] == s[i+1]){
                    res++;
                    l--;
                    r++;
                }
            }
        }
        return res;
    }
};

// 分组统计
class Solution {
public:
    int countBinarySubstrings(string s) {
        int n = s.size();
        int res = 0;
        int index = 0, last = 0;
        while (index < s.size()) {
            char temp = s[index];
            int count = 0;
            while (s[index] == temp) {
                count++;
                index++;
            }
            res += min(last, count);
            last = count;
        }
        return res;
    }
};