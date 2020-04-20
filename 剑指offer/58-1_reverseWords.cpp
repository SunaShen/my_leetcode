// @File   : 58-1_reverseWords.cpp
// @Source : https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof/
// @Title  : 面试题58 - I. 翻转单词顺序
// @Auther : sun_ds
// @Date   : 2020/3/29

/**  题目描述：
    输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，则输出"student. a am I"。

     

    示例 1：

    输入: "the sky is blue"
    输出: "blue is sky the"
    示例 2：

    输入: "  hello world!  "
    输出: "world! hello"
    解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
    示例 3：

    输入: "a good   example"
    输出: "example good a"
    解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
     

    说明：

    无空格字符构成一个单词。
    输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
    如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
    注意：本题与主站 151 题相同：https://leetcode-cn.com/problems/reverse-words-in-a-string/

    注意：此题对比原题有改动

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.取出各单词，逆序拼接
 *   需要额外空间，空间复杂度O(n)
 * 2.两次反转，原址操作
 *  2.1首先反转各个单词，并将单词前移到特定位置(过滤前空格)
 *  2.2反转整个串。
 *
 */

class Solution {
public:
    string reverseWords(string s) {
        int i=0;
        //过滤空格
        while(i<s.size()&&s[i] == ' ') ++i;
        if(i==s.size()) return "";
        vector<string> t;
        //取出单词
        while(i<s.size()){
            string temp;
            while(i<s.size()&&s[i] != ' '){temp.push_back(s[i]); ++i;}
            t.push_back(temp);
            while(i<s.size()&&s[i] == ' '){++i;} //过滤空格
        }
        //逆序拼接
        string res;
        for(auto iter = t.rbegin();iter!=t.rend();++iter){
            res += *iter;
            res += " ";
        }
        //去掉最后一个空格
        return string(res.begin(),res.end()-1);
    }
};

class Solution {
public:
    string reverseWords(string s) {
        int len = s.size();
        int k=0;
        for(int i=0,j=0;i<len;++i){
            while(j<len&&s[j] == ' ') ++j;
            if(j==len) break;
            i = j;
            while(j<len&&s[j] != ' ') ++j;
            //反转各个单词
            reverse(s.begin() + i, s.begin() + j);
            //单词往前放
            while(i<j){
                s[k] = s[i];
                ++k;
                ++i;
            }
            s[k++] = ' ';
        }
        //反转整个串
        reverse(s.begin(),s.begin()+k-1);
        return k == 0 ? "" : s.substr(0,k-1);
    }
};
