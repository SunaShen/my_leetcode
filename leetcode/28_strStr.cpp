// @File   : 28_strStr.cpp
// @Source : https://leetcode-cn.com/problems/implement-strstr/
// @Title  : 28. 实现 strStr()
// @Auther : sun_ds
// @Date   : 2020/4/6

/**  题目描述：
    实现 strStr() 函数。

    给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

    示例 1:

    输入: haystack = "hello", needle = "ll"
    输出: 2
    示例 2:

    输入: haystack = "aaaaa", needle = "bba"
    输出: -1
    说明:

    当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

    对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/implement-strstr
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.KMP
 * 见下
 *
 *
 */

class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.size()==0) return 0;
        if(haystack.size()==0) return -1;

        int m = haystack.size();
        int n = needle.size();
        //next数组意义：当needle的j位置不能和haystack的i位置字符匹配时，j指针应该移动的位置为j = next[j]，而不是暴力搜索的j=0.
        //next[j] = j前面字符串的最长相等前后缀的长度 + 1.
        vector<int> next(n+1,0);
        //求next数组
        //i指向needle中各个位置。i只会自增遍历整个needle。
        //j指向i前面的最长前后缀的长度的后一个位置。即j = i前面最长前后缀长度+1
        int i=0,j=-1;
        next[i] = j;
        while(i<n){
            //如果j=最长前后缀的长度的后一个位置 的元素 不等于 i此时对应的元素
            //那么，j继续往前缩小长度。直接j = next[j]接着匹配。
            //直到特殊情况。j=0.时，还不相等。那说明，i前面没有前后缀了。
            //此时由于初值，next[0] = -1;。所以，j=-1.跳出循环。执行i++，j++。
            //此时next[i] = j = 0.即从头开始比。
            //注意这里，needle长度为n而next长度为n+1.所以needle[i]和 next[i+1]对应一个位置。而next[0]为哨兵。
            while(j>=0&&needle[i]!=needle[j]) j = next[j];
            i++;
            j++;
            next[i] = j;
        }

        //利用next数组移动下一次比较的位置。
        //j指向needle i指向haystack
        i = 0, j = 0;
        while(i<m){
            //如果不匹配，下一次j应该移动到next[j]位置重新比较。
            //j>=0 判断特例 即needle第一个字符就不能匹配，此时j=next[j]=next[0]=-1;
            //j=-1.跳出循环。执行i++,j++。
            //最终效果相当于。如果needle第一个字符就不能匹配，那么needle的j不动，haystack的i++。
            while(j>=0&&haystack[i]!=needle[j]) j = next[j];
            i++;
            j++;
            if(j==n){
                return i - n;
            }
        }
        return -1;
    }
};
