// @File   : 35_copyRandomList.cpp
// @Source : https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/
// @Title  : 面试题35. 复杂链表的复制
// @Auther : sun_ds
// @Date   : 2020/3/26

/**  题目描述：
    请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

     

    示例 1：



    输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
    输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
    示例 2：



    输入：head = [[1,1],[2,1]]
    输出：[[1,1],[2,1]]
    示例 3：



    输入：head = [[3,null],[3,0],[3,null]]
    输出：[[3,null],[3,0],[3,null]]
    示例 4：

    输入：head = []
    输出：[]
    解释：给定的链表为空（空指针），因此返回 null。
     

    提示：

    -10000 <= Node.val <= 10000
    Node.random 为空（null）或指向链表中的节点。
    节点数目不超过 1000 。
     

    注意：本题与主站 138 题相同：https://leetcode-cn.com/problems/copy-list-with-random-pointer/

     

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.使用map
 * 第一次遍历创建新节点并存储当前节点与random节点的对应关系
 * 第二次遍历，根据map，更新random指针的指向
 * 2.dfs
 * 存储老节点和新节点对应的map
 * 从头开始递归构建。
 * 如果当前老节点在map中，说明他对应的新节点已经创建，直接返回。
 * 否则，为当前节点创建新节点，并添加他的next和random
 * 3.bfs
 * 使用队列
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* dummy = new Node(0);
        Node* temp = dummy;
        Node* t = head;
        unordered_map<Node*,Node*> m;
        while(t!=NULL){
            Node* node = new Node(t->val);
            m[t] = node;
            temp->next = node;
            temp = temp->next;
            t = t->next;
        }
        temp = dummy->next;
        t = head;
        while(t!=NULL){
            Node* node = t->random;
            temp->random = m[node];
            temp = temp->next;
            t = t->next;
        }
        return dummy->next;
    }
};


//迭代 精炼
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        unordered_map<Node*, Node*> mp;
        for (Node *it = head; it; it = it->next) {
            mp[it] = new Node(it->val);
        }
        for (Node *it = head; it; it = it->next) {
            if (it->next) mp[it]->next = mp[it->next];
            if (it->random) mp[it]->random = mp[it->random];
        }
        return mp[head];
    }
};

//dfs
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> used;
        return dfs(head, used);
    }

    Node* dfs(Node* head, unordered_map<Node*, Node*>& used) {
        if (!head) return nullptr;
        if (used.count(head)) return used[head];
        Node *res = new Node(head->val);
        used[head] = res;
        res->next = dfs(head->next, used);
        res->random = dfs(head->random, used);
        return res;
    }
};

//bfs
class Solution {
public:
    Node* copyRandomList(Node* head) {
        return bfs(head);
    }
    Node* bfs(Node* head) {
        if (!head) return nullptr;
        unordered_map<Node*, Node*> used;
        used[head] = new Node(head->val);
        queue<Node*> q;
        q.push(head);
        while (!q.empty()) {
            int siz = q.size();
            for (int i = 0; i < siz; i++) {
                Node *t = q.front(); q.pop();
                if (t->next) {
                    if (!used[t->next]) {
                        used[t->next] = new Node(t->next->val);
                        q.push(t->next);
                    }
                    used[t]->next = used[t->next];
                }
                if (t->random) {
                    if (!used[t->random]) {
                        used[t->random] = new Node(t->random->val);
                        q.push(t->random);
                    }
                    used[t]->random = used[t->random];
                }
            }
        }
        return used[head];
    }
};
