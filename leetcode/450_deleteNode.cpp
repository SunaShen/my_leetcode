// @File   : 450_deleteNode.cpp
// @Source : https://leetcode-cn.com/problems/delete-node-in-a-bst/
// @Title  : 删除二叉搜索树中的节点
// @Auther : sun_ds
// @Date   : 2020/1/7

/**  题目描述：
    给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

    一般来说，删除节点可分为两个步骤：

    首先找到需要删除的节点；
    如果找到了，删除它。
    说明： 要求算法时间复杂度为 O(h)，h 为树的高度。

    示例:

    root = [5,3,6,2,4,null,7]
    key = 3

        5
       / \
      3   6
     / \   \
    2   4   7

    给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。

    一个正确的答案是 [5,4,6,2,null,null,7], 如下图所示。

        5
       / \
      4   6
     /     \
    2       7

    另一个正确答案是 [5,2,6,null,4,null,7]。

        5
       / \
      2   6
       \   \
        4   7

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/delete-node-in-a-bst
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 删除二叉搜索树中的指定元素
 *
 * 二叉搜索树中序遍历值升序排列。即 左子树所有值 < 根节点值 < 右子树所有值
 *
 * 首先，利用二叉搜索树特性，找到指定元素key。判断根节点值是否等于key,若不等于，若key<val搜索左子树，若key>val搜索右子树
 * 若没有找到key直接返回原二叉树
 * 要删除找到的key节点分为4种情况:
 *  1.当前key节点为叶子节点(无左右孩子) 直接删除当前叶子节点
 *  2.当前key节点有左孩子没有右孩子 将左孩子代替当前节点
 *  3.当前key节点有右孩子没有左孩子 将右孩子代替当前节点
 *  4.当前key节点有左孩子和右孩子 找到左子树中最大值m(左子树一路向右到叶子节点)，将key节点的值换为m并删除m节点 或 找到右子树中最小值m(右子树一路向左到叶子节点)，将key节点的值换为m并删除m节点
 *
 * 删除节点需要保存它的父节点，并需要知道它是父节点的左孩子还是右孩子。
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == NULL) return root;
        TreeNode* temp = root;
        //哑节点，方便删除根节点root。
        TreeNode* dummy = new TreeNode(0);
        dummy->left = root;
        TreeNode* p = dummy;
        int flag = 1;
        //p保存父节点，flag记录temp是左孩子还是右孩子
        //检索key
        while(temp != NULL){
            if(temp->val == key){
                break;
            }
            else if(temp->val > key){
                p = temp;
                flag = 1;
                temp = temp->left;
            }else{
                p = temp;
                flag = 0;
                temp = temp->right;
            }
        }
        //删除key节点
        //temp->val == key
        if(temp != NULL){   //找到
            if(temp->left == NULL && temp->right == NULL){ //叶子
                if(flag){
                    p->left = NULL;
                }
                else{
                    p->right = NULL;
                }
            }else if(temp->left != NULL && temp->right != NULL){ //包含左右孩子
                //找左子树的最大值。
                TreeNode* t = temp->left;
                TreeNode* p2;
                while(t->right != NULL && t->right->right != NULL){
                    t = t->right;
                }
                if(t->right == NULL){
                    temp->val = t->val;
                    temp->left = t->left;
                }
                else if(t->right->right == NULL){
                    temp->val = t->right->val;
                    t->right = t->right->left;
                }
            }else if(temp->right != NULL){ //只包含右孩子
                if(flag){
                    p->left = temp->right;
                }else{
                    p->right = temp->right;
                }
            }else if(temp->left != NULL){ //只包含左孩子
                if(flag){
                    p->left = temp->left;
                }else{
                    p->right = temp->left;
                }
            }
        }
        return dummy->left;
    }
};