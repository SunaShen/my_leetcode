// @File   : 459_repeatedSubstringPattern.cpp
// @Source : https://leetcode-cn.com/problems/repeated-substring-pattern/
// @Title  : 459. 重复的子字符串
// @Auther : sun_ds
// @Date   : 2020/8/24

/**  题目描述：
    给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。给定的字符串只含有小写英文字母，并且长度不超过10000。

    示例 1:

    输入: "abab"

    输出: True

    解释: 可由子字符串 "ab" 重复两次构成。
    示例 2:

    输入: "aba"

    输出: False
    示例 3:

    输入: "abcabcabcabc"

    输出: True

    解释: 可由子字符串 "abc" 重复四次构成。 (或者子字符串 "abcabc" 重复两次构成。)

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/repeated-substring-pattern
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.遍历
 * 两层循环
 * 外层循环遍历子串长度。
 * 内存循环按照子串长度，固定间隔遍历。
 * 发现有不相等的表示当前子串长度不满足要求，进行下一次子串长度的遍历。
 *
 * 时间复杂度 O(N^2)
 * 空间复杂度 O(1)
 *
 * 2.构造双倍字符串
 *  构造双倍字符串a = s + s，去掉 a 中第一个和最后一个字符后，若还包含 s，则表示 s 可以由它的一个子串重复多次构成。
 *
 *  假设 s 可由 子串 x 重复 n 次构成，即 s = nx
 *  则有 s+s = 2nx
 *  移除 s+s 开头和结尾的字符，变为 (s+s)[1:-1]，则破坏了开头和结尾的子串 x
 *  此时只剩 2n-2 个子串
 *  若 s 在 (s+s)[1:-1] 中，则有 2n-2 >= n，即 n >= 2
 *  即 s 至少可由 x 重复 2 次构成
 *  否则，n < 2，n 为整数，只能取 1，说明 s 不能由其子串重复多次构成
 *
 *  作者：elevenxx
 *  链接：https://leetcode-cn.com/problems/repeated-substring-pattern/solution/gou-zao-shuang-bei-zi-fu-chuan-by-elevenxx/
 *  来源：力扣（LeetCode）
 *  著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 * 3.使用 kmp 做查找
 *  继续使用双倍字符串思想，只不过 find 使用 kmp 算法
 *
 *
 */

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        for(int i=1;i<=s.size()/2;i++){
            if (s.size()%i == 0) {
                bool match = true;
                for(int j=i;j<s.size();j++){
                    if(s[j] != s[j-i]){ //妙
                        match = false;
                        break;
                    }
                }
                if(match){
                    return true;
                }
            }
        }
        return false;
    }
};

// 双倍字符串
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        return (s + s).find(s, 1) != s.size();
    }
};

class Solution {
public:
    bool kmp(const string& query, const string& pattern) {

        int n = query.size();
        int m = pattern.size();

        vector<int> next(m+1, 0);
        int i=0, j=-1;
        next[0] = -1;
        while(i<m){
            while(j>=0 && pattern[i] != pattern[j]) j = next[j];
            i++;
            j++;
            next[i] = j;
        }

        i=0,j=0;
        while(i<n){
            while(j>=0 && query[i] != pattern[j]) j = next[j];
            i++;
            j++;
            if(j == m){
                return true;
            }
        }
        return false;
    }

    bool repeatedSubstringPattern(string s) {
        string temp = s + s;
        string t(temp.begin()+1, temp.end()-1);
        return kmp(t, s);
    }
};