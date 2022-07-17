#pragma once

#include "../../../kerep/src/base/base.h"

typedef enum TokenId{
    // base types
    tok_void_t,
    tok_int8_t,
    tok_uint8_t,
    tok_int16_t,
    tok_uint16_t,
    tok_int32_t,
    tok_uint32_t,
    tok_int64_t,
    tok_uint64_t,
    tok_char_t,      //ascii
    tok_char8_t,     //utf8
    tok_char16_t,    //utf16
    tok_bool_t,
    tok_float32_t,
    tok_float64_t,
    // constant
    tok_null,
    tok_true,
    tok_false,
    // control flow operators
    tok_if,
    tok_else,
    tok_for,
    tok_while,
    tok_switch,
    tok_case,
    tok_brake,
    tok_braketo,
    tok_return,
    tok_goto,
    // declaration keywords
    tok_struct,
    tok_enum,
    tok_union,
    tok_event,
    tok_import,
    tok_alias,
    // access modifiers
    tok_static,
    tok_const,
    tok_readonly,
    tok_protected,
    tok_internal,
    tok_public,
    tok_virtual,
    tok_override,
    tok_partial,
    // allocation keywords
    tok_halloc, // allocates struct in heap
    tok_malloc, // allocates bytes in stack
    tok_sizeof, // size of variable value
    tok_typeof, // type of variable
    // user-defined
    tok_label,
    tok_number,
    tok_character,
    tok_string,
    tok_comment,
    // special characters
    tok_lbracket,    // (
    tok_lbracket_fi, // {
    tok_lbracket_sq, // [
    tok_rbracket,    // )
    tok_rbracket_fi, // }
    tok_rbracket_sq, // ]
    //tok_quot,        // '
    //tok_quot_d,      // "
    tok_less,        // <
    tok_more,        // >
    tok_plus,        // +
    tok_minus,       // -
    tok_asterisk,    // *
    tok_slash,       // /
    tok_assign,      // =
    tok_not,         // !
    tok_equals,      // ==
    tok_not_equals,  // !=
    tok_and,         // &
    tok_and_d,       // &&
    tok_or,          // |
    tok_or_d,        // ||
    tok_question,    // ?
    tok_question_d,  // ??
    tok_colon,       // :
    tok_semicolon,   // ;
    tok_point,       // .
    tok_comma,       // ,
    tok_tilda,       // ~
    tok_backslash,   // \
    tok_percent,     // %
    tok_xor,         // ^
    tok_lattice,     // #
    tok_dollar,      // $
    tok_at           // @
} __attribute__((__packed__)) TokenId;

typedef struct Token{
    char* value;
    TokenId id;
} Token;

