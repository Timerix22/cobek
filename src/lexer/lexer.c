#include "lexer.h"
#include "../../../kerep/src/String/string.h"

typedef struct SharedLexerData{
    char* _source;
    char* _filename;
    Autoarr(Token)* _tokens;
    string _context;
    string _line;
    string _label;
    uint32 _linenum;
    uint32 _charnum;
} SharedLexerData;

#define source sld->_source
#define filename sld->_filename
#define tokens sld->_tokens
#define context sld->_context
#define line sld->_line
#define label sld->_label
#define linenum sld->_linenum
#define charnum sld->_charnum

Maybe _throw_wrongchar(SharedLexerData* sld){
    char* errline=string_extract(line);
    char* _context=string_extract(context);
    printf("\n\e[91mwrong char <%c> at [%s:%u:%u %s]\n >>> %s\n",
                source[charnum], filename,linenum,charnum,context, errline);
    exit(96);
}
#define throw_wrongchar(freeMem) { freeMem; return _throw_wrongchar(sld); }
    
#define addTok(id) Autoarr_add(tokens, default_tokens[id])
    
void _addTok_ifnext(char next, TokenId yes, TokenId no, SharedLexerData* sld){
    if(*(++source)==next){
        addTok(yes);
    }
    else {
        source--;
        addTok(no);
    }
}
#define addTok_ifnext(nextChar, yesTok, noTok) _addTok_ifnext(nextChar, yesTok, noTok, sld)

// adds <label> to <tokens> as tok_label or tok_number
void _tryAddLabel(SharedLexerData* sld){
    if(label.length==0) return;
    Unitype fake_uni=ST_pullString(keywordsSearchTree,label);
    if(fake_uni.VoidPtr!=NULL) // built-in keyword
        Autoarr_add(tokens, *(Token*)(void*)&fake_uni);
    else {          // user-defined label
        Token ut;
        ut.value=string_extract(label);
        switch(*label.ptr){
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9': 
                ut.id=tok_number;
                break;
            default:
                ut.id=tok_label;
                break;
        }
        Autoarr_add(tokens, ut);
    }
    
    label=(string){source,0};
};
#define tryAddLabel() _tryAddLabel(sld)

// returns text in quotes or error
Maybe _readString(char quotChar, SharedLexerData* sld){
    char c;
    bool prevIsBackslash=false;
    char* srcFirst=source;
    while ((c=*++source)){
        if(c==quotChar) {
            if(prevIsBackslash) // \"
                prevIsBackslash=false;
            else { // "
                string str={srcFirst, source-srcFirst+1};
                char* extracted=string_extract(str);
                return SUCCESS(UniPtr(CharPtr, extracted));
            }
        } 
        else prevIsBackslash= c=='\\' && !prevIsBackslash;
    }
    source=srcFirst;
    throw_wrongchar(;);
}
#define readString(quotChar) _readString(quotChar, sld)


Maybe _lexan(SharedLexerData* sld){
    char c;
    source--;
    while ((c=*++source)) switch(c){
        case ' ': case '\t':
        case '\r': case '\n':
            tryAddLabel();
            break;
        case '(':
            tryAddLabel();
            addTok(tok_lbracket);
            break;
        case '{':
            tryAddLabel();
            addTok(tok_lbracket_fi);
            break;
        case '[':
            tryAddLabel();
            addTok(tok_lbracket_sq);
            break;
        case ')':
            tryAddLabel();
            addTok(tok_rbracket);
            break;
        case '}':
            tryAddLabel();
            addTok(tok_rbracket_fi);
            break;
        case ']':
            tryAddLabel();
            addTok(tok_rbracket_sq);
            break;
        case '\'':
            tryAddLabel();
            try(readString('\''), maybeC, ;){
                Token ctok={ 
                    .id=tok_character,
                    .value=(char*)maybeC.value.VoidPtr
                };
                Autoarr_add(tokens, ctok);
            }
            break;
        case '"':
            tryAddLabel();
            try(readString('"'), maybeS, ;){
                Token stok={ 
                    .id=tok_string,
                    .value=(char*)maybeS.value.VoidPtr
                };
                Autoarr_add(tokens, stok);
            }
            break;
        case '<':
            tryAddLabel();
            addTok(tok_less);
            break;
        case '>':
            tryAddLabel();
            addTok(tok_more);
            break;
        case '+':
            tryAddLabel();
            addTok(tok_plus);
            break;
        case '-':
            tryAddLabel();
            addTok(tok_minus);
            break;
        case '*':
            tryAddLabel();
            addTok(tok_asterisk);
            break;
        case '/':
            tryAddLabel();
            string commentStr={source,0};
            c=*++source;
            if(c=='/') { // single-line comment
                while((c=*++source)){
                    if(c=='\n' || c=='\r') break;
                    else commentStr.length++;
                }
            }
            else if(c=='*') { // multi-line comment
                while((c=*++source)){
                    commentStr.length++;
                    if(c=='*' && *(++source)=='/') break;
                }
            }
            else { // not comment
                source--;
                addTok(tok_slash);
                break;
            }
            Token comTok={
                .value=string_extract(commentStr),
                .id=tok_comment
            };
            Autoarr_add(tokens,comTok);
            break;
        case '=':
            tryAddLabel();
            addTok_ifnext('=',tok_equals,tok_assign);
            break;
        case '!':
            tryAddLabel();
            addTok_ifnext('=',tok_not_equals,tok_not);
            break;
        case '&':
            tryAddLabel();
            addTok_ifnext('&',tok_and_d,tok_and);
            break;
        case '|':
            tryAddLabel();
            addTok_ifnext('|',tok_or_d,tok_or);
            break;
        case '?':
            tryAddLabel();
            addTok_ifnext('?',tok_question_d,tok_question);
            break;
        case ':':
            tryAddLabel();
            addTok(tok_colon);
            break;
        case ';':
            tryAddLabel();
            addTok(tok_semicolon);
            break;
        case '.':
            tryAddLabel();
            addTok(tok_point);
            break;
        case ',':
            tryAddLabel();
            addTok(tok_comma);
            break;
        case '~':
            tryAddLabel();
            addTok(tok_tilda);
            break;
        case '\\':
            tryAddLabel();
            addTok(tok_backslash);
            break;
        case '%':
            tryAddLabel();
            addTok(tok_percent);
            break;
        case '^':
            tryAddLabel();
            addTok(tok_xor);
            break;
        case '$':
            tryAddLabel();
            addTok(tok_dollar);
            break;
        case '@':
            tryAddLabel();
            addTok(tok_at);
            break;
        default:
            label.length++;
            break;
    }
    
    return SUCCESS(UniPtr(AutoarrTokenPtr,tokens));
}


Maybe lexan(char* _source, char* _filename){
    SharedLexerData sld={
        ._source=_source,
        ._filename=_filename,
        ._tokens=Autoarr_create(Token,64,1024),
        ._label={_source,0},
        ._line={_source,0},
        ._linenum=0,
        ._charnum=0
    };
    return _lexan(&sld);
}