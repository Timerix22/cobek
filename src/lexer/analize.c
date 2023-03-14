#include "lexer.h"

Maybe _throw_wrongchar(Lexer* lex){
    char* _errline=string_extract(lex->line);
    char* _context=string_extract(lex->context);
    printf("\n\e[91mwrong char <%c> at [%s:%u:%u %s]\n >>> %s\n",
        lex->source[lex->charnum], lex->filename,lex->linenum,lex->charnum,_context, _errline);
    exit(96);
}
#define throw_wrongchar(freeMem) { freeMem; return _throw_wrongchar(lex); }

// adds <lex->label> to <lex->tokens> as tok_label or tok_number
void _tryAddLabel(Lexer* lex){
    if(lex->label.length==0) return;

    Unitype uni=ST_pullString(lex->keywordSearchTree, lex->label);
    if(uni.VoidPtr!=NULL) // built-in keyword
        LinkedList_addToEnd(lex->tokens, LLNode_create(Token,*(Token*)uni.VoidPtr));
    else {          // user-defined lex->label
        TokenId udt_id=tok_label;
        switch(*lex->label.ptr){ // starts with number
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                udt_id=tok_number;
                break;
        }
        Token udt=Token_createUD(udt_id, string_extract(lex->label));
        LinkedList_addToEnd(lex->tokens, LLNode_create(Token,udt));
    }
  
    lex->label=(string){lex->source, 0};
};
#define tryAddLabel() _tryAddLabel(lex)
  
#define addDefTok(id) { tryAddLabel(); LinkedList_addToEnd(lex->tokens, LLNode_create(Token,default_tokens[id])); }
  
void _addDefTok_ifnext(Lexer* lex, char next, TokenId yes, TokenId no){
    if(*(lex->source+1)==next){
        lex->source++;
        addDefTok(yes);
    }
    else addDefTok(no);
}
#define addDefTok_ifnext(nextChar, yesTok, noTok) _addDefTok_ifnext(lex, nextChar, yesTok, noTok)

// returns text in quotes or error
Maybe _readString(Lexer* lex, char quotChar){
    char c;
    bool prevIsBackslash=false;
    char* srcFirst=lex->source;
    while ((c=*++lex->source)){
        if(c==quotChar) {
            if(prevIsBackslash) // \"
                prevIsBackslash=false;
            else { // "
                string str={srcFirst, lex->source-srcFirst+1};
                char* extracted=string_extract(str);
                return SUCCESS(UniHeapPtr(char, extracted));
            }
        }
        else prevIsBackslash= c=='\\' && !prevIsBackslash;
    }
    lex->source=srcFirst;
    throw_wrongchar(;);
}
#define readString(quotChar) _readString(lex, quotChar)


Maybe __Lexer_analize(Lexer* lex, char* _filename, char* _source){
    lex->filename=_filename;
    lex->source=_source;
    if(lex->tokens!=NULL)
        LinkedList_free(lex->tokens);
    lex->tokens=LinkedList_create(Token);
    lex->label=(string){_source, 0};
    lex->line=(string){_source, 0};
    lex->linenum=0;
    lex->charnum=0;

    char c;
    lex->source--;
    while ((c=*++(lex->source))) {
        // tryAddLabel() resets lex->label.length, but lex->label.ptr still pointing to prev token beginning
        if(lex->label.length==0)
            lex->label.ptr=lex->source;

        switch(c){
        case ' ': case '\t':
        case '\r': case '\n':
            tryAddLabel();
            break;
		
        case '(': addDefTok(tok_lbracket);    break;
        case '{': addDefTok(tok_lbracket_fi); break;
        case '[': addDefTok(tok_lbracket_sq); break;
        case ')': addDefTok(tok_rbracket);    break;
        case '}': addDefTok(tok_rbracket_fi); break;
        case ']': addDefTok(tok_rbracket_sq); break;
		
        case '\'':
            tryAddLabel();
            try(readString('\''), m_ch, ;){
                Token ctok=Token_createUD(tok_character, m_ch.value.VoidPtr);
                LinkedList_addToEnd(lex->tokens, LLNode_create(Token,ctok));
            }
            break;
        case '"':
            tryAddLabel();
            try(readString('"'), m_Str, ;){
                Token stok=Token_createUD(tok_string, m_Str.value.VoidPtr);
                LinkedList_addToEnd(lex->tokens, LLNode_create(Token,stok));
            }
            break;
		
        case '<': addDefTok(tok_less); break;
        case '>': addDefTok(tok_more); break;
        case '+': addDefTok(tok_plus); break;
        case '-': addDefTok(tok_minus); break;
        case '*': addDefTok(tok_asterisk); break;
		
        case '/':
            tryAddLabel();
            string commentStr={lex->source, 1};
            c=*++lex->source;
            if(c=='/') { // single-lex->line comment
                commentStr.length++;
                while((c=*++lex->source)){
                    if(c=='\n' || c=='\r') break;
                    else commentStr.length++;
                }
            }
            else if(c=='*') { // multi-lex->line comment
                commentStr.length++; // first slash
                while((c=*++lex->source)){
                    commentStr.length++;
                    if(c=='*' && *(++lex->source)=='/') break;
                }
                commentStr.length++; // last slash
            }
            else { // not comment
                lex->source--;
                addDefTok(tok_slash);
                break;
            }
            Token comTok=Token_createUD(tok_comment, string_extract(commentStr));
            LinkedList_addToEnd(lex->tokens, LLNode_create(Token,comTok));
            break;
		
        case '=': addDefTok_ifnext('=', tok_equal, tok_assign);       break;
        case '!': addDefTok_ifnext('=', tok_not_equal, tok_not);      break;
        case '&': addDefTok_ifnext('&', tok_and_d, tok_and);          break;
        case '|': addDefTok_ifnext('|', tok_or_d,  tok_or);           break;
        case '?': addDefTok_ifnext('?', tok_question_d, tok_question);break;
        case ':': addDefTok(tok_colon);      break;
        case ';': addDefTok(tok_semicolon);  break;
        case '.': addDefTok(tok_point);      break;
        case ',': addDefTok(tok_comma);      break;
        case '~': addDefTok(tok_tilda);      break;
        case '\\':addDefTok(tok_backslash);  break;
        case '%': addDefTok(tok_percent);    break;
        case '^': addDefTok(tok_xor);        break;
        case '$': addDefTok(tok_dollar);     break;
        case '@': addDefTok(tok_at);         break;
		
        default:
            lex->label.length++;
            break;
        }
    }
    
    tryAddLabel();
    return SUCCESS(UniHeapPtr(LinkedList(Token), lex->tokens));
}
