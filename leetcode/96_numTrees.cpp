// @File   : 96_numTrees.cpp
// @Source : https://leetcode-cn.com/problems/unique-binary-search-trees/
// @Title  : 不同的二叉搜索树
// @Auther : sun_ds
// @Date   : 2019/12/28

/**  题目描述：
    给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？

    示例:

    输入: 3
    输出: 5
    解释:
    给定 n = 3, 一共有 5 种不同结构的二叉搜索树:

       1         3     3      2      1
        \       /     /      / \      \
         3     2     1      1   3      2
        /     /       \                 \
       2     1         2                 3

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/unique-binary-search-trees
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？
 *
 * 1.dp
 * 给定一个序列[1...n]，使用i作为根，则[1...i-1]和[i+1...n]分别组成左右子树。 i的取值为[1,n]。
 * [1...i-1]和[i+1...n]又可以看成是n=i-1,n-i的两个上述的问题。
 * 得到了最优子结构。
 * G[n]为长度为n的序列的不同二叉树个数 F(i,n)为以i为根的二叉树个数
 * G[n] = sum(F(i,n)) i=[1,n]。  其中G[0] = G[1] = 1。没有节点和只有一个节点都只有一种二叉树结构。
 * F(i,n)为以i为根的二叉树个数，以i为根得到[1...i-1]和[i+1...n]组成的左右子树。
 * 则F(i,n) = G(i-1)*G(n-i);
 *
 * 最终得到，G[n] = sum(G(i-1)*G(n-i)) i=[1,n]
 * 从小到大计算G[i]
 *
 * 最终G[n]为所求结果
 *
 * 时间复杂度O(n^2) 空间复杂度O(n)
 *
 * 2.数学
 * G[n]被称为卡塔兰数
 * 有 G[0] = 1 G[n+1] = [2*(2n+1)/(n+2)]*G[n]
 *
 * 时间复杂度O(n) 空间复杂度O(1)
 *
 *
 */

//dp
class Solution {
public:
    int numTrees(int n) {
        int dp[n+1] = {0};
        dp[0] = 1;
        dp[1] = 1;
        for(int i=2;i<=n;++i){
            for(int j=1;j<=i;++j)
                dp[i] += dp[j-1]*dp[i-j];
        }
        return dp[n];
    }
};


