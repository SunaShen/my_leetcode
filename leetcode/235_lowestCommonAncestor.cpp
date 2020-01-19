// @File   : 235_lowestCommonAncestor.cpp
// @Source : https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// @Title  : 二叉搜索树的最近公共祖先
// @Auther : sun_ds
// @Date   : 2020/1/14

/**  题目描述：
    给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

    百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

    例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]



     

    示例 1:

    输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
    输出: 6
    解释: 节点 2 和节点 8 的最近公共祖先是 6。
    示例 2:

    输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
    输出: 2
    解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。
     

    说明:

    所有节点的值都是唯一的。
    p、q 为不同节点且均存在于给定的二叉搜索树中。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 返回二叉搜索树中两个节点最近的公共祖先
 *
 * 1.分别获取各个节点的祖先，求最近公共祖先
 *  利用搜索二叉树性质，分别使用递归获取各节点p,q的祖先temp_p,temp_q(包含本身)。
 *  获得最近公共祖先，需要从前往后找到temp_p,temp_q中第一个不同的节点，即为最近公共节点。
 *
 *
 * 2.迭代法
 *  将该问题进一步简化最近公共祖先问题(LCA)。
 *      p,q都在当前节点的右子树，以右孩子为节点继续LCA
 *      p,q都在当前节点的左子树，以左孩子为节点继续LCA
 *      否则，即当前节点为p或q，则当前节点就是最近公共祖先。返回。
 *
 *  树为二叉搜索树，所以可以很简单的通过val来判断p,q是在当前节点的左还是右子树。
 *
 *  时间复杂度O(n) 空间复杂度O(1)
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
    void recursion(TreeNode* root, TreeNode* p,vector<TreeNode*>& temp){
        temp.push_back(root);   //包含本身
        if(root == p) return;
        if(root->val > p->val){
            recursion(root->left,p,temp);
        }else{
            recursion(root->right,p,temp);
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> temp_p,temp_q;
        recursion(root, p, temp_p);
        recursion(root, q, temp_q);
        //由各节点祖先得出最近公共祖先
        int i=0;
        for(;i<temp_p.size()&&i<temp_q.size();++i){
            if(temp_p[i] != temp_q[i]) return temp_p[i-1];
        }
        return temp_p[i-1];
    }
};


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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int val_p = p->val;
        int val_q = q->val;
        TreeNode* node = root;
        while(node != NULL){
            if(node->val>val_p&&node->val>val_q){
                node = node->left;
            }else if(node->val<val_p&&node->val<val_q){
                node = node->right;
            }else{
                return node;
            }
        }
        return NULL;
    }
};


