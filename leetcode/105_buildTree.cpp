// @File   : 105_buildTree.cpp
// @Source : https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// @Title  : 从前序与中序遍历序列构造二叉树
// @Auther : sun_ds
// @Date   : 2020/2/18

/**  题目描述：
    根据一棵树的前序遍历与中序遍历构造二叉树。

    注意:
    你可以假设树中没有重复的元素。

    例如，给出

    前序遍历 preorder = [3,9,20,15,7]
    中序遍历 inorder = [9,3,15,20,7]
    返回如下的二叉树：

        3
       / \
      9  20
        /  \
       15   7


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 前序遍历：根 - 左 - 右
 * 中序遍历：左 - 根 - 右
 *
 * 因此，前序遍历的第一个值即为根节点。
 * 在中序遍历中找到与前序遍历中第一个值对应的位置。
 * 该位置的左面为当前根的整个左子树的元素，该位置的右面是当前根的整个右子树元素。
 * 中序遍历遍历以根为界限，拆分成两部分。 前序遍历根据中序遍历的左右子树元素个数，按照顺序也分成两部分，变成两个前序遍历。
 * 其中拆分后的每个前序遍历的第一个值仍未对应中序遍历的子树的根。
 *
 * 使用递归。
 * 依次执行。
 * 最终得到整个子树。
 *
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
    TreeNode* func(vector<int>& preorder, vector<int>& inorder, int index, int left, int right){
        if(left > right) return NULL;  //left == right 可以执行，只剩最后一个元素，他是叶子节点，左右子树都为null。
        TreeNode* root = new TreeNode(preorder[index]); //前序遍历的第一个值为根节点。
        int temp = left;
        while(inorder[temp] != preorder[index]) temp++; //在中序遍历中找到与根节点对应的坐标。前面为左子树，后面为右子树。
        // 拆分后的前序遍历的第一个位置分别为 index+1  和 index+1+左子树长度
        // temp对应中序中根节点对应的位置。
        // 中序左子树范围为 left，temp-1
        // 中序右子树范围为 temp+1 right
        root->left = func(preorder,inorder,index+1,left,temp-1);
        root->right = func(preorder,inorder,index+temp-left+1,temp+1,right);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return func(preorder,inorder,0,0,preorder.size()-1);
    }
};