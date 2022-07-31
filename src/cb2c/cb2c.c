#include "cb2c.h"
#include "../../../kerep/src/String/StringBuilder.h"

void namespaceToC(NamespaceContext* context, StringBuilder* b){
    
}

void functionToC(FunctionContext* context, StringBuilder* b){
    
}

void classToC(ClassContext* context, StringBuilder* b){
    
}

char* contextToC(void* context){
    StringBuilder* b=StringBuilder_create();
    switch(((Context*)context)->type){
        case CT_Namespace: namespaceToC(context, b); break;
        case CT_Function: functionToC(context, b); break;
        case CT_Class: classToC(context, b); break;
        default: throw(ERR_WRONGTYPE);
    }
    return StringBuilder_build(b).ptr;
}
