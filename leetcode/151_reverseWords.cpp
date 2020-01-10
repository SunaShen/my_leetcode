// @File   : 151_reverseWords.cpp
// @Source : https://leetcode-cn.com/problems/reverse-words-in-a-string/
// @Title  : 翻转字符串里的单词
// @Auther : sun_ds
// @Date   : 2020/1/9

/**  题目描述：
    给定一个字符串，逐个翻转字符串中的每个单词。

     

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
     

    进阶：

    请选用 C 语言的用户尝试使用 O(1) 额外空间复杂度的原地解法。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/reverse-words-in-a-string
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 反转各单词的顺序，并过滤空格。
 *
 * 1.基础法
 *  使用while循环过滤空格、检索单词。
 *  使用vector存储各单词。
 *  逆序输出vector中的单词。 rbegin,rend。
 *  逆序特性使用栈更好，单词入栈，然后出栈。
 *  各单词中间间隔空格。
 *
 * 2.字符流输入
 *  使用stringstream，将string输入字符流，自动过滤空格。
 *  然后逆序存储各单词，insert(0,str)
 *
 *  速度慢。    insert速度慢
 *
 *
 * 3.原地操作
 *  两次反转，先单词反转后整体反转。并将单词前移。
 *  将各个单词反转,并将单词+空格移到前面。原址操作。
 *  然后将前k-1个反转
 *  取前k-1个得到结果
 *
 *  原址操作
 *
 *  空间复杂度O(1)
 *
 *
 *
 */

class Solution {
public:
    string reverseWords(string s) {
        int i=0;
        while(i<s.size()&&s[i] == ' ') ++i;
        if(i==s.size()) return "";
        vector<string> t;
        while(i<s.size()){
            string temp;
            while(i<s.size()&&s[i] != ' '){temp.push_back(s[i]); ++i;}
            t.push_back(temp);
            while(i<s.size()&&s[i] == ' '){++i;}
        }
        string res;
        for(auto iter = t.rbegin();iter!=t.rend();++iter){
            res += *iter;
            res += " ";
        }
        return string(res.begin(),res.end()-1);
    }
};

//使用字符流输入,过滤空格。
//insert(0,str) 每次将单词塞到头上
class Solution {
public:
    string reverseWords(string s) {
        string ans, str;
        stringstream ss(s);
        while (ss >> str) ans.insert(0, str + " ");
        return ans.size() ? string(ans.begin(), ans.end() - 1) : "";
    }
};

//原地操作
class Solution {
public:
    string reverseWords(string s){
        int len = s.size();
        int k=0;
        for(int i=0,j=0;i<len;++i){
            while(j<len&&s[j] == ' ') ++j;
            if(j==len) break;
            i = j;
            while(j<len&&s[j] != ' ') ++j;
            reverse(s.begin() + i, s.begin() + j);
            while(i<j){
                s[k] = s[i];
                ++k;
                ++i;
            }
            s[k++] = ' ';
        }
        reverse(s.begin(),s.begin()+k-1);
        return k == 0 ? "" : s.substr(0,k-1);
    }
};