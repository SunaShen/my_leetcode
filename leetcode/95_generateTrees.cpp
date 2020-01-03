// @File   : 95_generateTrees.cpp
// @Source : https://leetcode-cn.com/problems/unique-binary-search-trees-ii/
// @Title  : 不同的二叉搜索树 II
// @Auther : sun_ds
// @Date   : 2019/12/30

/**  题目描述：
    给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

    示例:

    输入: 3
    输出:
    [
      [1,null,3,2],
      [3,2,null,1],
      [3,1,null,null,2],
      [2,1,3],
      [1,null,2,null,3]
    ]
    解释:
    以上的输出对应以下 5 种不同结构的二叉搜索树：

       1         3     3      2      1
        \       /     /      / \      \
         3     2     1      1   3      2
        /     /       \                 \
       2     1         2                 3

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/unique-binary-search-trees-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 递归
 * 终止条件，start>end，写入null
 * i的范围[1，n] for循环
 * 以i为根节点，[1,i-1]为左子树，[i+1,n]为右子树
 * 左子树，右子树继续调用递归。
 * 使用左右子树的返回值，两层for循环继续组合新的结构。
 * 最终得到所有的结果
 *
 */

//递归
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> func(int start, int end){
        vector<TreeNode*> temp;
        if(start > end)
            temp.push_back(nullptr);
        for(int i=start;i<=end;++i){
            vector<TreeNode*> l = func(start,i-1);
            vector<TreeNode*> r = func(i+1,end);
            for(auto j:l){
                for(auto k:r){
                    TreeNode *node = new TreeNode(i);
                    node->left = j;
                    node->right = k;
                    temp.push_back(node);
                }
            }
        }
        return temp;
    }
    vector<TreeNode*> generateTrees(int n) {
        if(n == 0)
            return {};
        return func(1,n);
    }
};