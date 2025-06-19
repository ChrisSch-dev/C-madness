typedef enum { TYPE_INT, TYPE_TEXT, TYPE_FLOAT, TYPE_DATE, TYPE_BOOL, TYPE_NULL } coltype_t;
typedef struct {
    coltype_t type;
    union {
        int i;
        double f;
        char* s;
        int b;
        void* p;
    };
    int is_null;
} value_t;