#include "lexer.h"
#include "../../kerep/src/String/string.h"
#include "../../kerep/src/Filesystem/filesystem.h"

Maybe __Lexer_analize(Lexer* lex, char* _filename, char* _source);

Lexer* Lexer_create(){
    Lexer* lex=malloc(sizeof(*lex));
    *lex=(Lexer){0};
    lex->analize=__Lexer_analize;
    lex->keywordSearchTree=STNode_create();
    for(TokenId keywordId=0; keywordId<=tok_typeof; keywordId++){
        const Token* keywordptr=&default_tokens[keywordId];
        Unitype uni=UniStackPtr(Token, keywordptr);
        ST_push(lex->keywordSearchTree, keywordptr->value, uni);
    }
    return lex;
}

void Lexer_freeMembers(void* _l){
    Lexer* lex=(Lexer*)_l;
    STNode_free(lex->keywordSearchTree);
}

kt_define(Lexer, Lexer_freeMembers, NULL)

void Lexer_destroy(Lexer* lex){
    Lexer_freeMembers(lex);
    free(lex);
}

///@return Maybe<Autoarr(Token)*>
Maybe Lexer_parseFile(Lexer* lex, char* src_file_name){
    try(file_open(src_file_name, FileOpenMode_Read), m_src_file,;)
        File* src_file=m_src_file.value.VoidPtr;
    char* src_text;
    try(file_readAll(src_file, &src_text), m_src_len, file_close(src_file))
        u64 src_len=m_src_len.value.UInt64;
    kprintf("srclen: %lu\n", src_len);
    try(Lexer_parseText(lex, src_file_name, src_text), m_tokens, file_close(src_file))
        Autoarr(Token)* tokens=m_tokens.value.VoidPtr;
    return SUCCESS(UniHeapPtr(Autoarr(Token), tokens));
}
