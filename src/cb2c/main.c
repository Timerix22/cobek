#include "cb2c.h"

int main(){
    // kerep type system
    ktDescriptors_beginInit();
    ktDescriptors_initKerepTypes();
    ktDescriptors_initCbLexerTypes();
    ktDescriptors_endInit();
    // keywords search tree
    init_keywordsSearchTree();
    printf("keywordsSearchTree: %p\n", keywordsSearchTree);
    STNode_free(keywordsSearchTree);
    return 0;
}