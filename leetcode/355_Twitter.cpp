// @File   : 355_Twitter.cpp
// @Source : https://leetcode-cn.com/problems/design-twitter/
// @Title  : 355. 设计推特
// @Auther : sun_ds
// @Date   : 2020/4/13

/**  题目描述：
    设计一个简化版的推特(Twitter)，可以让用户实现发送推文，关注/取消关注其他用户，能够看见关注人（包括自己）的最近十条推文。你的设计需要支持以下的几个功能：

    postTweet(userId, tweetId): 创建一条新的推文
    getNewsFeed(userId): 检索最近的十条推文。每个推文都必须是由此用户关注的人或者是用户自己发出的。推文必须按照时间顺序由最近的开始排序。
    follow(followerId, followeeId): 关注一个用户
    unfollow(followerId, followeeId): 取消关注一个用户
    示例:

    Twitter twitter = new Twitter();

    // 用户1发送了一条新推文 (用户id = 1, 推文id = 5).
    twitter.postTweet(1, 5);

    // 用户1的获取推文应当返回一个列表，其中包含一个id为5的推文.
    twitter.getNewsFeed(1);

    // 用户1关注了用户2.
    twitter.follow(1, 2);

    // 用户2发送了一个新推文 (推文id = 6).
    twitter.postTweet(2, 6);

    // 用户1的获取推文应当返回一个列表，其中包含两个推文，id分别为 -> [6, 5].
    // 推文id6应当在推文id5之前，因为它是在5之后发送的.
    twitter.getNewsFeed(1);

    // 用户1取消关注了用户2.
    twitter.unfollow(1, 2);

    // 用户1的获取推文应当返回一个列表，其中包含一个id为5的推文.
    // 因为用户1已经不再关注用户2.
    twitter.getNewsFeed(1);

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/design-twitter
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * cotent存储内容节点，包括tweetId(内容id),time(时间),next(该用户上一条内容)
 * cotent组成用户的内容链表(单向链表，头部插入)(默认排序)
 * node存储用户节点，包括c(内容节点链表头节点指针),id(用户id),follow_id(关注用户的id集合)
 *
 * 用户id没有规律。使用map存储用户id和其对应的node，方便查找。
 *
 * 关注用户、取关用户 只用操作对应用户节点的follow_id。时间复杂度O(1)
 * 发布推文，需要在用户节点的内容链表头增加内容节点。时间复杂度O(1)
 *
 * 查询当前用户和关注用户的前k条推文(时间倒序)，即合并多个用户的内容链表(已排序)
 * 使用优先队列，取出各内容链表中的前k个。
 *
 * 时间复杂度 klogn 其中k为前k个，n为用户自己+关注用户个数(即优先队列中堆的大小)
 *
 *
 */


struct content{
    int tweetId;
    long long time;
    content *next;
    content(int _tweetId,long long _time,content* _next):tweetId(_tweetId),time(_time),next(_next){}
};
class node{
public:
    content* c;
    int id;
    unordered_set<int> follow_id;
    node():c(nullptr){}
};
class Twitter {
    long long time;
    unordered_map<int,node> user;
public:
    /** Initialize your data structure here. */
    Twitter() {
        time = 0;
        user.clear();
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        time++;
        if(user.count(userId)==0){  //没有该用户
            node temp;
            temp.id = userId;
            content *c = new content(tweetId,time,temp.c);
            temp.c = c;
            user.insert(make_pair(userId,temp));
        }else{
            node temp = user[userId];
            content *c = new content(tweetId,time,temp.c);
            temp.c = c;
            user[userId] = temp;
        }
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        if(user.count(userId)==0){
            return {};
        }else{
            vector<int> res;
            vector<int> index = {userId};
            node temp = user[userId];
            for(auto iter = temp.follow_id.begin();iter!=temp.follow_id.end();iter++){
                if(user.count(*iter)!= 0){
                    index.push_back(*iter);
                }
            }
            auto cmp = [](content& a, content& b){return a.time < b.time;};
            priority_queue<content,vector<content>,decltype(cmp)> q(cmp);
            for(auto i:index){
                if(user[i].c!=nullptr){
                    content temp = *user[i].c;
                    q.push(temp);
                }
            }

            for(int i=0;!q.empty()&&i<10;i++){
                content t = q.top();
                q.pop();
                res.push_back(t.tweetId);
                if(t.next!=nullptr){
                    content tt = *(t.next);
                    q.push(tt);
                }
            }
            return res;
        }
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if(followerId==followeeId) return;
        if(user.count(followerId)==0){  //没有该用户
            node temp;
            temp.id = followerId;
            temp.follow_id.insert(followeeId);
            user.insert(make_pair(followerId,temp));
        }else{
            node temp = user[followerId];
            temp.follow_id.insert(followeeId);
            user[followerId] = temp;
        }
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if(user.count(followerId)!=0){  //没有该用户
            node temp = user[followerId];
            temp.follow_id.erase(followeeId);
            user[followerId] = temp;
        }
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

