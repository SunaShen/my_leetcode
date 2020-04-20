// @File   : 945_minIncrementForUnique.cpp
// @Source : https://leetcode-cn.com/problems/minimum-increment-to-make-array-unique/
// @Title  : 945. 使数组唯一的最小增量
// @Auther : sun_ds
// @Date   : 2020/3/22

/**  题目描述：
    给定整数数组 A，每次 move 操作将会选择任意 A[i]，并将其递增 1。

    返回使 A 中的每个值都是唯一的最少操作次数。

    示例 1:

    输入：[1,2,2]
    输出：1
    解释：经过一次 move 操作，数组将变为 [1, 2, 3]。
    示例 2:

    输入：[3,2,1,2,1,7]
    输出：6
    解释：经过 6 次 move 操作，数组将变为 [3, 4, 1, 2, 5, 7]。
    可以看出 5 次或 5 次以下的 move 操作是不能让数组的每个值唯一的。
    提示：

    0 <= A.length <= 40000
    0 <= A[i] < 40000

*/

/**
 *
 * 每个数都不能重复，且修改当前值只能递增。
 *
 * 1.排序后递增
 *  先排序。
 *  遍历数组，如果当前值小于等于前面值，则需要增加操作数使得当前值大于前面值。以此类推。
 *  (小于等于因为会修改A[i]不满足排序的特性）
 *  最终求得操作数。
 * 时间复杂度O(NlogN)-排序的复杂度
 *
 * 2.计数法
 * 使用数组作为桶，统计每个值的个数。
 * 遍历桶
 * 当前桶内个数大于1，记录多出来的个数加到c上，并将操作数减去这些多出来数的和(操作数先减掉自己本身，这样后面直接加他要修改成为的数即为操作数了。反而不需要记录哪些值是多少了。)
 * 当前桶内个数为0，且c>0(有数字需要修改)，则拿一个数改为当前位置的值。操作数加当前值，并c减一。
 * 时间复杂度O(N+K)
 */


//排序后递增
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        if(A.size()==0) return 0;
        sort(A.begin(),A.end());
        int res = 0;
        for(int i=1;i<A.size();i++){
            //不能因为sort后只是用A[i]==A[i-1]
            //因为在修改A[i]的值啊，会破坏排好序的性质。
            if(A[i]<=A[i-1]){
                int sub = A[i-1] - A[i] + 1;
                res+=sub;
                A[i]+=sub;
            }
        }
        return res;
    }
};

//计数法
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {

        vector<int> count(40000+A.size(),0);
        int res = 0;
        int c = 0;
        for(auto i:A){
            count[i]++;
        }
        //count的范围0~40000+A.size()
        //由于最多40000个数，最坏情况39999个39999。需要扩展到80000啊
        for(int i=0;i<count.size();i++){
            if(count[i]>1){
                c += count[i] - 1;
                res -= i*(count[i] - 1); //操作数先减掉自己本身，这样后面直接加他要修改成为的数即为操作数了。反而不需要记录哪些值是多少了。
            }else if(c>0 && count[i]==0){
                res += i; //由于操作数都清零了，所以直接加当前的值为操作数。
                c--;
            }
        }
        return res;
    }
};


