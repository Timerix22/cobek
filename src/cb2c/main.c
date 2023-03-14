#include "../../kerep/src/kprint/kprint.h"
#include "../../kerep/src/Filesystem/filesystem.h"
#include "cb2c.h"

char cb2c_version[]="0.0.1";

i32 main(const int argc, const char* const* argv){
    if(setlocale(LC_CTYPE, "C.UTF-8")!=0)
        kprintf("\e[93msetlocale failed\e[37m\n");

    Autoarr(Pointer)* source_files=Autoarr_create(Pointer, 64, 64);
    bool  compile=false;
    char* compiler=NULL;
    char* compilation_out_dir=NULL;
    bool  translate=false;
    char* translation_traget=NULL; // single .c + single .h; namespace structured project
    char* translation_out_dir=NULL;

    // command arguments
    if(argc==1){
        kprintf("\e[91mno arguments\e[37m\n");
        return -1;
    }
    for(int argi=1; argi<argc; argi++){
        char* a=argv[argi];
        kprintf("%s\n", a);

        if(cptr_compare(a, "-v") || cptr_compare(a, "--version")){
            kprintf("  cb2c v%s\n", cb2c_version);
            return 0;
        }

        if(cptr_compare(a, "-c") || cptr_compare(a, "--compiler")){
            compile=true;
            kprintf("  compile=true\n");

            if(argi+1>=argc || argv[argi+1][0]=='-')
                throw("after argument --compiler must be compiler name");
            
            compiler=argv[++argi];
            kprintf("  compiler=%s\n", compiler);
        }

        else if(cptr_compare(a, "-t") || cptr_compare(a, "--translate")){
            translate=true;
            kprintf("  translate=true\n");

            if(argi+1>=argc || argv[argi+1][0]=='-')
                throw("after argument --translation-out-dir must be directory path");
            
            translation_traget=argv[++argi];
            kprintf("  translation_traget=%s\n",translation_traget);
        }

        else if(cptr_compare(a, "-to") || cptr_compare(a, "--tranlation-out-dir")){
            if(argi+1>=argc || argv[argi+1][0]=='-')
                throw("after argument --translation-out-dir must be directory path");
            
            translation_out_dir=argv[++argi];
            kprintf("  translation_out_dir=%s\n", translation_out_dir);

            if(!dir_exists(translation_out_dir)){
                dir_create(translation_out_dir);
                kprintf("  directory was created\n");
            }
            else kprintf("  directory exists\n");
        }

        else if(cptr_compare(a, "-o") || cptr_compare(a, "--compilation-out-dir")){
            if(argi+1>=argc || argv[argi+1][0]=='-')
                throw("after argument --compilation-out-dir must be directory path");
            
            compilation_out_dir=argv[++argi];
            kprintf("  compilation_out_dir=%s\n", compilation_out_dir);

            if(!dir_exists(compilation_out_dir)){
                dir_create(compilation_out_dir);
                kprintf("  directory was created\n");
            }
            else kprintf("  directory exists\n");
        }

        else {
            if(a[0]=='-'){
                kprintf("  \e[91minvalid argument: %s\e[37m\n", a);
                return -2;
            }
            if(file_exists(a)){
                Autoarr_add(source_files, a);
                kprintf("  found source file: %s\n", a);
            }
            else {
                kprintf("  \e[91mfile not found: %s\e[37m\n", a);
                return -3;
            }
        }
    }

    if(!compile && !translate){
        kprintf("\e[91moperation not specified: select --translate and/or --compile\e[37m\n");
        return -4;
    }
    if(Autoarr_length(source_files)==0){
        kprintf("\e[91mno source files specified\e[37m\n");
        return -5;
    }

    // kerep type system
    kt_beginInit();
    kt_initKerepTypes();
    kt_initLexerTypes();
    kt_endInit();
    kprint_setColor(kp_fgGray);

    Lexer* lexer=Lexer_create();
    
    Autoarr_foreach(source_files, src_file_name, ({
        tryLast(Lexer_parseFile(lexer, src_file_name), m_tokens)
            LinkedList(Token)* tokens=m_tokens.value.VoidPtr;
        kprintf("tokens count: %u\n", tokens->count);
        LinkedList_foreach(tokens, tokNode, 
            kprintf("%u %s\n", tokNode->value.id, tokNode->value.value));
        char* basename=path_basename(src_file_name, false);
        NamespaceContext file_context={
            .base={
                .name=basename,
                .namespace=NULL,
                .parent=NULL,
                .type=ContextType_Namespace,
                .tokens=tokens
            }
        };
        tryLast(translateToC(&file_context.base), m_c_code)
            char* generated_code=m_c_code.value.VoidPtr;
        kprintf("%s", generated_code);

        char* generated_file_name;
        if(file_context.base.namespace!=NULL)
            generated_file_name=cptr_concat(file_context.base.namespace,".",file_context.base.name,".g.c");
        else generated_file_name=cptr_concat(file_context.base.name,".g.c");
        tryLast(file_open(generated_file_name, FileOpenMode_Write), m_generated_file)
            FileHandle generated_file=m_generated_file.value.VoidPtr;
        kprintf("created file %s\n", generated_file_name);
        tryLast(file_writeCptr(generated_file, generated_code),_m_1885);
        tryLast(file_close(generated_file),_m_14415);
        kprintf("source code has been written to the file\n");
        free(basename);
        LinkedList_free(tokens);
        free(generated_code);
        free(generated_file_name);
    }));

    Autoarr_free(source_files, true);
    Lexer_destroy(lexer);
    kt_free();
    return 0;
}
