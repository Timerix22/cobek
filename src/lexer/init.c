#include "lexer.h"

void ktDescriptors_initCbLexerTypes(){
    kt_register(Token, NULL, NULL);
    kt_register(Autoarr_Token, ____Autoarr_free_Token, NULL);
}
