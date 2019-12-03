// @File   : 112_hasPathSum.cpp
// @Source : https://leetcode-cn.com/problems/path-sum/
// @Title  : 路径总和
// @Auther : sun_ds
// @Date   : 2019/10/16

/*  题目描述：
    给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。

    说明: 叶子节点是指没有子节点的节点。

    示例: 
    给定如下二叉树，以及目标和 sum = 22，

                  5
                 / \
                4   8
               /   / \
              11  13  4
             /  \      \
            7    2      1
    返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/path-sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 *
 * 二叉树路径和
 * 前序遍历二叉树，节点处判断是否满足条件
 *
 */


//class Solution {
//public:
//    int r = 0, flag = 0;
//    void fun(TreeNode *root, int curr){
//        curr += root->val;
//        cout << curr << endl;
//        if(root->left||root->right){
//            if(root->left)
//                fun(root->left, curr);
//            if(root->right)
//                fun(root->right, curr);
//        }else{
//            if(curr==r){
//                flag = 1;
//                cout << curr << endl;
//            }
//        }
//    }
//    bool hasPathSum(TreeNode* root, int sum) {
//        if(!root)
//            return false;
//        r = sum;
//        fun(root, 0);
//        return flag==1;
//    }
//};


class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
//        子节点
        if((!root->left)&&(!root->right)) return root->val == sum;
//        if(root->left) return hasPathSum(root->left,sum-root->val);
//        if(root->right) return hasPathSum(root->right,sum->root->val);
        if(hasPathSum(root->left,sum-root->val)) return true;
        if(hasPathSum(root->right,sum-root->val)) return true;
        return false;
    }
};