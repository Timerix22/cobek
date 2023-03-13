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


STNode* keywordsSearchTree=NULL;
void init_keywordsSearchTree(){
    keywordsSearchTree=STNode_create();
    for(TokenId keywordId=0; keywordId<=tok_typeof; keywordId++){
        const Token* keywordptr=&default_tokens[keywordId];
        Unitype uni=UniStackPtr(Token, keywordptr);
        ST_push(keywordsSearchTree, keywordptr->value, uni);
    }
}
