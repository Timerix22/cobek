#include "cb2c.h"

int main(){
    init_keywordsSearchTree();
    printf("keywordsSearchTree: %p\n", keywordsSearchTree);
    STNode_free(keywordsSearchTree);
    return 0;
}