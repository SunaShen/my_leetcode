// @File   : 82_deleteDuplicates.cpp
// @Source : https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/
// @Title  : 删除排序链表中的重复元素 II
// @Auther : sun_ds
// @Date   : 2019/11/12

/*  题目描述：
    给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。

    示例 1:

    输入: 1->2->3->3->4->4->5
    输出: 1->2->5
    示例 2:

    输入: 1->1->1->2->3
    输出: 2->3

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 * 删除链表中重复元素
 *
 * 双指针
 * 一个指向前面节点，一个向前检索
 *
 * 通过i来统计同一数字出现的次数，大于0即为有重复。
 * 删除中间节点
 *
 * 注意最后一组数，需要在循环外单独判断i。
 *
 *
 * 使用dummy
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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==NULL||head->next==NULL)
            return head;
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* p1 = dummy;
        ListNode* p2 = head;
        int i=0;
        while(p2->next){
            if(p2->val!=p2->next->val){
                if(i==0)
                {
                    p1 = p1->next;
                }else{
                    p1->next = p2->next;
                }
                i=0;
            }else{
                ++i;
            }
            p2 = p2->next;
        }
        if(i) p1->next = NULL;
        return dummy->next;
    }
};