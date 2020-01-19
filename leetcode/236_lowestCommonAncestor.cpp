// @File   : 236_lowestCommonAncestor.cpp
// @Source : https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
// @Title  : 二叉树的最近公共祖先
// @Auther : sun_ds
// @Date   : 2020/1/15

/**  题目描述：
    给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

    百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

    例如，给定如下二叉树:  root = [3,5,1,6,2,0,8,null,null,7,4]



     

    示例 1:

    输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
    输出: 3
    解释: 节点 5 和节点 1 的最近公共祖先是节点 3。
    示例 2:

    输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
    输出: 5
    解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
     

    说明:

    所有节点的值都是唯一的。
    p、q 为不同节点且均存在于给定的二叉树中。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.回溯法分别获得各个节点的祖先
 *   使用回溯法从根节点开始分别获得各个节点的所有祖先(包含自身)存储在temp_p,temp_q中。
 *   获得最近公共祖先，需要从前往后找到temp_p,temp_q中第一个不同的节点，即为最近公共节点。
 *
 * 2.后序遍历(递归)
 *      若root中只包含p则返回p
 *      若root中只包含q则返回q
 *      若root中不包含p也不包含q则返回NULL
 *      若root中同时包含p和q，则返回root（此时root为最近公共祖先）
 *
 *  先在找root的左子树的最近公共祖先得到返回值left， 再从右子树中查找最近公共祖先得到返回值right。
 *      若left为NULL，因为题目保证有解，所以答案必在右边
 *      若left不为NULL，则看right是否为NULL，若right为NULL， 则答案一定是左边这个left。
 *      若左右都不为NULL， 说明root在中间，p和q在两边。该根结点一定是最近公共祖先。
 *
 *  https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/leetcode236-er-cha-shu-de-zui-jin-gong-gong-zu-xia/
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
    bool recursion(TreeNode* root, TreeNode* p,vector<TreeNode*>& temp){
        temp.push_back(root);
        if(root == p) return true;
        if(root->left != NULL && recursion(root->left,p,temp)) return true;
        if(root->right != NULL && recursion(root->right,p,temp)) return true;
        temp.pop_back();
        return false;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root||!p||!q) return NULL;

        vector<TreeNode*> temp_p,temp_q;
        recursion(root, p, temp_p);
        recursion(root, q, temp_q);

        TreeNode* res;
        int len = min(temp_p.size(),temp_q.size());
        for(int i=0;i<len;++i){
            if(temp_p[i] != temp_q[i]) break;
            res = temp_p[i];
        }
        return res;
    }
};



//后序遍历(递归)
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
        // 若root包含p 返回p
        // 若root包含q 返回q
        // 若root都不包含 返回NULL
        // 若以root的子树中包含p和q 返回root(最近公共祖先)
        if (!root || root == p || root == q) return root;

        auto left = lowestCommonAncestor(root->left, p, q);
        auto right = lowestCommonAncestor(root->right, p, q);

        if (!left) return right;
        if (!right) return left;

        return root;
    }
};

