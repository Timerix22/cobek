#pragma once

#include "../../../kerep/src/String/StringBuilder.h"
#include "../lexer/lexer.h"
#include "Assembly.h"
#include "Context.h"

Context* parse(Autoarr(Token)* tokens);

string genBytecode(Context* toplvl_context);

Assembly genAssembly(Autoarr(string)* compiled_contexts, AssemblyParams params);
