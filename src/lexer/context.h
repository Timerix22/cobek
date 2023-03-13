#pragma once

#include "../../kerep/src/base/base.h"
#include "tokens.h"


PACKED_ENUM(ContextType,
    CT_Namespace,
    CT_Class,
    CT_Function
)

typedef struct Context Context;
STRUCT(Context,
    char* name;
    Context* parent;
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
