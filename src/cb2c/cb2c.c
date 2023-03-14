#include "cb2c.h"
#include "../../kerep/src/String/StringBuilder.h"

#define addc(C) StringBuilder_append_char(b, C);
#define adds(S) StringBuilder_append_cptr(b, S);

void appendToken(StringBuilder* b, LLNode(Token)* tokNode, u16* _tab_count){
    u16 tab_count=*_tab_count;
    adds(tokNode->value.value)

    switch(tokNode->value.id){
        case tok_lbracket_fi:
            tab_count++;
            goto add_new_line;
        case tok_rbracket_fi:
            tab_count--;
            goto add_new_line;
        case tok_semicolon:
        case tok_colon:
        case tok_comment: ;
            add_new_line:
            addc('\n');
            for(u16 i=0; i<tab_count; i++)
                addc('\t');
            break;
        case tok_plus: case tok_minus: case tok_asterisk: case tok_slash:
        case tok_assign: case tok_equal: case tok_not: case tok_not_equal:
        case tok_and: case tok_and_d: case tok_or: case tok_or_d:
        case tok_less: case tok_more: case tok_percent:
        case tok_for: case tok_if: case tok_while: case tok_switch:
        case tok_lbracket: case tok_rbracket: case tok_lbracket_sq: case tok_rbracket_sq:
        case tok_break: case tok_backslash:
            break;
        default:
            addc(' ');
    }

    *_tab_count=tab_count;
}

Maybe appendNamespaceContext(StringBuilder* b, NamespaceContext* context){
    adds("/* context ")
    if(context->base.namespace!=NULL){
        adds(context->base.namespace)
        addc('.')
    }
    adds(context->base.name)
    adds(" */\n\n")

    u16 tab_count=0;
    LinkedList_foreach(context->base.tokens, tok, appendToken(b, tok, &tab_count));
    addc('\n');

    return MaybeNull;
}

Maybe appendClassContext(StringBuilder* b, ClassContext* context){
    safethrow(ERR_NOTIMPLEMENTED,;);
}

Maybe appendFunctionContext(StringBuilder* b, FunctionContext* context){
    safethrow(ERR_NOTIMPLEMENTED,;);
}

Maybe translateToC(Context* context){
    StringBuilder* b=StringBuilder_create();
    switch(context->type){
        case ContextType_Namespace:
            try(appendNamespaceContext(b, (NamespaceContext*)context), _0, StringBuilder_free(b));
            break;
        case ContextType_Class:
            try(appendClassContext(b, (ClassContext*)context), _2, StringBuilder_free(b));
            break;
        case ContextType_Function:
            try(appendFunctionContext(b, (FunctionContext*)context), _1, StringBuilder_free(b));
            break;
        default: safethrow(ERR_WRONGTYPE, StringBuilder_free(b));
    }
    return SUCCESS(UniHeapPtr(char, StringBuilder_build(b).ptr));
}
