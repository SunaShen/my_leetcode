// @File   : 20_isNumber.cpp
// @Source : https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/
// @Title  : 面试题20. 表示数值的字符串
// @Auther : sun_ds
// @Date   : 2020/3/8

/**  题目描述：
    请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100"、"5e2"、"-123"、"3.1416"、"0123"及"-1E-16"都表示数值，但"12e"、"1a3.14"、"1.2.3"、"+-5"及"12e+5.4"都不是。

     

    注意：本题与主站 65 题相同：https://leetcode-cn.com/problems/valid-number/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 就硬分类
 * 1.首先过滤掉前面的空格
 * 2.只能有一个e
 * 3.e分成两部分，前后部分都只能包含1个'+'或'-'且都必须在每部分开头位置 (判断开头位置，前面为' '或前面为'e')
 * 4.e分成两部分，只有前面部分能够包含1个'.'
 * 5.e前后必须有数字
 * 6.由于首先过滤掉了最前面的空格，所以后续再遇到空格就必须一路空格到底。且空格前面必须有数字。
 *
 *
 *
 */

class Solution {
public:
    bool isNumber(string s) {
        int e_flag = 0, pn_flag = 0, point_flag = 0, num_flag = 0;
        int i=0;
        //前面过滤空格
        while(i<s.size()&&s[i]==' ') i++;
        for(;i<s.size();i++){
            if(('0'<=s[i]&&s[i]<='9')){
                num_flag = 1; //有数字了
            }else if(s[i]=='e' || s[i]=='E'){
                if(e_flag==0&&num_flag!=0){
                    e_flag = 1; //第1个e
                    pn_flag = 0; //e后面正负号另算
                    point_flag = 1; //e后面不能有'.'
                    num_flag = 0; //e后面必须有数字
                }
                else return false; //不能出现多于1个e
            }else if(s[i]=='+'||s[i]=='-'){
                // '+''-'只能出现在开头(所以他必须是第一个或者他前面是空格)或e后面
                // pn_flag控制只能出现一次
                if(pn_flag==1||(i >= 1 && s[i-1] != ' ' && (s[i-1] != 'e' && s[i-1] != 'E'))) return false;
                pn_flag = 1;
            }else if(s[i]=='.'){
                if(point_flag==1) return false; //已经有‘.’了
                point_flag = 1;
            }else if(s[i]==' '){
                //空格前面必须有数字
                if(num_flag != 0){
                    while(i<s.size()&&s[i]==' ') i++;
                    //要是空格就一路空格到底
                    if(i == s.size()) return true;
                    else return false;
                }else{
                    return false;
                }
            }else{ //不合法字符
                return false;
            }
        }
        //防止最后一位为e
        if(num_flag == 1) return true;
        else return false;
    }
};

// 状态机
class Solution {
public:
    enum State {
        STATE_INITIAL,
        STATE_INT_SIGN,
        STATE_INTEGER,
        STATE_POINT,
        STATE_POINT_WITHOUT_INT,
        STATE_FRACTION,
        STATE_EXP,
        STATE_EXP_SIGN,
        STATE_EXP_NUMBER,
        STATE_END,
    };

    enum CharType {
        CHAR_NUMBER,
        CHAR_EXP,
        CHAR_POINT,
        CHAR_SIGN,
        CHAR_SPACE,
        CHAR_ILLEGAL,
    };

    CharType toCharType(char ch) {
        if (ch >= '0' && ch <= '9') {
            return CHAR_NUMBER;
        } else if (ch == 'e' || ch == 'E') {
            return CHAR_EXP;
        } else if (ch == '.') {
            return CHAR_POINT;
        } else if (ch == '+' || ch == '-') {
            return CHAR_SIGN;
        } else if (ch == ' ') {
            return CHAR_SPACE;
        } else {
            return CHAR_ILLEGAL;
        }
    }

    bool isNumber(string s) {
        unordered_map<State, unordered_map<CharType, State>> transfer{
                {
                        STATE_INITIAL, {
                                               {CHAR_SPACE, STATE_INITIAL},
                                               {CHAR_NUMBER, STATE_INTEGER},
                                               {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                                               {CHAR_SIGN, STATE_INT_SIGN},
                                       }
                }, {
                        STATE_INT_SIGN, {
                                               {CHAR_NUMBER, STATE_INTEGER},
                                               {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                                       }
                }, {
                        STATE_INTEGER, {
                                               {CHAR_NUMBER, STATE_INTEGER},
                                               {CHAR_EXP, STATE_EXP},
                                               {CHAR_POINT, STATE_POINT},
                                               {CHAR_SPACE, STATE_END},
                                       }
                }, {
                        STATE_POINT, {
                                               {CHAR_NUMBER, STATE_FRACTION},
                                               {CHAR_EXP, STATE_EXP},
                                               {CHAR_SPACE, STATE_END},
                                       }
                }, {
                        STATE_POINT_WITHOUT_INT, {
                                               {CHAR_NUMBER, STATE_FRACTION},
                                       }
                }, {
                        STATE_FRACTION,
                        {
                                               {CHAR_NUMBER, STATE_FRACTION},
                                               {CHAR_EXP, STATE_EXP},
                                               {CHAR_SPACE, STATE_END},
                                       }
                }, {
                        STATE_EXP,
                        {
                                               {CHAR_NUMBER, STATE_EXP_NUMBER},
                                               {CHAR_SIGN, STATE_EXP_SIGN},
                                       }
                }, {
                        STATE_EXP_SIGN, {
                                               {CHAR_NUMBER, STATE_EXP_NUMBER},
                                       }
                }, {
                        STATE_EXP_NUMBER, {
                                               {CHAR_NUMBER, STATE_EXP_NUMBER},
                                               {CHAR_SPACE, STATE_END},
                                       }
                }, {
                        STATE_END, {
                                               {CHAR_SPACE, STATE_END},
                                       }
                }
        };

        int len = s.length();
        State st = STATE_INITIAL;

        for (int i = 0; i < len; i++) {
            CharType typ = toCharType(s[i]);
            if (transfer[st].find(typ) == transfer[st].end()) {
                return false;
            } else {
                st = transfer[st][typ];
            }
        }
        return st == STATE_INTEGER || st == STATE_POINT || st == STATE_FRACTION || st == STATE_EXP_NUMBER || st == STATE_END;
    }
};

