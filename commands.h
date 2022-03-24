#pragma once
#include "../kerep/Autoarr/Autoarr.h"

typedef enum CommandId{
    
} __attribute__((__packed__)) CommandId;

struct CommandStruct;
typedef CommandStruct Command;
struct CommandStruct{
    Command* next;
    Command* prev;
    CommandId id;
}

Autoarr_declare(Comand);