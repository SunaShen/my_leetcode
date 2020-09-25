// @File   : 60_getPermutation.cpp
// @Source : https://leetcode-cn.com/problems/permutation-sequence/
// @Title  : 60. 第k个排列
// @Auther : sun_ds
// @Date   : 2020/9/5

/**  题目描述：
    给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。

    按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：

    "123"
    "132"
    "213"
    "231"
    "312"
    "321"
    给定 n 和 k，返回第 k 个排列。

    说明：

    给定 n 的范围是 [1, 9]。
    给定 k 的范围是[1,  n!]。
    示例 1:

    输入: n = 3, k = 3
    输出: "213"
    示例 2:

    输入: n = 4, k = 9
    输出: "2314"

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/permutation-sequence
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. next_permutation
 *
 * 2. 取模
 *  按顺序来
 *  选 1 作为 a1 共对应 (n-1)! 种排列(后面 n-1 个数的全排列)。
 *  选 2 作为 a1 共对应 (n-1)! 种排列(后面 n-1 个数的全排列)。
 *  ... ... ... ... ...
 *  选 n 作为 a1 共对应 (n-1)! 种排列(后面 n-1 个数的全排列)。
 *
 *  因此,
 *  k = [1, (n-1)!] , a1 = 1
 *  k = [(n-1)!+1, 2*(n-1)!] , a1 = 2
 *  k = [2*(n-1)!+1, 3*(n-1)!] , a1 = 3
 *  ... ... ... ... ...
 *  k = [(n-1)*(n-1)!+1, n*(n-1)!] , a1 = 1
 *
 *  所以 a1 = （k-1）// (n-1)! + 1 更通用讲，即 第（k-1）// (n-1)! + 1 小的数   第 xx 小
 *
 *  接下来选 a2. 相同的子问题。在剩下的 n-1 个元素中找到对应的元素放到 a2.
 *  此时需要求得是剩下 n-1 个元素的第 (k-1) % (n-1)! + 1个 排列
 *  当前的 k' = (k-1) % (n-1)! + 1。 继续使用公式 a2 = 第（k'-1）// (n-2)! + 1 小的数
 *  依次类推。
 *
 *
 *  时间复杂度 O(N^2)
 *  空间复杂度 O(N)
 *
 *
 */

// 使用 std::next_permutation
class Solution {
public:
    string getPermutation(int n, int k) {
        string num;
        for (int i = 0; i < n; ++i) {
            num.push_back(i + 1 + '0');
        }
        for (int i = 0; i < k - 1; ++i) {
            next_permutation(num.begin(), num.end());
        }
        return num;
    }
};

// 通过 k 依次选中各个位置的元素
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> factorial(n);
        factorial[0] = 1;
        for (int i = 1; i < n; ++i) {
            factorial[i] = factorial[i - 1] * i;
        }

        string ans;
        vector<int> valid(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            int order = (k - 1) / factorial[n - i] + 1;
            for (int j = 1; j <= n; ++j) {
                order -= valid[j];
                if (!order) {
                    ans += (j + '0');
                    valid[j] = 0;
                    break;
                }
            }
            k = (k - 1) % factorial[n - i] + 1;
        }
        return ans;
    }
};
