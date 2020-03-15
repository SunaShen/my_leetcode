// @File   : 27_mirrorTree.cpp
// @Source : https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof/
// @Title  : 面试题27. 二叉树的镜像
// @Auther : sun_ds
// @Date   : 2020/3/11

/**  题目描述：
    请完成一个函数，输入一个二叉树，该函数输出它的镜像。

    例如输入：

         4
       /   \
      2     7
     / \   / \
    1   3 6   9
    镜像输出：

         4
       /   \
      7     2
     / \   / \
    9   6 3   1

     

    示例 1：

    输入：root = [4,2,7,1,3,6,9]
    输出：[4,7,2,9,6,3,1]
     

    限制：

    0 <= 节点个数 <= 1000

    注意：本题与主站 226 题相同：https://leetcode-cn.com/problems/invert-binary-tree/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 镜像二叉树
 * 交换左右子树
 * 递归到每一层
 *
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
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if(root==NULL) return NULL;
        mirrorTree(root->left);
        mirrorTree(root->right);
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        return root;
    }
};
