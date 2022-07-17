#pragma once
#include "../../../kerep/src/String/string.h"
#include "../../../kerep/src/Autoarr/Autoarr.h"

typedef enum CommandId{
    CommandVoid
} __attribute__((__packed__)) CommandId;

typedef struct CommandStruct Command;
struct CommandStruct{
    Command* next;
    Command* prev;
    CommandId id;
};

Autoarr_declare(Command)

typedef struct ConstantStruct {

} Constant;

Autoarr_declare(Constant)