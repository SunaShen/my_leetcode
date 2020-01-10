// @File   : 150_evalRPN.cpp
// @Source : https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/
// @Title  : 波兰表达式求值
// @Auther : sun_ds
// @Date   : 2020/1/7

/**  题目描述：
    根据逆波兰表示法，求表达式的值。

    有效的运算符包括 +, -, *, / 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

    说明：

    整数除法只保留整数部分。
    给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。
    示例 1：

    输入: ["2", "1", "+", "3", "*"]
    输出: 9
    解释: ((2 + 1) * 3) = 9
    示例 2：

    输入: ["4", "13", "5", "/", "+"]
    输出: 6
    解释: (4 + (13 / 5)) = 6
    示例 3：

    输入: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
    输出: 22
    解释:
      ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
    = ((10 * (6 / (12 * -11))) + 17) + 5
    = ((10 * (6 / -132)) + 17) + 5
    = ((10 * 0) + 17) + 5
    = (0 + 17) + 5
    = 17 + 5
    = 22

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/evaluate-reverse-polish-notation
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * 逆波兰表示法
 * 运算符号在两个数字后，且当前符号使用前面最近的两个数字。
 * 依次运算，得到最终结果。
 *
 * 1.容器
 * 从前往后遍历表达式，遇到运算符号，就取前面两个元素(一定是数字)做该运算符的运算，并将这三个元素变成一个运算结果。
 * 依次执行直到最后，缩减为一个数值，即为最终结果。
 *
 * vector的erase操作速度极慢。。。
 *
 * 2.栈
 * 同样的原理，从前往后遍历表达式，遇到运算符号，就取前面两个元素(一定是数字)做该运算符的运算。
 * 由于每个符号只与其紧邻的前面两个数字有关，有着一个先入后出的特性，因此使用栈来存储表达式中的各个数。
 *
 * 遍历表达式，若不为运算符号，则入栈，否则出栈两次获得两个数字，得到运算结果后在入栈，进行下一次循环。
 *
 * 最后栈中只剩最后最终结果。
 *
 *
 */

//速度很慢，erase速度慢
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<string> temp = tokens;
        int i=0;
        while(i != temp.size()){
            if(temp[i] == "+"){
                int t = stoi(temp[i-2]) + stoi(temp[i-1]);
                temp[i-2] = to_string(t);
                temp.erase(temp.begin()+i-1);
                temp.erase(temp.begin()+i-1);
                i = i - 1;
            }else if(temp[i] == "-"){
                int t = stoi(temp[i-2]) - stoi(temp[i-1]);
                temp[i-2] = to_string(t);
                temp.erase(temp.begin()+i-1);
                temp.erase(temp.begin()+i-1);
                i = i - 1;
            }else if(temp[i] == "*"){
                int t = stoi(temp[i-2]) * stoi(temp[i-1]);
                temp[i-2] = to_string(t);
                temp.erase(temp.begin()+i-1);
                temp.erase(temp.begin()+i-1);
                i = i - 1;
            }else if(temp[i] == "/"){
                int t = stoi(temp[i-2]) / stoi(temp[i-1]);
                temp[i-2] = to_string(t);
                temp.erase(temp.begin()+i-1);
                temp.erase(temp.begin()+i-1);
                i = i - 1;
            }else{
                ++i;
            }
        }
        return stoi(temp[0]);
    }
};

//使用栈
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<string> s;
        for(int i=0;i<tokens.size();++i){
            if(tokens[i] == "+"){
                int t1 = stoi(s.top());s.pop();
                int t2 = stoi(s.top());s.pop();
                s.push(to_string(t2 + t1));
            }else if(tokens[i] == "-"){
                int t1 = stoi(s.top());s.pop();
                int t2 = stoi(s.top());s.pop();
                s.push(to_string(t2 - t1));
            }else if(tokens[i] == "*"){
                int t1 = stoi(s.top());s.pop();
                int t2 = stoi(s.top());s.pop();
                s.push(to_string(t2 * t1));
            }else if(tokens[i] == "/"){
                int t1 = stoi(s.top());s.pop();
                int t2 = stoi(s.top());s.pop();
                s.push(to_string(t2 / t1));
            }else{
                s.push(tokens[i]);
            }
        }
        return stoi(s.top());
    }
};