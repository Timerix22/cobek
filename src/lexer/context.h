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
    Autoarr(Token)* tokens;
    ContextType type;
)

STRUCT(NamespaceContext,
    Context base;
)

STRUCT(ClassContext,
    Context base;
    Autoarr(Token)* attributes;
    Token accessModifier;
)

STRUCT(FunctionContext,
    Context base;
    Autoarr(Token)* arguments;
    Autoarr(Token)* attributes;
    Token accessModifier;
    Token returnType;
)
