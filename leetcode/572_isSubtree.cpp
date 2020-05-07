// @File   : 572_isSubtree.cpp
// @Source : https://leetcode-cn.com/problems/subtree-of-another-tree/
// @Title  : 572. 另一个树的子树
// @Auther : sun_ds
// @Date   : 2020/5/7

/**  题目描述：
    给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。

    示例 1:
    给定的树 s:

         3
        / \
       4   5
      / \
     1   2
    给定的树 t：

       4
      / \
     1   2
    返回 true，因为 t 与 s 的一个子树拥有相同的结构和节点值。

    示例 2:
    给定的树 s：

         3
        / \
       4   5
      / \
     1   2
        /
       0
    给定的树 t：

       4
      / \
     1   2
    返回 false。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/subtree-of-another-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.暴力法 dfs
 * dfs每个节点与t的起点对应，在接着判断下去。
 * 时间复杂度O(S*T) 两颗树的节点数乘积
 *
 * 2.dfs序列 + KMP
 * 生成各个树的前序遍历序列(包含null节点,没有null节点不是唯一匹配)
 * 问题转换成从s序列中找到是否有t序列
 * 使用KMP方法来查找
 * 时间复杂度O(S+T)
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
    bool check(TreeNode* s, TreeNode* t){
        if(s==nullptr&&t==nullptr) return true;
        if((s==nullptr&&t!=nullptr)||(s!=nullptr&&t==nullptr)) return false;
        return (s->val==t->val)&&check(s->left,t->left)&&check(s->right,t->right);
    }
    bool dfs(TreeNode* s, TreeNode* t){
        if(s==nullptr) return false;
        return check(s,t)||dfs(s->left,t)||dfs(s->right,t);
    }
    bool isSubtree(TreeNode* s, TreeNode* t) {
        return dfs(s,t);
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
    void get_order(TreeNode* node,vector<int>& order){
        if(node==nullptr){
            //必须输出null节点，不然不是唯一匹配
            //代表null
            order.push_back(INT_MAX);
            return ;
        }
        order.push_back(node->val);
        get_order(node->left,order);
        get_order(node->right,order);
    }
    bool kmp(vector<int>& s_order,vector<int>& t_order){
        int len_s = s_order.size();
        int len_t = t_order.size();
        vector<int> next(len_t+1,-1);
        int i=0,j=-1;
        while(i<len_t){
            while(j>=0&&t_order[i]!=t_order[j]) j = next[j];
            i++;
            j++;
            next[i] = j;
        }

        i=0,j=0;
        while(i<len_s){
            while(j>=0&&s_order[i]!=t_order[j]) j = next[j];
            i++;
            j++;
            if(j==len_t) return true;
        }
        return false;
    }
    bool isSubtree(TreeNode* s, TreeNode* t) {
        vector<int> s_order;
        vector<int> t_order;

        get_order(s,s_order);
        get_order(t,t_order);

        return kmp(s_order,t_order);
    }
};
