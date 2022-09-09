#include "tokens.h"

ktId_define(ktId_Token);
ktId_define(ktId_TokenPtr);

Autoarr_define(Token)
ktId_define(ktId_AutoarrToken);
ktId_define(ktId_AutoarrTokenPtr);


STNode* keywordsSearchTree=NULL;
void init_keywordsSearchTree(){
    keywordsSearchTree=STNode_create();
    for(TokenId keywordId=0; keywordId<=tok_typeof; keywordId++){
        const Token* keywordptr=&default_tokens[keywordId];
        Unitype uni=UniStack(ktId_TokenPtr, keywordptr);
        ST_push(keywordsSearchTree, keywordptr->value, uni);
    }
}
