#pragma once
#include "tokens.h"
#include "context.h"

Autoarr_declare(Token);

Autoarr(Token)* lexan(char* source, char* filename);

Context* parse(Autoarr(Token)* tokens);

string genBytecode(Context* toplvl_context);

Assembly genAssembly(Autoarr(string)* compiled_contexts, AssemblyParams params);
