// @File   : 543_diameterOfBinaryTree.cpp
// @Source : https://leetcode-cn.com/problems/diameter-of-binary-tree/
// @Title  : 543. 二叉树的直径
// @Auther : sun_ds
// @Date   : 2020/3/10

/**  题目描述：
    给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过根结点。

    示例 :
    给定二叉树

              1
             / \
            2   3
           / \
          4   5
    返回 3, 它的长度是路径 [4,2,1,3] 或者 [5,2,1,3]。

    注意：两结点之间的路径长度是以它们之间边的数目表示。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/diameter-of-binary-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 二叉树直径
 *
 * 1.dfs
 *  二叉树直径即其中各节点的最长路径，与树的深度有关。
 *  当前节点为根的树的半径 = max{左子树的半径，右子树的半径，左子树深度+右子树深度}
 *
 *  dfs遍历每个节点。
 *
 *  使用全局变量res记录出现的最长路径即为树的直径
 *
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
    int res = 0;
    int dfs(TreeNode* root){
        if(root==NULL) return 0;
        int left = dfs(root->left);
        int right = dfs(root->right);
        res = max(res,left+right);
        return 1+max(left,right);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return res;
    }
};
