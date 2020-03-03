// @File   : 146_LRUCache.cpp
// @Source : https://leetcode-cn.com/problems/lru-cache/
// @Title  : 146. LRU缓存机制
// @Auther : sun_ds
// @Date   : 2020/3/1

/**  题目描述：
    运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

    获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
    写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

    进阶:

    你是否可以在 O(1) 时间复杂度内完成这两种操作？

    示例:

    LRUCache cache = new LRUCache( 2 ); //2 缓存容量

    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);       // 返回  1
    cache.put(3, 3);    // 该操作会使得密钥 2 作废
    cache.get(2);       // 返回 -1 (未找到)
    cache.put(4, 4);    // 该操作会使得密钥 1 作废
    cache.get(1);       // 返回 -1 (未找到)
    cache.get(3);       // 返回  3
    cache.get(4);       // 返回  4

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/lru-cache
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *  LRU (最近最少使用) 缓存机制
 *
 *  LRU就是一种缓存淘汰策略。
 *  计算机的缓存容量有限，如果缓存满了就要删除一些内容，给新内容腾位置。但问题是，删除哪些内容呢？
 *  我们肯定希望删掉哪些没什么用的缓存，而把有用的数据继续留在缓存里，方便之后继续使用。
 *  那么，什么样的数据，我们判定为「有用的」的数据呢？
 *  LRU 缓存淘汰算法就是一种常用策略。
 *  LRU 的全称是 Least Recently Used，也就是说我们认为最近使用过的数据应该是是「有用的」，很久都没用过的数据应该是无用的，内存满了就优先删那些很久没用过的数据。
 *
 *  作者：labuladong
 *  链接：https://leetcode-cn.com/problems/lru-cache/solution/lru-ce-lue-xiang-jie-he-shi-xian-by-labuladong/
 *  来源：力扣（LeetCode）
 *  著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 * 题目要求实现 LRU 缓存机制，需要在 O(1) 时间内完成如下操作：
 *  1.获取键 / 检查键是否存在
 *  2.设置键
 *  3.删除最先插入的键
 *
 * 获取键值对，使用map。
 * 维护先后调用顺序，使用双向链表。表头是最近调用的，表尾是最久调用的。
 *
 * 双向链表作用，再删除表尾时，新的tail要指向前一个元素。
 * 若为单向链表，在更新表尾指针时，需要重新从表头遍历。
 *
 *
 */




/**
 * Definition of cachelist node, it's double linked list node.
 */
struct CacheNode {
    int key;
    int value;
    CacheNode *pre, *next;
    CacheNode(int k, int v) : key(k), value(v), pre(NULL), next(NULL) {}
};

class LRUCache {
private:
    int size;
    CacheNode *head, *tail;
    map<int,CacheNode *> mp;
public:
    LRUCache(int capacity) {
        size = capacity;
        head = NULL;
        tail = NULL;
        mp.clear();
    }

    int get(int key) {
        map<int, CacheNode *>::iterator it = mp.find(key);
        if(it != mp.end()){
            CacheNode *node = it->second;
            remove(node);
            setHead(node);
            return node->value;
        }else{
            return -1;
        }
    }

    void put(int key, int value) {
        map<int, CacheNode *>::iterator it = mp.find(key);
        if(it != mp.end()){
            CacheNode *node = it->second;
            remove(node);
            setHead(node);
            node->value = value;
        }else{
            CacheNode *node = new CacheNode(key,value);
            if(mp.size() >= size){
                map<int, CacheNode *>::iterator iter = mp.find(tail -> key);
                remove(tail);
                mp.erase(iter);
            }
            setHead(node);
            mp[key] = node;
        }

    }

    void remove(CacheNode *node){
        if(node->next != NULL){
            node->next->pre = node->pre;
        }else{
            tail = node->pre;
        }
        if(node->pre != NULL){
            node->pre->next = node->next;
        }else{
            head = node->next;
        }
    }

    void setHead(CacheNode *node){
        node->pre = NULL;
        node->next = head;
        if(head != NULL){
            head->pre = node;
        }
        if(tail == NULL){
            tail = node;
        }
        head = node;
    }
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


// 迭代器
// https://leetcode-cn.com/problems/lru-cache/solution/lru-cshi-xian-by-bao-bao-ke-guai-liao/
class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        if (hash_.find(key) == hash_.end())
            return -1;
        else {
            int value = hash_[key]->second;
            ls_.erase(hash_[key]);
            ls_.push_front(make_pair(key, value));
            hash_[key] = ls_.begin();
            return value;
        }
    }

    void put(int key, int value) {
        if (hash_.find(key) != hash_.end())
            ls_.erase(hash_[key]);
        else if (ls_.size() >= capacity_) {
            hash_.erase(ls_.back().first);
            ls_.pop_back();
        }
        ls_.push_front(make_pair(key, value));
        hash_[key] = ls_.begin();
    }

private:
    int capacity_;
    list<pair<int, int>> ls_;
    unordered_map<int, list<pair<int, int>>::iterator> hash_;
};


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


