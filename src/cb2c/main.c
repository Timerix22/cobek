#include "../../kerep/src/kprint/kprint.h"
#include "../../kerep/src/Filesystem/filesystem.h"
#include "cb2c.h"
#include "../lexer/lexer.h"

Autoarr(Token)* parseFile(char* filename){
    tryLast(file_open(filename, FileOpenMode_Read), m_srcfile)
        File* srcfile=m_srcfile.value.VoidPtr;
    char* src;
    tryLast(file_readAll(srcfile, &src), m_srcLen)
        uint64 srcLen=m_srcLen.value.UInt64;
    kprintf("srclen: %lu\n", srcLen);
    src[srcLen]='\0';
    tryLast(lexan(src, filename), m_tokens)
        Autoarr(Token)* tokens=m_tokens.value.VoidPtr;
    return tokens;
}

int main(const int argc, const char* const* argv){
    if(!setlocale(LC_ALL, "C.UTF8"))
        kprintf("\e[93msetlocale failed\n");

    bool compile=0, translate=0;
    char *compiler=NULL, *tranlation_out_dir=NULL; 
    for(int argi=1; argi<argc; argi++){
        char* a=argv[argi];
        kprintf("%s ", a);
        if(cptr_compare(a, "-c") || cptr_compare(a, "--compiler")){
            compile=1;
            if(argi+1>=argc || argv[argi+1][0]=='-')
                throw("after argument --compiler must be compiler name");
            compiler=argv[++argi];
        }
        else if(cptr_compare(a, "-t") || cptr_compare(a, "--tranlation-out-dir")){
            translate=1;
            if(argi+1>=argc || argv[argi+1][0]=='-')
                throw("after argument --translation-out-dir must be directory path");
            tranlation_out_dir=argv[argi+1];
            if(!dir_exists(tranlation_out_dir))
                dir_create(tranlation_out_dir);     
        }
    }
    kprintf("\n"); return 0;
    // kerep type system
    ktDescriptors_beginInit();
    ktDescriptors_initKerepTypes();
    ktDescriptors_initCbLexerTypes();
    ktDescriptors_endInit();
    // keywords search tree
    init_keywordsSearchTree();
    kprint(kp_s|kp_fgGray, "keywordsSearchTree: ", kp_h|kp_pre, keywordsSearchTree, kp_c, '\n');
    Autoarr(Token)* tokens=parseFile("src.cb");
    kprintf("tokens: %u\n", Autoarr_length(tokens));
    Autoarr_foreach(tokens, tok, kprintf("%u %s\n",tok.id, tok.value));
    STNode_free(keywordsSearchTree);
    return 0;
}