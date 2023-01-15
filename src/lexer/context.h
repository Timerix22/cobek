#pragma once

#include "../../kerep/src/base/base.h"
#include "tokens.h"

typedef struct ContextStruct Context;

typedef enum ContextType{ 
    CT_Namespace,
    CT_Function,
    CT_Class
} __attribute__((__packed__))  ContextType;

struct ContextStruct {
    char* name;
    Context* parent;
    Autoarr(Token)* tokens;
    ContextType type;
};

typedef struct NamespaceContext{
    union {
        Context base;
        Context;
    };
} NamespaceContext;

typedef struct FunctionContext {
    union {
        Context base;
        Context;
    };
    Autoarr(Token)* arguments;
    Autoarr(Token)* attributes;
    Token accessModifier;
    Token returnType;
} FunctionContext;

typedef struct ClassContext {
    union {
        Context base;
        Context;
    };
    Autoarr(Token)* attributes;
    Token accessModifier;
} ClassContext;
