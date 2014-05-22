enum tokentype 
{
    OPERATOR, 
    NUMBER 
};

enum optype 
{
    PLUSOP,
    MINUSOP,
    TIMESOP,
    DIVIDEOP,
    MODOP,
    POWEROP,
    LPAREN,
    RPAREN
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
    char name;
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

#define ASCII 256
int optable[ASCII];

Token talloc();
void printtoken(Token);
void initsymbols();
Token cons(Token, Token); 
int length(Token);
Token nreverse(Token);
void pplist(Token tree);
void printelem(Token tok);
Token op(Token tok);
Token lhs(Token tok);
Token rhs(Token tok);
