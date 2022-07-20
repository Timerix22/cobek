#include "tokens.h"

Autoarr_define(Token)

void init_keywordsSearchTree(){
    keywordsSearchTree=STNode_create();
    for(TokenId keywordId=0; keywordId<=tok_typeof; keywordId++){
        Token keyword=default_tokens[keywordId];
        Unitype fake_uni=*(Unitype*)(void*)&keyword;
        ST_push(keywordsSearchTree, keyword.value, fake_uni);
    }
}
