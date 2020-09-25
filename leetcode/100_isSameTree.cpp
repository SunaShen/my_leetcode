// @File   : 100_isSameTree.cpp
// @Source : https://leetcode-cn.com/problems/same-tree/
// @Title  : 100. 相同的树
// @Auther : sun_ds
// @Date   : 2020/8/7

/**  题目描述：
    给定两个二叉树，编写一个函数来检验它们是否相同。

    如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

    示例 1:

    输入:       1         1
              / \       / \
             2   3     2   3

            [1,2,3],   [1,2,3]

    输出: true
    示例 2:

    输入:      1          1
              /           \
             2             2

            [1,2],     [1,null,2]

    输出: false
    示例 3:

    输入:       1         1
              / \       / \
             2   1     1   2

            [1,2,1],   [1,1,2]

    输出: false

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/same-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dfs
 *  同时遍历各个节点。
 *  出现不一致返回 false，否则一直向下。
 *
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        } else if (p == nullptr || q == nullptr) {
            return false;
        } else {
            if (p->val == q->val) {
                return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
            } else {
                return false;
            }
        }
    }
};
