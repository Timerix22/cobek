#pragma once

#include "../../../kerep/src/Autoarr/Autoarr.h"
#include "../../../kerep/src/String/string.h"
#include "tokens.h"

Autoarr_declare(Token)

Autoarr(Token)* lexan(char* source, char* filename);
