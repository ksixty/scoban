#include "utils.h"

typedef struct Atom Atom;
typedef enum at_types at_type;

enum at_types { T_BOO, T_NUM, T_SYM };

struct Atom {
  at_type type;
  union {
    bool  boo;
    int   num;
    char* sym; 
  } val;
};

Atom* atom_new(at_type type, void* val);
