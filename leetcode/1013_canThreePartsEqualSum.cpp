// @File   : 1013_canThreePartsEqualSum.cpp
// @Source : https://leetcode-cn.com/problems/partition-array-into-three-parts-with-equal-sum/
// @Title  : 1013. 将数组分成和相等的三个部分
// @Auther : sun_ds
// @Date   : 2020/3/11

/**  题目描述：
    给你一个整数数组 A，只有可以将其划分为三个和相等的非空部分时才返回 true，否则返回 false。

    形式上，如果可以找出索引 i+1 < j 且满足 (A[0] + A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... + A[A.length - 1]) 就可以将数组三等分。

     

    示例 1：

    输出：[0,2,1,-6,6,-7,9,1,2,0,1]
    输出：true
    解释：0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1
    示例 2：

    输入：[0,2,1,-6,6,7,9,-1,2,0,1]
    输出：false
    示例 3：

    输入：[3,3,6,5,-2,2,5,1,-9,4]
    输出：true
    解释：3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4
     

    提示：

    3 <= A.length <= 50000
    -10^4 <= A[i] <= 10^4

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/partition-array-into-three-parts-with-equal-sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 能够分成三段，则数组的和肯定能被3整除。
 * 遍历数组，找到第一段满足和等于sum/3的位置。
 * 继续遍历找到第二段和等于sum/3的位置。
 * 并且他后面还有元素，则第三段自然满足等于sum/3
 *
 *
 *
 */

//前面加一段这个减少运行时间
//lambda函数
static const auto _ = []()
{
    ios::sync_with_stdio(false); //设置在每次输入/输出操作后标准C ++流是否与标准C流同步 解除之后不能用scanf，printf
    cin.tie(nullptr); //解除std :: cin和std :: cout之间的绑定，不用每次操作的时候（也就是调用”<<”或者”>>”）都要刷新（调用flush)
    return nullptr;
}();
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int n = A.size();
        int sum = 0;
        for(auto i:A) sum+=i;
        if(sum%3!=0) return false;
        int index=0;
        //判断前两部分满足，第三部分自然满足了
        for(int i=0;i<2;i++){
            int temp=0;
            while(index<n){
                temp+=A[index++];
                if(temp==sum/3)
                    break;
            }
        }
        //给第三段留点空间
        return index!=n;
    }
};


