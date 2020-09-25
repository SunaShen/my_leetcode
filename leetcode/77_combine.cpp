// @File   : 77_combine.cpp
// @Source : https://leetcode-cn.com/problems/combinations/
// @Title  : 77. 组合
// @Auther : sun_ds
// @Date   : 2020/9/8

/**  题目描述：
    给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。

    示例:

    输入: n = 4, k = 2
    输出:
    [
      [2,4],
      [3,4],
      [2,3],
      [1,2],
      [1,3],
      [1,4],
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/combinations
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.回溯法
 *  n 个元素中选取 k 个。
 *  结束条件
 *   - 后面数字全选也不够
 *   - 当前选中数字刚好 k 个，记录
 *
 *  时间复杂度 O(C(n,k)*k)
 *  空间复杂度 O(n+k) = O(n)
 *
 */

class Solution {
private:
    vector<vector<int>> res;
public:
    void backtrack(int index, int n, int k, vector<int> temp){
        // 剪枝，后面的数全选都不够
        if(n - index + 1 < k - temp.size()){
            return;
        }
        if(temp.size() == k){
            res.push_back(temp);
            return;
        }
        // 有第一个剪枝，当前判断可省略
//        if(index == n+1){
//            return;
//        }
        for(int i=index; i<=n; i++){
            temp.push_back(i);
            backtrack(i+1, n, k, temp);
            temp.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        backtrack(1, n, k, {});
        return res;
    }
};
