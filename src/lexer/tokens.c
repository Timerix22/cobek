#include "tokens.h"

ktid_define(Token);
Autoarr_define(Token)


STNode* keywordsSearchTree=NULL;
void init_keywordsSearchTree(){
    keywordsSearchTree=STNode_create();
    for(TokenId keywordId=0; keywordId<=tok_typeof; keywordId++){
        const Token* keywordptr=&default_tokens[keywordId];
        Unitype uni=UniStackPtr(Token, keywordptr);
        ST_push(keywordsSearchTree, keywordptr->value, uni);
    }
}
