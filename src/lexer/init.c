#include "lexer.h"

void kt_initLexerTypes(){
    kt_register(Token);
    kt_register(LinkedList_Token);
    kt_register(LLNode_Token);
}
