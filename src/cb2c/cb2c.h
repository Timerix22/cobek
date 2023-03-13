#pragma once

#include "../lexer/lexer.h"

/// @brief generates C source code from tokens
/// @param context contains code tokens
/// @return Maybe<char*> C source code 
Maybe translateToC(Context* context);
