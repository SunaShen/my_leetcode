// @File   : 974_subarraysDivByK.cpp
// @Source : https://leetcode-cn.com/problems/subarray-sums-divisible-by-k/
// @Title  : 974. 和可被 K 整除的子数组
// @Auther : sun_ds
// @Date   : 2020/4/10

/**  题目描述：
    给定一个整数数组 A，返回其中元素之和可被 K 整除的（连续、非空）子数组的数目。

     

    示例：

    输入：A = [4,5,0,-2,-3,1], K = 5
    输出：7
    解释：
    有 7 个子数组满足其元素之和可被 K = 5 整除：
    [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
     

    提示：

    1 <= A.length <= 30000
    -10000 <= A[i] <= 10000
    2 <= K <= 10000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/subarray-sums-divisible-by-k
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 与连续子数组和有关，使用前缀和！！！！
 * p[i] = A[0]+A[1]+A[2]+.....+A[i]
 * 则子数组 [i,j]的和为p[j]-p[i-1];
 *
 * 遍历一遍获得前缀和
 * 遍历i，j的各个位置，得到所有子数组的和，判断是否能够被整除。
 * 复杂度O(N^2)
 *
 * 利用线性同余特性
 * 即： (a-b)%m=0 等价于 a%m=b%m
 * 将各个前缀和对m取模，得到的值用于分类。分成一类的任意两个可以组成满足子数组和被m整除的条件。
 *
 * 使用vector或者unordered_map存储
 * 使用组合公式。C(n,2) = n*(n-1)/2;
 *
 * 防止负数取模出现负数。
 * ((x % MOD) + MOD) % MOD   保证结果为非负数
 *
 *
 *
 *
 */


class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        int n = A.size();
        vector<int> p(n,0);
        //求前缀和
        for(int i=0;i<n;i++){
            p[i] = i==0?A[i]:p[i-1]+A[i];
        }
        vector<int> k(K,0);
        //分类
        for(int i=0;i<n;i++){
            k[(p[i]%K+K)%K]++;
        }
        //统计
        int res = 0;
        for(int i=0;i<K;i++){
            res += (k[i]*(k[i]-1))/2;
        }
        res += k[0]; //包含自身A[i]可以被整除
        return res;
    }
};

class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        unordered_map<int, int> cnt;
        cnt[0] = 1;//包含自身A[i]可以被整除
        for(int i = 0, n = A.size(), sum = 0; i < n; i++) {
            sum = ((sum + A[i])%K + K)%K;
            ++ cnt[sum];
        }
        int anw = 0;
        for(auto p : cnt) {
            anw += p.second*(p.second-1)/2;
        }
        return anw;
    }
};


