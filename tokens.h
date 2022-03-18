#include ""

typedef enum TokenId{
    // base types
    tok_void,
    tok_int8,
    tok_uint8,
    tok_int16,
    tok_uint16,
    tok_int32,
    tok_uint32,
    tok_int64,
    tok_uint64,
    tok_char,      //ascii
    tok_char8,     //utf8
    tok_char16,    //utf16
    tok_bool,
    tok_float32,
    tok_float64,
    // constant
    tok_null,
    tok_true,
    tok_false,
    // control flow operators
    tok_if,
    tok_for,
    tok_while,
    tok_switch,
    tok_case,
    tok_brake,
    tok_return,
    // declaration keywords
    tok_struct,
    tok_enum,
    tok_union,
    tok_alias,
    tok_event,
    tok_import,
    // access modiiers
    tok_const,
    tok_protected,
    tok_public,
    tok_virtual,
    // cpecial characters
    tok_lbracket,    // (
    tok_lbracket_fi, // {
    tok_lbracket_sq, // [
    tok_rbracket,    // )
    tok_rbracket_fi, // }
    tok_rbracket_sq, // ]
    tok_quot,        // '
    tok_quot_d,      // "
    tok_less,        // <
    tok_more,        // >
    tok_plus,        // +
    tok_minus,       // -
    tok_multip,      // *
    tok_divide,      // /
    tok_assign,      // =
    tok_colon,       // :
    tok_semicolon,   // ;
    tok_point,       // .
    tok_comma,       // ,
    tok_question,    // ?
    tok_question_d,  // ??
    tok_and,         // &
    tok_and_d,       // &&
    tok_or,          // |
    tok_or_d,        // ||
    tok_not,         // !
    tok_equals,      // ==
    tok_not_equals,  // !=
    tok_tilda,       // ~
    tok_backslash,   // \
    tok_percent,     // %
    tok_xor,         // ^
    tok_lattice,     // #
    tok_dollar,      // $
    tok_
} __attribute__((__packed__)) TokenId;

typedef struct Token{
    TokenId id;
    Unitype value;
} Token;
