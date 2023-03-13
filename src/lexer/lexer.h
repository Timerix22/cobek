#pragma once

#include "tokens.h"
#include "context.h"

void kt_initLexerTypes();

STRUCT(Lexer,
    STNode* keywordSearchTree;
    Maybe (*analize)(Lexer* lex, char* src_file_name, char* src_file_text);
    
    char* source;
    char* filename;
    Autoarr(Token)* tokens;
    string context;
    string line;
    string label;
    u32 linenum;
    u32 charnum;
)

Lexer* Lexer_create();
void Lexer_destroy(Lexer* lex);
///@return Maybe<Autoarr(Token)*>

///@return Maybe<Autoarr(Token)*>
Maybe Lexer_parseFile(Lexer* lex, char* src_file_name);

///@return Maybe<Autoarr(Token)*>
static inline Maybe Lexer_parseText(Lexer* lex, char* src_file_name, char* src_file_text){
    return lex->analize(lex, src_file_name, src_file_text);
}
