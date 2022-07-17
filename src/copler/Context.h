#pragma once
#include "../../../kerep/src/Autoarr/Autoarr.h"
#include "commands.h"

typedef struct ContextStruct Context;

Autoarr_declare(Context)

struct ContextStruct{
    Context* parent;
    Autoarr(Context) children;
    Autoarr(Command) commandChain;
    Autoarr(Constant) constantStack;
    bool isPartial; // if true, not-defined members won't throw NotDefinedError before linkage
};
