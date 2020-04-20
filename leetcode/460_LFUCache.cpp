// @File   : 460_LFUCache.cpp
// @Source : https://leetcode-cn.com/problems/lfu-cache/
// @Title  : 460. LFU缓存
// @Auther : sun_ds
// @Date   : 2020/4/5

/**  题目描述：
    设计并实现最不经常使用（LFU）缓存的数据结构。它应该支持以下操作：get 和 put。

    get(key) - 如果键存在于缓存中，则获取键的值（总是正数），否则返回 -1。
    put(key, value) - 如果键不存在，请设置或插入值。当缓存达到其容量时，它应该在插入新项目之前，使最不经常使用的项目无效。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，最近最少使用的键将被去除。

    进阶：
    你是否可以在 O(1) 时间复杂度内执行两项操作？

    示例：

   LFUCache cache = new LFUCache( 2  );// capacity (缓存容量)
   cache.put(1, 1);
   cache.put(2, 2);
   cache.get(1);       // 返回 1
   cache.put(3, 3);    // 去除 key 2
   cache.get(2);       // 返回 -1 (未找到key 2)
   cache.get(3);       // 返回 3
   cache.put(4, 4);    // 去除 key 1
   cache.get(1);       // 返回 -1 (未找到 key 1)
   cache.get(3);       // 返回 3
   cache.get(4);       // 返回 4

   来源：力扣（LeetCode）
   链接：https://leetcode-cn.com/problems/lfu-cache
   著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 数据结构 map+2个list(cnt链表挂key链表)
 *
 * map保存key和node
 * 一个list保存cnt和list<int>的pair
 * 即对应的cnt的都一些node都挂在这个位置成一个新的链表包含对应cnt下的各个key。
 *
 *
 * node包含
 *   value 值
 *   cnt 调用次数
 *   cnt_pos 指向cnt链表，即指向对应的cnt的key链表。
 *   key_pos 指向对应的cnt的key链表中的对应的key位置。
 *
 *
 * 每次get对应的值，需要使得node的cnt+1，并将key放到新的cnt对应的链表的头部
 * 每次put对应的值
 * 如果已经存在，则更新value。并另cnt+1，并将key放到新的cnt对应的链表的头部。
 * 如果不存在，判断是否超过最大容量，如果超过容量，从cnt链表的表头挂的key链表的表尾删除一个节点。下面继续插入。
 * 如果不超过最大容量，则将cnt=1插入cnt链表中key链表的第一个位置。
 *
 *
 * 链表中只保存了cnt和对应cnt下的各个key
 * 真正的node保存在map中。
 *
 *
 *
 * 参考：
 * https://leetcode-cn.com/problems/lfu-cache/solution/shuo-de-ming-bai-by-jason-2/
 *
 */


class LFUCache {
private:
    int cap;
    list<pair<int,list<int>>> cnt_list;
    typedef list<pair<int,list<int>>>::iterator lli;
    typedef list<int>::iterator li;
    struct Node{
        int value;
        int cnt;
        lli cnt_pos;
        li key_pos;
        Node(int _cnt=0):cnt(_cnt){}
    };
    unordered_map<int,Node> m;
public:
    LFUCache(int capacity):cap(capacity){

    }

    int get(int key) {
        if(cap==0) return -1;
        if(m.count(key)){
            Node &node = m[key];
            update(key,node);
            return node.value;
        }else{
            return -1;
        }
    }

    void put(int key, int value) {
        if(cap==0) return;
        if(m.count(key)){
            Node &node=m[key];
            node.value = value;
            update(key,node);
        }else{
            //容量不足，需要删除
            if(m.size()>=cap){
                lli it = cnt_list.begin();
                int delete_key = it->second.back();
                it->second.pop_back();
                //删空了要删除节点
                if(it->second.empty()){
                    cnt_list.erase(it);
                }
                m.erase(delete_key);
            }
            //插入新的
            lli iter = cnt_list.begin();
            //如果没有cnt=1的位置，则添加个坑
            if(iter == cnt_list.end() || iter->first != 1){
                cnt_list.push_front(make_pair(1,list<int>()));
                iter = cnt_list.begin();
            }
            //新建节点
            Node n;
            n.value = value;
            n.cnt = 1;
            n.cnt_pos = iter;
            iter->second.push_front(key);
            n.key_pos = iter->second.begin();
            m[key] = n;
        }
    }

    void update(int key, Node& n){
        n.cnt++;
        lli next_cnt_pos = next(n.cnt_pos);
        //cnt次节点不存在，需要新建
        if(next_cnt_pos==cnt_list.end()||next_cnt_pos->first!=n.cnt){
            next_cnt_pos = cnt_list.insert(next_cnt_pos,make_pair(n.cnt,list<int>()));
        }
        //取下当前
        n.cnt_pos->second.erase(n.key_pos);
        //若cnt空了 删除节点
        if(n.cnt_pos->second.empty()){
            cnt_list.erase(n.cnt_pos);
        }
        //插入新的
        n.cnt_pos = next_cnt_pos;
        n.cnt_pos->second.push_front(key);
        n.key_pos = n.cnt_pos->second.begin();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


