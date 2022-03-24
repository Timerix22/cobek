#include "cobek_compiler.h"

Autoarr_define(Token);


char charFromEscapeStr(string estr){
    if(*estr.ptr!='\\') throw("first char is not \\");
    switch(*(++estr.ptr)){
        case 'n': return '\n';
        case 'r': return '\r';
        case 't': return '\t';
        case 'e': return '\e';
        case '\\': return '\\';
        case '"': return '"';
        case '\'': return '\'';
        default: throw(ERR_WRONGCHAR);    
    }
}


Autoarr(Token)* lexan(char* source, char* filename){
    Autoarr(Token)* tokens=malloc(sizeof(Autoarr(Token)));
    *tokens=Autoarr_create(Token,64,1024);
    char c;
    string label={source,0};
    string line={source,0};
    uint32 linenum;
    uint32 cnum;
    
    
    void throw_wrongchar(){
        char* errline=string_cpToCharPtr(line);
        printf("\n\e[91mwrong char <%c> at [%s:%u:%u %s]\n >>> %s\n" ,filename,linenum,cnum,c,errline);
        exit(96);
    };
    
    
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
