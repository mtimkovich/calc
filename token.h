enum tokentype 
{
    OPERATOR, 
    NUMBERTOK 
};

enum optype 
{
    PLUSOP,
    MINUSOP,
    TIMEOP,
    DIVIDEOP
};

enum datatype 
{
    INTEGER,
    REAL
};

struct tokn
{
    enum tokentype tokentype;
    enum datatype datatype;
    struct tokn* operands;
    struct tokn* link;
    union {
        enum optype which;
        int intnum;
        int realnum;
    } val;
};

typedef struct tokn *Token;

#define whichval val.which
#define intval val.intnum
#define realval val.realnum

Token talloc();
