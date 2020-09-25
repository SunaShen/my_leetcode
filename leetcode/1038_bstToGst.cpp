// @File   : 1038_bstToGst.cpp
// @Source : https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/
// @Title  : 1038. 从二叉搜索树到更大和树
// @Auther : sun_ds
// @Date   : 2020/9/21

/**  题目描述：
    给出二叉 搜索 树的根节点，该二叉树的节点值各不相同，修改二叉树，使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

    提醒一下，二叉搜索树满足下列约束条件：

    节点的左子树仅包含键 小于 节点键的节点。
    节点的右子树仅包含键 大于 节点键的节点。
    左右子树也必须是二叉搜索树。
     

    示例：



    输入：[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    输出：[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
     

    提示：

    树中的节点数介于 1 和 100 之间。
    每个节点的值介于 0 和 100 之间。
    给定的树为二叉搜索树。
     

    注意：该题目与 538: https://leetcode-cn.com/problems/convert-bst-to-greater-tree/  相同

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 反中序遍历
 *  右-根-左顺序遍历，每次累加值替换当前值。
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
    TreeNode* bstToGst(TreeNode* root) {
        if(root == nullptr) return nullptr;
        bstToGst(root->right);
        temp += root->val;
        root->val = temp;
        bstToGst(root->left);
        return root;
    }
};
