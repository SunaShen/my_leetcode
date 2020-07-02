// @File   : 718_findLength.cpp
// @Source : https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/
// @Title  : 718. 最长重复子数组
// @Auther : sun_ds
// @Date   : 2020/7/1

/**  题目描述：
    给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。

    示例 1:

    输入:
    A: [1,2,3,2,1]
    B: [3,2,1,4,7]
    输出: 3
    解释:
    长度最长的公共子数组是 [3, 2, 1]。
    说明:

    1 <= len(A), len(B) <= 1000
    0 <= A[i], B[i] < 100


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 * 使用 dp[i][j], 表示 A[i:] 与 B[j:] 的最长公共前缀长度。
 * 若 A[i] == B[j], 则有 dp[i][j] = dp[i+1][j+1] + 1;
 * 若 A[i] != B[j], 则有 dp[i][j] = 0;
 *
 * 从后往前计算，整个过程中最大的 dp[i][j] 为结果。
 *
 * 2.滑动窗口
 * 枚举各种对齐方式。
 * 固定对齐方式下，同步遍历数组，统计最长相同连续子串长度。
 *
 *
 */

class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int m = A.size(), n = B.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        int res = 0;
        for(int i=m-1; i>=0; --i){
            for(int j=n-1; j>=0; --j){
                if(A[i] == B[j]){
                    dp[i][j] = dp[i+1][j+1] + 1;
                }else{
                    dp[i][j] = 0;
                }
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }
};

//滑动窗口
class Solution {
public:
    int maxLength(vector<int>& A, vector<int>& B, int addA, int addB, int len) {
        int ret = 0, k = 0;
        for (int i = 0; i < len; i++) {
            if (A[addA + i] == B[addB + i]) {
                k++;
            } else {
                k = 0;
            }
            ret = max(ret, k);
        }
        return ret;
    }
    int findLength(vector<int>& A, vector<int>& B) {
        int n = A.size(), m = B.size();
        int ret = 0;
        // 遍历各种对齐方式
        for (int i = 0; i < n; i++) {
            int len = min(m, n - i);
            // 默认对齐情况下求最长重复子串
            int maxlen = maxLength(A, B, i, 0, len);
            ret = max(ret, maxlen);
        }
        for (int i = 0; i < m; i++) {
            int len = min(n, m - i);
            // 默认对齐情况下求最长重复子串
            int maxlen = maxLength(A, B, 0, i, len);
            ret = max(ret, maxlen);
        }
        return ret;
    }
};





