#pragma once

#include "../../kerep/src/base/base.h"
#include "tokens.h"


PACKED_ENUM(ContextType,
    ContextType_Namespace,
    ContextType_Class,
    ContextType_Function
)

STRUCT(Context,
    char* name;
    char* namespace; /* nullable */
    Context* parent; /* nullable */
    LinkedList(Token)* tokens;
    ContextType type;
)

STRUCT(NamespaceContext,
    Context base;
)

STRUCT(ClassContext,
    Context base;
    LinkedList(Token)* attributes;
    Token accessModifier;
)

STRUCT(FunctionContext,
    Context base;
    LinkedList(Token)* arguments;
    LinkedList(Token)* attributes;
    Token accessModifier;
    Token returnType;
)
