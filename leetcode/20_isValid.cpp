// @File   : 20_isValid.cpp
// @Source : https://leetcode-cn.com/problems/valid-parentheses/
// @Title  : 20. 有效的括号
// @Auther : sun_ds
// @Date   : 2020/3/19

/**  题目描述：
    给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

    有效字符串需满足：

    左括号必须用相同类型的右括号闭合。
    左括号必须以正确的顺序闭合。
    注意空字符串可被认为是有效字符串。

    示例 1:

    输入: "()"
    输出: true
    示例 2:

    输入: "()[]{}"
    输出: true
    示例 3:

    输入: "(]"
    输出: false
    示例 4:

    输入: "([)]"
    输出: false
    示例 5:

    输入: "{[]}"
    输出: true
*/

/**
 *
 * 使用栈匹配括号
 * 左括号入栈，右括号看是否和栈顶对应。不对应为无效。
 * 最终栈中不应有元素，有元素表示多了左括号，无效。
 * 循环过程中遇到右括号时，栈不能为空，为空表示当前右括号没有左括号匹配，无效。
 *
 *
 */

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(int i=0;i<s.size();i++){
            if(s[i]=='('||s[i]=='['||s[i]=='{'){
                st.push(s[i]);
            }else{
                if(st.empty()) return false;
                if(s[i]==')'&&st.top()!='(') return false;
                if(s[i]==']'&&st.top()!='[') return false;
                if(s[i]=='}'&&st.top()!='{') return false;
                st.pop();
            }
        }
        if(st.empty()) return true;
        else return false;
    }
};


