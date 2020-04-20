// @File   : 3_lengthOfLongestSubstring.cpp
// @Source : https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
// @Title  : 3. 无重复字符的最长子串
// @Auther : sun_ds
// @Date   : 2020/3/24

/**  题目描述：
    给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

    示例 1:

    输入: "abcabcbb"
    输出: 3
    解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
    示例 2:

    输入: "bbbbb"
    输出: 1
    解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
    示例 3:

    输入: "pwwkew"
    输出: 3
    解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
         请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 滑动窗口
 * 循环后移尾端并统计长度
 * 如果尾端字符已经存在了，则以前面存在字符的后一位和当前起始index比较，取大的。
 * 继续计算窗口长度
 *
 *
 *
 *
 */

//map
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> m;
        int index = 0, res = 0;
        for(int i=0;i<s.size();i++){
            if(m.find(s[i])==m.end()){
                m[s[i]] = i;
            }else{
                index = max(index,m[s[i]]+1); //要+1，不然子串中头尾相同了。
                m[s[i]] = i;
            }
            res = max(res, i - index + 1);
        }
        return res;
    }
};
//桶
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> count(128,-1);
        int index = 0, res = 0;
        for(int i=0;i<s.size();i++){
            if(count[(int)s[i]]==-1){
                count[(int)s[i]] = i;
            }else{
                index = max(index,count[(int)s[i]]+1); //要+1，不然子串中头尾相同了。
                count[(int)s[i]] = i;
            }
            res = max(res, i - index + 1);
        }
        return res;
    }
};