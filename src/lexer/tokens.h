#pragma once

#include "../../kerep/src/Autoarr/Autoarr.h"
#include "../../kerep/src/SearchTree/SearchTree.h"

PACKED_ENUM(TokenId,
    /* base types */
    tok_void_t,
    tok_i8_t,
    tok_u8_t,
    tok_i16_t,
    tok_u16_t,
    tok_i32_t,
    tok_u32_t,
    tok_i64_t,
    tok_u64_t,
    tok_char_t,      /* ansi */
    tok_char8_t,     /* utf8 *? */
    tok_char16_t,    /* utf16 */
    tok_bool_t,
    tok_f32_t,
    tok_f64_t,
    /* constant */
    tok_null,
    tok_true,
    tok_false,
    /* control flow operators */
    tok_if,
    tok_else,
    tok_for,
    tok_while,
    tok_switch,
    tok_case,
    tok_break,
    tok_breakto,
    tok_return,
    tok_goto,
    /* declaration keywords */
    tok_class,
    tok_struct,
    tok_enum,
    tok_union,
    tok_event,
    tok_import,
    tok_alias,
    /* access modifiers */
    tok_static,
    tok_const,
    tok_readonly,
    tok_protected,
    tok_internal,
    tok_public,
    tok_virtual,
    tok_override,
    tok_partial,
    /* allocation keywords */
    tok_new, /* allocates struct in heap */
    tok_sizeof, /* size of variable value */
    tok_typeof, /* type of variable */
    /* special characters */
    tok_lbracket,    /* ( */
    tok_lbracket_fi, /* { */
    tok_lbracket_sq, /* [ */
    tok_rbracket,    /* ) */
    tok_rbracket_fi, /* } */
    tok_rbracket_sq, /* ] */
    tok_less,        /* < */
    tok_more,        /* > */
    tok_plus,        /* + */
    tok_minus,       /* - */
    tok_asterisk,    /* * */
    tok_slash,       /* / */
    tok_assign,      /* = */
    tok_not,         /* ! */
    tok_equal,      /* == */
    tok_not_equal,  /* != */
    tok_and,         /* & */
    tok_and_d,       /* && */
    tok_or,          /* | */
    tok_or_d,        /* || */
    tok_question,    /* ? */
    tok_question_d,  /* ?? */
    tok_colon,       /* : */
    tok_semicolon,   /* ; */
    tok_point,       /* . */
    tok_comma,       /* , */
    tok_tilda,       /* ~ */
    tok_backslash,   /* \ / */
    tok_percent,     /* % */
    tok_xor,         /* ^ */
    tok_lattice,     /* # */
    tok_dollar,      /* $ */
    tok_at,           /* @ */
    /* user-defined */
    tok_label,
    tok_number,
    tok_character,
    tok_string,
    tok_comment
)

STRUCT(Token,
    char* value;
    TokenId id;
    bool on_heap; // allocated on stack or heap
)
Autoarr_declare(Token)

static const Token default_tokens[]={
    /* base types */
    {"void", tok_void_t, 0},
    {"i8", tok_i8_t, 0},
    {"u8", tok_u8_t, 0},
    {"i16", tok_i16_t, 0},
    {"u16", tok_u16_t, 0},
    {"i32", tok_i32_t, 0},
    {"u32", tok_u32_t, 0},
    {"i64", tok_i64_t, 0},
    {"u64", tok_u64_t, 0},
    {"char", tok_char_t, 0},
    {"char8", tok_char8_t, 0},
    {"char16", tok_char16_t, 0},
    {"bool", tok_bool_t, 0},
    {"f32", tok_f32_t, 0},
    {"f64", tok_f64_t, 0},
    /* constant */
    {"null", tok_null, 0},
    {"true", tok_true, 0},
    {"false", tok_false, 0},
    /* control flow operators */
    {"if", tok_if, 0},
    {"else", tok_else, 0},
    {"for", tok_for, 0},
    {"while", tok_while, 0},
    {"switch", tok_switch, 0},
    {"case", tok_case, 0},
    {"brake", tok_break, 0},
    {"braketo", tok_breakto, 0},
    {"return", tok_return, 0},
    {"goto", tok_goto, 0},
    /* declaration keywords */
    {"class", tok_class, 0},
    {"struct", tok_struct, 0},
    {"enum", tok_enum, 0},
    {"union", tok_union, 0},
    {"event", tok_event, 0},
    {"import", tok_import, 0},
    {"alias", tok_alias, 0},
    /* access modifiers */
    {"static", tok_static, 0},
    {"const", tok_const, 0},
    {"readonly", tok_readonly, 0},
    {"protected", tok_protected, 0},
    {"internal", tok_internal, 0},
    {"public", tok_public, 0},
    {"virtual", tok_virtual, 0},
    {"override", tok_override, 0},
    {"partial", tok_partial, 0},
    /* allocation keywords */
    {"new", tok_new, 0},
    {"sizeof", tok_sizeof, 0},
    {"typeof", tok_typeof, 0},
    /* special characters */
    {"(", tok_lbracket, 0},
    {"{", tok_lbracket_fi, 0},
    {"[", tok_lbracket_sq, 0},
    {")", tok_rbracket, 0},
    {"}", tok_rbracket_fi, 0},
    {"]", tok_rbracket_sq, 0},
    {"<", tok_less, 0},
    {">", tok_more, 0},
    {"+", tok_plus, 0},
    {"-", tok_minus, 0},
    {"*", tok_asterisk, 0},
    {"/", tok_slash, 0},
    {"=", tok_assign, 0},
    {"!", tok_not, 0},
    {"==", tok_equal, 0},
    {"!=", tok_not_equal, 0},
    {"&", tok_and, 0},
    {"&&", tok_and_d, 0},
    {"|", tok_or, 0},
    {"||", tok_or_d, 0},
    {"?", tok_question, 0},
    {"??", tok_question_d, 0},
    {":", tok_colon, 0},
    {";", tok_semicolon, 0},
    {".", tok_point, 0},
    {",", tok_comma, 0},
    {"~", tok_tilda, 0},
    {"\\", tok_backslash, 0},
    {"%", tok_percent, 0},
    {"^", tok_xor, 0},
    {"#", tok_lattice, 0},
    {"$", tok_dollar, 0},
    {"@", tok_at, 0}
};
