#include "copler.h"
#include "../lexer/lexer.h"

int main(){
    init_keywordsSearchTree();

    STNode_free(keywordsSearchTree);
    return 0;
}