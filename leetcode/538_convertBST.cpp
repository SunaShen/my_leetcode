// @File   : 538_convertBST.cpp
// @Source : https://leetcode-cn.com/problems/convert-bst-to-greater-tree/
// @Title  : 538. 把二叉搜索树转换为累加树
// @Auther : sun_ds
// @Date   : 2020/9/21

/**  题目描述：
    给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树（Greater Tree)，使得每个节点的值是原来的节点值加上所有大于它的节点值之和。

     

    例如：

    输入: 原始二叉搜索树:
                  5
                /   \
               2     13

    输出: 转换为累加树:
                 18
                /   \
              20     13
     

    注意：本题和 1038: https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/ 相同



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/convert-bst-to-greater-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 反中序遍历
 *  右-根-左的顺序遍历，并一直累加 temp，更新节点值。
 *
 *  时间复杂度 O(N) N 为节点数
 *  空间复杂度 O(N) 递归栈，平均 O(LOG(N)),最坏 O(N)
 *
 */

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
private:
    int temp = 0;
public:
    void func(TreeNode* root){
        if(root == nullptr) return;
        func(root->right);
        root->val += temp;
        temp = root->val;
        func(root->left);
    }
    TreeNode* convertBST(TreeNode* root) {
        func(root);
        return root;
    }
};
