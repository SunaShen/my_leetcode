// @File   : 365_canMeasureWater.cpp
// @Source : https://leetcode-cn.com/problems/water-and-jug-problem/
// @Title  : 365. 水壶问题
// @Auther : sun_ds
// @Date   : 2020/3/22

/**  题目描述：
    有两个容量分别为 x升 和 y升 的水壶以及无限多的水。请判断能否通过使用这两个水壶，从而可以得到恰好 z升 的水？

    如果可以，最后请用以上水壶中的一或两个来盛放取得的 z升 水。

    你允许：

    装满任意一个水壶
    清空任意一个水壶
    从一个水壶向另外一个水壶倒水，直到装满或者倒空
    示例 1: (From the famous "Die Hard" example)

    输入: x = 3, y = 5, z = 4
    输出: True
    示例 2:

    输入: x = 2, y = 6, z = 5
    输出: False
*/

/**
 *
 * 1.dfs
 * 设定当前两个水壶中的水量remain_x,remain_y为当前状态。
 * 起始状态：remain_x,remain_y = 0；
 * 结束状态：remain_x==z||remain_y==z||remain_x+remain_y==z；
 *
 * 状态转移：
 *  把 X 壶的水灌进 Y 壶，直至灌满或倒空；
 *  把 Y 壶的水灌进 X 壶，直至灌满或倒空；
 *  把 X 壶灌满；
 *  把 Y 壶灌满；
 *  把 X 壶倒空；
 *  把 Y 壶倒空；
 *
 *  使用stack用迭代的方法写深搜。
 *  搜索下去。但是会有重复的情况出现，避免死循环，使用set去重。记录当前remain_x,remain_y状态，若遍历过直接跳过。
 *  直到满足条件 remain_x==z||remain_y==z||remain_x+remain_y==z； 返回true；
 *  如果所有能到达的状态都不能满足结束条件，则stack会变空，退出，返回false；
 *
 *
 * 2.gcd
 *  我们认为，每次操作只会让桶里的水总量增加 x，增加 y，减少 x，或者减少 y。
 *
 *  你可能认为这有问题：如果往一个不满的桶里放水，或者把它排空呢？那变化量不就不是 x 或者 y 了吗？接下来我们来解释这一点：
 *
 *  首先要清楚，在题目所给的操作下，两个桶不可能同时有水且不满。因为观察所有题目中的操作，操作的结果都至少有一个桶是空的或者满的；
 *
 *  其次，对一个不满的桶加水是没有意义的。因为如果另一个桶是空的，那么这个操作的结果等价于直接从初始状态给这个桶加满水；而如果另一个桶是满的，那么这个操作的结果等价于从初始状态分别给两个桶加满；
 *
 *  再次，把一个不满的桶里面的水倒掉是没有意义的。因为如果另一个桶是空的，那么这个操作的结果等价于回到初始状态；而如果另一个桶是满的，那么这个操作的结果等价于从初始状态直接给另一个桶倒满。
 *
 *  因此，我们可以认为每次操作只会给水的总量带来 x 或者 y 的变化量。因此我们的目标可以改写成：找到一对整数 a,b，使得ax+by=z
 *
 *  而只要满足 z≤x+y，且这样的 a,b 存在，那么我们的目标就是可以达成的。这是因为：
 *
 *  若 a≥0,b≥0，那么显然可以达成目标。
 *
 *  若 a<0，那么可以进行以下操作：
 *
 *          往 y 壶倒水；
 *
 *          把 y 壶的水倒入 x 壶；
 *
 *          如果 y 壶不为空，那么 x 壶肯定是满的，把 x 壶倒空，然后再把 y 壶的水倒入 x 壶。
 *
 *          重复以上操作直至某一步时 x 壶进行了 a 次倒空操作，y 壶进行了 b 次倒水操作。
 *
 *  若 b<0，方法同上，x 与 y 互换。
 *
 *  而贝祖定理告诉我们，ax+by=z 有解当且仅当 z 是 x,y 的最大公约数的倍数。因此我们只需要找到 x,y 的最大公约数并判断 z 是否是它的倍数即可。
 *
 * 作者：LeetCode-Solution
 * 链接：https://leetcode-cn.com/problems/water-and-jug-problem/solution/shui-hu-wen-ti-by-leetcode-solution/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 */


//dfs
using PII = pair<int, int>;

class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        stack<PII> stk;
        stk.emplace(0, 0);
        auto hash_function = [](const PII& o) {return hash<int>()(o.first) ^ hash<int>()(o.second);};
        unordered_set<PII, decltype(hash_function)> seen(0, hash_function);
        while (!stk.empty()) {
            if (seen.count(stk.top())) {
                stk.pop();
                continue;
            }
            seen.emplace(stk.top());

            auto [remain_x, remain_y] = stk.top();
            stk.pop();
            if (remain_x == z || remain_y == z || remain_x + remain_y == z) {       //也可以使用remain_x + remain_y == z只是多操作一轮，没有这个剪枝好
                return true;
            }
            // 把 X 壶灌满。
            stk.emplace(x, remain_y);
            // 把 Y 壶灌满。
            stk.emplace(remain_x, y);
            // 把 X 壶倒空。
            stk.emplace(0, remain_y);
            // 把 Y 壶倒空。
            stk.emplace(remain_x, 0);
            // 把 X 壶的水灌进 Y 壶，直至灌满或倒空。
            stk.emplace(remain_x - min(remain_x, y - remain_y), remain_y + min(remain_x, y - remain_y));
            // 把 Y 壶的水灌进 X 壶，直至灌满或倒空。
            stk.emplace(remain_x + min(remain_y, x - remain_x), remain_y - min(remain_y, x - remain_x));
        }
        return false;
    }
};

87

//gcd
class Solution {
public:
    int gcd(int a,int b){
        if(a%b==0){
            return b;
        }
        return gcd(b,a%b);
    }
    bool canMeasureWater(int x, int y, int z) {
        if(x+y<z) return false;
        if (x == 0||y == 0) return z == 0 || x + y == z;
        return z%gcd(x,y)==0;
    }
};