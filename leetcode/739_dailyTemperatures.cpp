// @File   : 739_dailyTemperatures.cpp
// @Source : https://leetcode-cn.com/problems/daily-temperatures/
// @Title  : 739. 每日温度
// @Auther : sun_ds
// @Date   : 2020/3/1

/**  题目描述：
    根据每日 气温 列表，请重新生成一个列表，对应位置的输入是你需要再等待多久温度才会升高超过该日的天数。如果之后都不会升高，请在该位置用 0 来代替。

    例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

    提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/daily-temperatures
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.单调栈
 * 维护单调递减栈。栈中存储索引，以来计算相隔天数。
 * 维护单调递减栈，入栈元素不满足递减规则时，需要将栈顶出栈。则表示栈顶的下一个温度升高的天数为当前需要入栈的元素。
 * 存储两个索引(天数)之间的差值，得到相隔的天数。
 *
 */

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int n = T.size();
        stack<int> s;
        vector<int> res(n,0);
        for(int i=0;i<n;i++){
            while(!s.empty()&&T[s.top()]<T[i]){
                res[s.top()] = i - s.top();
                s.pop();
            }
            s.push(i);
        }
        return res;
    }
};