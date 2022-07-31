#include "cb2c.h"

int main(){
    init_keywordsSearchTree();

    STNode_free(keywordsSearchTree);
    return 0;
}