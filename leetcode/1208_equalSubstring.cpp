// @File   : 1208_equalSubstring.cpp
// @Source : https://leetcode-cn.com/problems/get-equal-substrings-within-budget/
// @Title  : 尽可能使字符串相等
// @Auther : sun_ds
// @Date   : 2019/10/17

/*  题目描述：
    给你两个长度相同的字符串，s 和 t。

    将 s 中的第 i 个字符变到 t 中的第 i 个字符需要 |s[i] - t[i]| 的开销（开销可能为 0），也就是两个字符的 ASCII 码值的差的绝对值。

    用于变更字符串的最大预算是 maxCost。在转化字符串时，总开销应当小于等于该预算，这也意味着字符串的转化可能是不完全的。

    如果你可以将 s 的子字符串转化为它在 t 中对应的子字符串，则返回可以转化的最大长度。

    如果 s 中没有子字符串可以转化成 t 中对应的子字符串，则返回 0。

     

    示例 1：

    输入：s = "abcd", t = "bcdf", cost = 3
    输出：3
    解释：s 中的 "abc" 可以变为 "bcd"。开销为 3，所以最大长度为 3。
    示例 2：

    输入：s = "abcd", t = "cdef", cost = 3
    输出：1
    解释：s 中的任一字符要想变成 t 中对应的字符，其开销都是 2。因此，最大长度为 1。
    示例 3：

    输入：s = "abcd", t = "acde", cost = 0
    输出：1
    解释：你无法作出任何改动，所以最大长度为 1。
     

    提示：

    1 <= s.length, t.length <= 10^5
    0 <= maxCost <= 10^6
    s 和 t 都只含小写英文字母。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/get-equal-substrings-within-budget
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 尽可能使字符串相等
 * 在开销允许的范围内，可以得到调整完的最长的子串长度
 *
 * 注意：
 * 注意审题，返回的是最长子串，调整后的必须连续的!
 *
 * 首先，统计各个位置调整开销。
 * 然后，使用双指针法搜索满足开销的最长子串
 * 深刻理解sum -= cost[i]; 由于条件限制，sum是满足开销的，故sum-=cost[i];必满足。接着j++搜索即可。
 *
 *
 */


//双指针搜索
class Solution {
public:
    int abs(int x){
        return x>=0?x:-x;
    }
    int equalSubstring(string s, string t, int maxCost) {
        int n = s.length();
        vector<int> cost(n,0);
        for(int i=0;i<n;i++) cost[i] = abs(s[i] - t[i]);
        int i=0,j=0,sum=0,res=0;
        while(i<n){
            while(j<n&&sum + cost[j]<=maxCost){
                sum += cost[j];
                j++;
            }
            res = max(res,j-i);
            //核心
            sum -= cost[i];
            i++;
        }
        return res;
    }
};