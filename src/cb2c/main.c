#include "cb2c.h"
#include "../../kerep/src/kprint/kprint.h"

int main(){
    if(!setlocale(LC_ALL, "C.UTF8"))
        kprintf("\e[93msetlocale failed\n");
    // kerep type system
    ktDescriptors_beginInit();
    ktDescriptors_initKerepTypes();
    ktDescriptors_initCbLexerTypes();
    ktDescriptors_endInit();
    // keywords search tree
    init_keywordsSearchTree();
    kprint(kp_s|kp_fgGray, "keywordsSearchTree: ", kp_h|kp_pre, keywordsSearchTree, kp_c, '\n');
    STNode_free(keywordsSearchTree);
    return 0;
}