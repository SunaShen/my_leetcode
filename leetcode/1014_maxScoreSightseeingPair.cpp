// @File   : 1014_maxScoreSightseeingPair.cpp
// @Source : https://leetcode-cn.com/problems/best-sightseeing-pair/
// @Title  : 1014. 最佳观光组合
// @Auther : sun_ds
// @Date   : 2020/6/17

/**  题目描述：
    给定正整数数组 A，A[i] 表示第 i 个观光景点的评分，并且两个景点 i 和 j 之间的距离为 j - i。

    一对景点（i < j）组成的观光组合的得分为（A[i] + A[j] + i - j）：景点的评分之和减去它们两者之间的距离。

    返回一对观光景点能取得的最高分。

     

    示例：

    输入：[8,1,5,2,6]
    输出：11
    解释：i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11
     

    提示：

    2 <= A.length <= 50000
    1 <= A[i] <= 1000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/best-sightseeing-pair
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 两层循环
 *  直接了两层循环，超时。
 *  使用剪枝。j<=i+A[i]。当 j > i+A[i] 此时，A[i] + A[j] + i - j; 变形为 A[j] + ( A[i] + i - j )
 *  此时，( A[i] + i - j ) < 0, 继续下去得不偿失。
 *
 *  时间复杂度 O(N^2)
 *
 * 2. 遍历 O(N)
 *  要求 A[i] + A[j] + i - j 的值最大。
 *  当前遍历值为 j，则 i 的取值范围为 0~j-1
 *  当前值 j 固定，则 A[j] - j 的值固定，所以即求 A[i] + i 的值最大。
 *  遍历 j 的时候使用 mx 记录过程中 A[i] + i 的最大值。以此减少一次循环。
 *  时间复杂度 O(N)
 *
 *
 */

class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int n = A.size();
        int max_score = INT_MIN;
        for(int i=0;i<n-1;i++){
            for(int j=i+1;j<=i+A[i]&&j<n;j++){
                int score = A[i] + A[j] + i - j;
                if(score > max_score){
                    max_score = score;
                }
            }
        }
        return max_score;
    }
};

class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int n = A.size();
        int max_score = 0;
        int mx = A[0] + 0;
        for(int j=1;j<n;j++){
            int score = mx + A[j] - j;
            mx = max(mx, A[j] + j);
            if(score > max_score) max_score = score;
        }
        return max_score;
    }
};
