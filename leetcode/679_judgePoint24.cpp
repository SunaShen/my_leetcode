// @File   : 679_judgePoint24.cpp
// @Source : https://leetcode-cn.com/problems/24-game/
// @Title  : 679. 24 点游戏
// @Auther : sun_ds
// @Date   : 2020/8/22

/**  题目描述：
    你有 4 张写有 1 到 9 数字的牌。你需要判断是否能通过 *，/，+，-，(，) 的运算得到 24。

    示例 1:

    输入: [4, 1, 8, 7]
    输出: True
    解释: (8-4) * (7-1) = 24
    示例 2:

    输入: [1, 2, 1, 2]
    输出: False
    注意:

    除法运算符 / 表示实数除法，而不是整数除法。例如 4 / (1 - 2/3) = 12 。
    每个运算符对两个数进行运算。特别是我们不能用 - 作为一元运算符。例如，[1, 1, 1, 1] 作为输入时，表达式 -1 - 1 - 1 - 1 是不允许的。
    你不能将数字连接在一起。例如，输入为 [1, 2, 1, 2] 时，不能写成 12 + 12 。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/24-game
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.回溯法
 * 4 个数字和 3 个运算符
 * 首先从 4 个数字中选择 2 个数字 共有 4*3=12 种选法，并从加减乘除中选一个运算符 4 种选法。
 * 得到的结果替代原来两个数字，剩下三个数字。(核心)
 * 剩下 3 个数字中选择 2 个数字，共有 3*2=6 种选法，并从加减乘除中选一个运算符 4 种选法。
 * 此时剩下 2 个数字，有2种不同的排列顺序，并从加减乘除中选一个运算符 4 种选法。
 *
 * 因此，一共有 12*4 * 6*4 * 2*4 = 9216 种情况
 *
 * 使用回溯法，遍历不同的数字选择和符号选择。
 *
 * 其中，加法和乘法都满足交换律，因此可适当剪枝。
 *
 * 本题除法为实数除法，因此需要考虑精度误差，设置 1e-6
 *
 * 时间复杂度 O(1)
 * 空间复杂度 O(1)
 *
 */

class Solution {
public:
    static constexpr int TARGET = 24;
    static constexpr double EPSILON = 1e-6;
    static constexpr int ADD = 0, MULTIPLY = 1, SUBTRACT = 2, DIVIDE = 3;

    bool judgePoint24(vector<int> &nums) {
        vector<double> l;
        for (const int &num : nums) {
            l.emplace_back(static_cast<double>(num));
        }
        return solve(l);
    }

    bool solve(vector<double> &l) {
        if (l.size() == 0) {
            return false;
        }
        if (l.size() == 1) {
            return fabs(l[0] - TARGET) < EPSILON;
        }
        int size = l.size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    // 在 l 中挑两个数 l[i] 和 l[j] 合并他们， 并且还有挑个运算符
                    vector<double> list2 = vector<double>();
                    for (int k = 0; k < size; k++) {
                        if (k != i && k != j) {
                            // 记录剩下的数字
                            list2.emplace_back(l[k]);
                        }
                    }
                    // 遍历运算符
                    // 0 : "+", 1 : "*", 2 : "-", 3 : "/".
                    for (int k = 0; k < 4; k++) {
                        // 剪枝 加法和乘法交换顺序结果一致
                        if (k < 2 && i > j) {
                            continue;
                        }
                        if (k == ADD) {
                            list2.emplace_back(l[i] + l[j]);
                        } else if (k == MULTIPLY) {
                            list2.emplace_back(l[i] * l[j]);
                        } else if (k == SUBTRACT) {
                            list2.emplace_back(l[i] - l[j]);
                        } else if (k == DIVIDE) {
                            // 跳过，不进行除法  也不递归 solve 下去
                            if (fabs(l[j]) < EPSILON) {
                                continue;
                            }
                            list2.emplace_back(l[i] / l[j]);
                        }
                        if (solve(list2)) {
                            return true;
                        }
                        // 回溯，换下一个符号
                        list2.pop_back();
                    }
                }
            }
        }
        return false;
    }
};
