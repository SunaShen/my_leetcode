// @File   : 106_buildTree.cpp
// @Source : https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
// @Title  : 106. 从中序与后序遍历序列构造二叉树
// @Auther : sun_ds
// @Date   : 2020/9/25

/**  题目描述：
    根据一棵树的中序遍历与后序遍历构造二叉树。

    注意:
    你可以假设树中没有重复的元素。

    例如，给出

    中序遍历 inorder = [9,3,15,20,7]
    后序遍历 postorder = [9,15,7,20,3]
    返回如下的二叉树：

        3
       / \
      9  20
        /  \
       15   7

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.递归
 * 前序遍历：根 - 左 - 右
 * 中序遍历：左 - 根 - 右
 * 后序遍历：左 - 右 - 根
 *
 * 因此，后序遍历的最后一个值即为根节点。
 * 在中序遍历中找到与后序遍历中最后一个值对应的位置。
 * 该位置的左面为当前根的整个左子树的元素，该位置的右面是当前根的整个右子树元素。
 * 中序遍历遍历以根为界限，拆分成两部分。 后序遍历根据中序遍历的左右子树元素个数，按照顺序也分成两部分，变成两个后序遍历。
 * 其中拆分后的每个后序遍历的最后一个值仍为对应中序遍历的子树的根。
 *
 * 使用递归。
 * 依次执行。
 * 最终得到整个子树。
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
    TreeNode* func(vector<int>& inorder, vector<int>& postorder, int l, int r, int index){
        if(l>r) return nullptr;
        TreeNode* node = new TreeNode(postorder[index]);
        int mid = l;
        while(inorder[mid] != postorder[index]) mid++;
        node->left = func(inorder, postorder, l, mid - 1, index - (r - mid + 1));
        node->right = func(inorder, postorder, mid + 1, r, index - 1);
        return node;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return func(inorder, postorder, 0, inorder.size()-1, postorder.size()-1);
    }
};
