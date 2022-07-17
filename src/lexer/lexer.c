#include "lexer.h"

Autoarr_define(Token);

typedef struct SourceFileInfo{
    char* _source;
    char* _filename;
    Autoarr(Token)* _tokens;
    string _context;
    string _line;
    string _label;
    uint32 _linenum;
    uint32 _charnum;
} SourceFileInfo;

#define source sfi->_source
#define filename sfi->_filename
#define tokens sfi->_tokens
#define context sfi->_context
#define line sfi->_line
#define label sfi->_label
#define linenum sfi->_linenum
#define charnum sfi->_charnum

Maybe _throw_wrongchar(SourceFileInfo* sfi){
    char* errline=string_extract(line);
    printf("\n\e[91mwrong char <%c> at [%s:%u:%u %s]\n >>> %s\n",
                source[charnum], filename,linenum,charnum,context, errline);
    exit(96);
}
#define throw_wrongchar(freeMem) { freeMem; _throw_wrongchar(sfi); }

char _charFromEscapeStr(string estr, SourceFileInfo* sfi){
    if(*estr.ptr!='\\') throw("first char is not \\");
    switch(*(++estr.ptr)){
        case 'n': return '\n';
        case 'r': return '\r';
        case 't': return '\t';
        case 'e': return '\e';
        case '\\': return '\\';
        case '"': return '"';
        case '\'': return '\'';
        default: throw_wrongchar(;);
    }
}
#define charFromEscapeStr(estr) _charFromEscapeStr(estr, sfi)

Autoarr(Token)* lexan(char* _source, char* _filename){
    SourceFileInfo sfi={
        ._source=_source,
        ._filename=_filename,
        ._tokens=Autoarr_create(Token,64,1024),
        ._label={_source,0},
        ._line={_source,0},
        ._linenum=0,
        ._charnum=0
    };
    return _lexan(&sfi);
}

Autoarr(Token)* _lexan(SourceFileInfo* sfi){
    
    void addlabel(){
        if(label.length==0) return;
        Unitype token_ptr_u=ST_pull_str(label);
        // user-defined label
        if(token_ptr_u.type==Null){
            Token ut={
                .id=tok_label,
                .value=string_cpToCharPtr(label)
            };
            switch(*label.ptr){
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9': 
                    ut.id=tok_number;
                    break;
                default:
                    break;
            }
            Autoarr_add(tokens, ut);
        }
        // built-in keyword
        else Autoarr_add(tokens, (*token_ptr_u.VoidPtr));
        
        label={source,0};
    };
    
    
    addtok(TokenId id){
       Autoarr_add(tokens, default_tokens[id]);
    }
    
    
    addtok_ifnext(char next, TokenId yes, TokenId no){
        if(*(source+1)==next){
             addtok(yes);
             source++;
        }
        else addtok(no);
    }
    
    
    while ((c=*source++)) switch(c){
        case ' ': case '\t':
        case '\r': case '\n':
                addlabel();
                break;
        case '(':
            addlabel();
            addtok(tok_lbracket);
            break;
        case '{':
            addlabel();
            addtok(tok_lbracket_fi);
            break;
        case '[':
            addlabel();
            addtok(tok_lbracket_sq);
            break;
        case ')':
            addlabel();
            addtok(tok_rbracket);
            break;
        case '}':
            addlabel();
            addtok(tok_rbracket_fi);
            break;
        case ']':
            addlabel();
            addtok(tok_rbracket_sq);
            break;
        case '\'':
            addlabel();
            Token ctok={ 
                .id=tok_char ,
                .value={++source,1}
            };
            if(*source=='\\'){
                ctok.value=malloc(1);
                *ctok.value=charFromEscapeStr(source++,2);
            }
            if(*(++source)!='\'')
                throw_wrongchar();
            Autoarr_add(tokens, ctok);
            break;
        case '"':
            addlabel();
            
            
            break;
        case '<':
            addlabel();
            addtok(tok_less);
            break;
        case '>':
            addlabel();
            addtok(tok_more);
            break;
        case '+':
            addlabel();
            addtok(tok_plus);
            break;
        case '-':
            addlabel();
            addtok(tok_minus);
            break;
        case '*':
            addlabel();
            addtok(tok_asterisk);
            break;
        case '/':
            addlabel();
            if(*(++source)=='/'){
                label={++source,0};
                    while((c=*(source++))
                        if(c=='\n'){
                            // removes \r from the end of comment line
                            if(*(source-2)=='\r')
                                label.length--;
                            goto add_comment;
                        }
                        else label.length++;
                    add_comment:
                    Token comt={
                        .id=tok_comment,
                        .value=label
                    }
                    Autoarr_add(tokens,comt);
            }
            else if(*source=='*'){
                label={++source,0};
                    while((c=*(source++))
                        if(c=='*'&&*(source++)=='/')
                            goto add_comment;
                        else label.length++;
                    add_comment:
                    Token comt={
                        .id=tok_comment,
                        .value=label
                    }
                    Autoarr_add(tokens,comt);
            }
            else{
                source--;
                addtok(tok_slash);
            }
            break;
        case '=':
            addlabel();
            addtok_ifnext('=',tok_equals,tok_assign);
            break;
        case '!':
            addlabel();
addtok_ifnext('=',tok_not_equals,tok_not);
            break;
        case '&':
            addlabel();
            addtok_ifnext('&',tok_,tok_);
            break;
        case '|':
            addlabel();
            addtok_ifnext('|',tok_or,tok_or_d);
            break;
        case '?':
            addlabel();
            addtok_ifnext('?',tok_question,tok_question_d);
            break;
        case ':':
            addlabel();
            addtok(tok_colon);
            break;
        case ';':
            addlabel();
            addtok(tok_semicolon);
            break;
        case '.':
            addlabel();
            addtok(tok_point);
            break;
        case ',':
            addlabel();
            addtok(tok_comma);
            break;
        case '~':
            addlabel();
            addtok(tok_tilda);
            break;
        case '\\':
            addlabel();
            addtok(tok_backslash);
            break;
        case '%':
            addlabel();
            addtok(tok_percent);
            break;
        case '^':
            addlabel();
            addtok(tok_xor);
            break;
        case '$':
            addlabel();
            addtok(tok_dollar);
            break;
        case '@':
            addlabel();
            addtok(tok_at);
            break;
        default:
            label.length++;
            break;
    }
    
    return tokens;
}
