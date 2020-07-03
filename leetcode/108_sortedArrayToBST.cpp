// @File   : 108_sortedArrayToBST.cpp
// @Source : https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/
// @Title  : 108. 将有序数组转换为二叉搜索树
// @Auther : sun_ds
// @Date   : 2020/7/3

/**  题目描述：
    将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。

    本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

    示例:

    给定有序数组: [-10,-3,0,5,9],

    一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：

          0
         / \
       -3   9
       /   /
     -10  5

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.递归
 * 平衡二叉树，中间的值为根节点，左右两部分分别为左子树和右子树。
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
    TreeNode* func(vector<int>& nums,int l,int r,int mid){
        if(l>r) return nullptr;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = func(nums,l,mid-1,(l+mid-1)/2);
        root->right = func(nums,mid+1,r,(mid+1+r)/2);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int m = nums.size();
        return func(nums,0,m-1,(m-1)/2);
    }
};

