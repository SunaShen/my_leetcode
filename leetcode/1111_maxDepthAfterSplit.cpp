// @File   : 1111_maxDepthAfterSplit.cpp
// @Source : https://leetcode-cn.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/
// @Title  : 1111. 有效括号的嵌套深度
// @Auther : sun_ds
// @Date   : 2020/4/1

/**  题目描述：
    有效括号字符串 定义：对于每个左括号，都能找到与之对应的右括号，反之亦然。详情参见题末「有效括号字符串」部分。

    嵌套深度 depth 定义：即有效括号字符串嵌套的层数。详情参见题末「嵌套深度」部分。

     

    给你一个「有效括号字符串」 seq，请你将其分成两个不相交的有效括号字符串 A 和 B：

    不相交：每个 seq[i] 只能分给 A 和 B 二者中的一个，不能既属于 A 也属于 B 。
    A 或 B 中的元素在原字符串中可以不连续。
    A.length + B.length = seq.length
    请你选出 任意 这样的 A 和 B，使得 max(depth(A), depth(B)) 的可能取值最小。其中 depth(A) 表示 A 的嵌套深度，depth(B) 表示 B 的嵌套深度。

    请你返回一个长度为 seq.length 的答案数组 answer，编码规则如下：

    answer[i] = 0，seq[i] 分给 A 。
    answer[i] = 1，seq[i] 分给 B 。
    即便有多个满足要求的答案存在，你也只需返回其中任意 一个 。

     

    示例 1：

    输入：seq = "(()())"
    输出：[0,1,1,1,1,0]
    示例 2：

    输入：seq = "()(())()"
    输出：[0,0,0,1,1,0,1,1]
     

    提示：

    1 <= text.size <= 10000
     

    有效括号字符串：

    仅由 "(" 和 ")" 构成的字符串，对于每个左括号，都能找到与之对应的右括号，反之亦然。

    下述几种情况同样属于有效括号字符串：

    空字符串
    连接，可以记作 AB（A 与 B 连接），其中 A 和 B 都是有效括号字符串
    嵌套，可以记作 (A)，其中 A 是有效括号字符串
    嵌套深度：

    类似地，我们可以定义任意有效括号字符串 s 的 嵌套深度 depth(S)：

    s 为空时，depth("") = 0
    s 为 A 与 B 连接时，depth(A + B) = max(depth(A), depth(B))，其中 A 和 B 都是有效括号字符串
    s 为嵌套情况，depth("(" + A + ")") = 1 + depth(A)，其中 A 是有效括号字符串
    例如：""，"()()"，和 "()(()())" 都是有效括号字符串，嵌套深度分别为 0，1，2，而 ")(" 和 "(()" 都不是有效括号字符串。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 记录嵌套深度，为了使得max(depth(A), depth(B))最小，则A和B子序列的嵌套深度应该平均分配。
 * 因此，按照嵌套深度将括号分成两类。即奇数为一类，偶数为一类。
 * 1.栈
 *  使用栈保存前括号，遇到后括号出栈。则每个括号的嵌套深度即为栈的深度
 * 2.计数嵌套深度depth
 *  使用栈来只是记录嵌套深度有些浪费。
 *  使用depth记录嵌套深度，遇到前括号+1，遇到后括号-1
 *
 *
 *
 */

//栈
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size();
        stack<int> s;
        vector<int> res(n,0);
        for(int i=0;i<n;i++){
            if(seq[i]=='('){
                s.push(i);
                res[i] = s.size()%2;
            }else{
                res[i] = s.size()%2;
                s.pop();
            }
        }
        return res;
    }
};
//记录深度
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size();
        int depth = 0;
        vector<int> res(n,0);
        //depth为嵌套深度
        //均匀分配 嵌套深度为奇数的分给0 为偶数的分给1
        for(int i=0;i<n;i++){
            if(seq[i]=='('){
                depth++;
                res[i] = depth%2;
            }else{
                res[i] = depth%2;
                depth--;
            }
        }
        return res;
    }
};
