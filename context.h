#pragma once
#include "commands.h"

struct ContextStruct;
typedef ContextStruct Context;

Autoarr_declare(Context);

struct ContextStruct{
    Context* parent;
    Autoarr(Context) children;
    Autoarr(Command) commandChain;
    Autoarr(Constant) constantStack;
}
