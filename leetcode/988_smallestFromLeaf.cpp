// @File   : 988_smallestFromLeaf.cpp
// @Source : https://leetcode-cn.com/problems/smallest-string-starting-from-leaf/
// @Title  : 从叶结点开始的最小字符串
// @Auther : sun_ds
// @Date   : 2019/12/24

/**  题目描述：
    给定一颗根结点为 root 的二叉树，书中的每个结点都有一个从 0 到 25 的值，分别代表字母 'a' 到 'z'：值 0 代表 'a'，值 1 代表 'b'，依此类推。

    找出按字典序最小的字符串，该字符串从这棵树的一个叶结点开始，到根结点结束。

    （小贴士：字符串中任何较短的前缀在字典序上都是较小的：例如，在字典序上 "ab" 比 "aba" 要小。叶结点是指没有子结点的结点。）

     

    示例 1：



    输入：[0,1,2,3,4,3,4]
    输出："dba"
    示例 2：



    输入：[25,1,3,1,3,0,2]
    输出："adz"
    示例 3：



    输入：[2,2,1,null,1,0,null,0]
    输出："abc"
     

    提示：

    给定树的结点数介于 1 和 8500 之间。
    树中的每个结点都有一个介于 0 和 25 之间的值。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/smallest-string-starting-from-leaf
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 使用dfs遍历二叉树。
 * 在叶子节点处判断大小。
 * 保存最小，转换成字符串。
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
    string smallestFromLeaf(TreeNode* root) {
        deque<int> min_str;
        dfs(root,{},min_str);
        string res;
        for(auto i:min_str){
            res += i + 'a';
        }
        return res;
    }
    void dfs(TreeNode* root, deque<int> temp, deque<int> &min_str){
        if(root == NULL) return;
        temp.push_front(root->val);
        if(root->left == NULL && root->right == NULL){ //叶子节点
            if(min_str.size() == 0) min_str = temp;
            else if(temp < min_str) min_str = temp;
            return;
        }
        dfs(root->left,temp,min_str);
        dfs(root->right,temp,min_str);
    }
};
