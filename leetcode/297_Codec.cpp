// @File   : 297_Codec.cpp
// @Source : https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/
// @Title  : 297. 二叉树的序列化与反序列化
// @Auther : sun_ds
// @Date   : 2020/4/13

/**  题目描述：
    序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

    请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

    示例: 

    你可以将以下二叉树：

        1
       / \
      2   3
         / \
        4   5

    序列化为 "[1,2,3,null,null,4,5]"
    提示: 这与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

    说明: 不要使用类的成员 / 全局 / 静态变量来存储状态，你的序列化和反序列化算法应该是无状态的。



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 使用queue层序遍历
 * 序列化：使用queue层序遍历二叉树。左右孩子为null也要输出
 * 反序列化：对应的也是层序的构建，使用queue，并用i表示输入中的第i个节点。如果当前节点不为null就new新节点，否则就跳过。
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
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root==nullptr) return "[]";
        string res;
        queue<TreeNode*> q;
        q.push(root);
        //使用队列层序遍历
        while(!q.empty()){
            TreeNode* node = q.front();
            q.pop();
            if(node!=nullptr){
                res += to_string(node->val);
                res += ",";
                //左右孩子，就算是null也放进去
                q.push(node->left);
                q.push(node->right);
            }else{
                res += "null,";
            }
        }
        res[res.size()-1] = ']';//把最后一个","改成"]"
        res.insert(0,"[");//在最前面插入"["
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data=="[]") return nullptr;
        string s = data.substr(1,data.size()-2);    //去掉中括号"[","]".
        //使用stringstream 以 ","分割字符
        istringstream ss(s);
        string t;
        vector<string> num;
        while(getline(ss,t,',')){
            num.push_back(t);
        }

        //构造二叉树
        int i=0;    //使用i定位在string中的位置
        //使用queue 层序构建，跟上面保持一致
        queue<TreeNode*> q;
        TreeNode* root = new TreeNode(atoi(num[i++].c_str()));
        q.push(root);

        while(!q.empty()){
            TreeNode* temp = q.front();
            q.pop();
            //构建左孩子 如果为null就不构建了，下面直接i++跳过
            if(num[i]!="null"){
                temp->left = new TreeNode(atoi(num[i].c_str()));
                q.push(temp->left);
            }
            i++; //后移一位
            //构建右孩子 如果为null就不构建了，下面直接i++跳过
            if(num[i]!="null"){
                temp->right = new TreeNode(atoi(num[i].c_str()));
                q.push(temp->right);
            }
            i++; //后移一位
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

