#include "tokens.h"

void Token_freeMembers(void* _t){
    Token* t=(Token*)_t;
    if(t->on_heap)
        free(t->value);
}

char* Token_toString(void* _t, u32 fmt){
    return cptr_copy(((Token*)_t)->value);
}

kt_define(Token, Token_freeMembers, Token_toString);
Autoarr_define(Token, false)
