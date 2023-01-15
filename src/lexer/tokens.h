#pragma once

#include "../../../kerep/src/Autoarr/Autoarr.h"
#include "../../../kerep/src/SearchTree/SearchTree.h"

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
    tok_class,
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
    tok_new, // allocates struct in heap
    tok_sizeof, // size of variable value
    tok_typeof, // type of variable
    // special characters
    tok_lbracket,    // (
    tok_lbracket_fi, // {
    tok_lbracket_sq, // [
    tok_rbracket,    // )
    tok_rbracket_fi, // }
    tok_rbracket_sq, // ]
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
    tok_backslash,   // \ /
    tok_percent,     // %
    tok_xor,         // ^
    tok_lattice,     // #
    tok_dollar,      // $
    tok_at,           // @
    // user-defined
    tok_label,
    tok_number,
    tok_character,
    tok_string,
    tok_comment
} __attribute__((__packed__)) TokenId;

typedef struct Token{
    char* value;
    TokenId id;
} Token;
ktid_declare(Token);
Autoarr_declare(Token)

extern STNode* keywordsSearchTree;
// dont forget to free it
void init_keywordsSearchTree();


static const Token default_tokens[]={
    // base types
    {"void", tok_void_t},
    {"int8", tok_int8_t},
    {"uint8", tok_uint8_t},
    {"int16", tok_int16_t},
    {"uint16", tok_uint16_t},
    {"int32", tok_int32_t},
    {"uint32", tok_uint32_t},
    {"int64", tok_int64_t},
    {"uint64", tok_uint64_t},
    {"char", tok_char_t},
    {"char8", tok_char8_t},
    {"char16", tok_char16_t},
    {"bool", tok_bool_t},
    {"float32", tok_float32_t},
    {"float64", tok_float64_t},
    // constant
    {"null", tok_null},
    {"true", tok_true},
    {"false", tok_false},
    // control flow operators
    {"if", tok_if},
    {"else", tok_else},
    {"for", tok_for},
    {"while", tok_while},
    {"switch", tok_switch},
    {"case", tok_case},
    {"brake", tok_brake},
    {"braketo", tok_braketo},
    {"return", tok_return},
    {"goto", tok_goto},
    // declaration keywords
    {"class", tok_class},
    {"struct", tok_struct},
    {"enum", tok_enum},
    {"union", tok_union},
    {"event", tok_event},
    {"import", tok_import},
    {"alias", tok_alias},
    // access modifiers
    {"static", tok_static},
    {"const", tok_const},
    {"readonly", tok_readonly},
    {"protected", tok_protected},
    {"internal", tok_internal},
    {"public", tok_public},
    {"virtual", tok_virtual},
    {"override", tok_override},
    {"partial", tok_partial},
    // allocation keywords
    {"new", tok_new},
    {"sizeof", tok_sizeof},
    {"typeof", tok_typeof},
    // special characters
    {"(", tok_lbracket},
    {"{", tok_lbracket_fi},
    {"[", tok_lbracket_sq},
    {")", tok_rbracket},
    {"}", tok_rbracket_fi},
    {"]", tok_rbracket_sq},
    {"<", tok_less},
    {">", tok_more},
    {"+", tok_plus},
    {"-", tok_minus},
    {"*", tok_asterisk},
    {"/", tok_slash},
    {"=", tok_assign},
    {"!", tok_not},
    {"==", tok_equals},
    {"!=", tok_not_equals},
    {"&", tok_and},
    {"&&", tok_and_d},
    {"|", tok_or},
    {"||", tok_or_d},
    {"?", tok_question},
    {"??", tok_question_d},
    {":", tok_colon},
    {";", tok_semicolon},
    {".", tok_point},
    {",", tok_comma},
    {"~", tok_tilda},
    {"\\", tok_backslash},
    {"%", tok_percent},
    {"^", tok_xor},
    {"#", tok_lattice},
    {"$", tok_dollar},
    {"@", tok_at}
};
