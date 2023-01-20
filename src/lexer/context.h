#pragma once

#include "../../kerep/src/base/base.h"
#include "tokens.h"

typedef struct ContextStruct Context;

PACK_ENUM(ContextType,
    CT_Namespace,
    CT_Function,
    CT_Class
)

struct ContextStruct {
    char* name;
    Context* parent;
    Autoarr(Token)* tokens;
    ContextType type;
};

typedef struct NamespaceContext{
    Context base;
} NamespaceContext;

typedef struct FunctionContext {
    Context base;
    Autoarr(Token)* arguments;
    Autoarr(Token)* attributes;
    Token accessModifier;
    Token returnType;
} FunctionContext;

typedef struct ClassContext {
    Context base;
    Autoarr(Token)* attributes;
    Token accessModifier;
} ClassContext;
