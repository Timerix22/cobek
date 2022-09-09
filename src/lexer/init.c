#include "lexer.h"

void ktDescriptors_initCbLexerTypes(){
    kt_register(Token, ktId_Token, NULL, NULL);
    kt_register(Token*, ktId_TokenPtr, NULL, NULL);
    kt_register(Autoarr_Token, ktId_AutoarrToken, ____Autoarr_free_Token, NULL);
    kt_register(Autoarr_Token*, ktId_AutoarrTokenPtr, ____Autoarr_free_Token, NULL);
}