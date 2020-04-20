// @File   : 23_mergeKLists.cpp
// @Source : https://leetcode-cn.com/problems/merge-k-sorted-lists/
// @Title  : 23. 合并K个排序链表
// @Auther : sun_ds
// @Date   : 2020/4/13

/**  题目描述：
    合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。

    示例:

    输入:
    [
      1->4->5,
      1->3->4,
      2->6
    ]
    输出: 1->1->2->3->4->4->5->6

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/merge-k-sorted-lists
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 合并K个排序链表
 *
 * 使用优先队列。
 *
 *
 *
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    struct cmp{
        bool operator()(const ListNode* a, const ListNode* b){
            return a->val > b->val;
        }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*,vector<ListNode*>,cmp> q;
        //各链表的头节点插入优先队列
        for(int i=0;i<lists.size();i++){
            if(lists[i]!=nullptr){
                q.push(lists[i]);
            }
        }
        //每次从堆顶取节点，并将该节点下一个节点入堆(如果有的话）
        ListNode* dummy = new ListNode(-1);
        ListNode* temp = dummy;
        while(!q.empty()){
            ListNode* t = q.top();
            q.pop();
            if(t->next!=nullptr){
                q.push(t->next);
            }
            temp->next = t;
            temp = temp->next;
        }
        return dummy->next;
    }
};

