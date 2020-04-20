// @File   : 55-1_maxDepth.cpp
// @Source : https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof/
// @Title  : 面试题55 - I. 二叉树的深度
// @Auther : sun_ds
// @Date   : 2020/4/3

/**  题目描述：
    输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。

    例如：

    给定二叉树 [3,9,20,null,null,15,7]，

        3
       / \
      9  20
        /  \
       15   7
    返回它的最大深度 3 。

     

    提示：

    节点总数 <= 10000
    注意：本题与主站 104 题相同：https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.递归
 * 递归，记录最大深度。
 * 2.迭代
 * 可以使用stack(dfs)或queue(bfs)
 * 为了方便可以stack中放个pair<node,dep>
 * 对于queue可以按层序遍历，好统计层数=深度
 *
 *
 *
 */

//递归
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
    int res = 0;
public:
    void func(TreeNode* root,int depth){
        if(root==NULL) return;
        depth++;
        res = max(res,depth);
        func(root->left,depth);
        func(root->right,depth);
    }
    int maxDepth(TreeNode* root) {
        func(root,0);
        return res;
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
    int maxDepth(TreeNode* root) {
        return root==nullptr ? 0 : max(maxDepth(root->left),maxDepth(root->right))+1;
    }
};
//迭代
//stack dfs
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
    int maxDepth(TreeNode* root) {
        stack<pair<TreeNode*,int>> s;
        int res = 0;
        if(root) s.push(make_pair(root,1));
        while(!s.empty()){
            auto temp = s.top(); s.pop();
            auto node = temp.first;
            int dep = temp.second;
            res = max(res,dep);
            if(node->right){
                s.push(make_pair(node->right,dep+1));
            }
            if(node->left){
                s.push(make_pair(node->left,dep+1));
            }
        }
        return res;
    }
};
//queue bfs
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
    int maxDepth(TreeNode* root) {
        queue<pair<TreeNode*,int>> q;
        int res = 0;
        if(root) q.push(make_pair(root,1));
        while(!q.empty()){
            auto temp = q.front(); q.pop();
            auto node = temp.first;
            int dep = temp.second;
            res = max(res,dep);
            if(node->left){
                q.push(make_pair(node->left,dep+1));
            }
            if(node->right){
                q.push(make_pair(node->right,dep+1));
            }
        }
        return res;
    }
};
//queue 层序遍历
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
    int maxDepth(TreeNode* root) {
        queue<TreeNode*> q;
        int res = 0;
        if(root) q.push(root);
        TreeNode* temp;
        while(!q.empty()){
            res++;
            int len = q.size();
            for(int i=0;i<len;i++){
                temp = q.front(); q.pop();
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
            }
        }
        return res;
    }
};