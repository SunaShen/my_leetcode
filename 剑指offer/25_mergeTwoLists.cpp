// @File   : 25_mergeTwoLists.cpp
// @Source : https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/
// @Title  : 面试题25. 合并两个排序的链表
// @Auther : sun_ds
// @Date   : 2020/3/10

/**  题目描述：
    输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

    示例1：

    输入：1->2->4, 1->3->4
    输出：1->1->2->3->4->4
    限制：

    0 <= 链表长度 <= 1000

    注意：本题与主站 21 题相同：https://leetcode-cn.com/problems/merge-two-sorted-lists/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 合并两个排序链表
 *
 * 起始点的选取。
 * 1.判断l1->val和l2->val的大小，选小的。然后后面循环。
 * 2.使用哑结点dummy。然后开始循环。
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1==NULL) return l2;
        if(l2==NULL) return l1;
        ListNode* head = NULL;
        if(l1->val>l2->val) {
            head = l2;
            l2 = l2->next;
        }else{
            head = l1;
            l1 = l1->next;
        }
        ListNode* temp = head;
        while(l1!=NULL||l2!=NULL){
            if(l1==NULL){
                temp->next = l2;
                temp = temp->next;
                l2 = l2->next;
            }else if(l2==NULL){
                temp->next = l1;
                temp = temp->next;
                l1 = l1->next;
            }else{
                if(l1->val>l2->val){
                    temp->next = l2;
                    temp = temp->next;
                    l2 = l2->next;
                }else{
                    temp->next = l1;
                    temp = temp->next;
                    l1 = l1->next;
                }
            }
        }
        return head;
    }
};


//哑结点
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;
        while(l1!=NULL&&l2!=NULL){
            if(l1->val > l2->val){
                cur->next = l2;
                l2 = l2->next;
            }else{
                cur->next = l1;
                l1 = l1->next;
            }
            cur = cur->next;
        }
        cur->next = l1!=NULL?l1:l2;
        return dummy->next;
    }
};

