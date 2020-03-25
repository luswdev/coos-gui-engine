/**
 *******************************************************************************
 * @file       kbddef.h
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      This is a file for keyboard define.
 *******************************************************************************
 */ 

#ifndef __KBD_KBDDEF_H__
#define __KBD_KBDDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/**< key mapping according to ASCII table */
typedef enum {
    KBD_KEY_FIRST           = 0,
    
    /* control character */
    KBD_KEY_UNKNOW          = 0,        /* ^@ */
    KBD_KEY_BACKSPACE       = 8,        /* ^H */
    KBD_KEY_TAB             = 9,        /* ^I */
    KBD_KEY_ENTER           = 10,       /* ^J */
    KBD_KEY_CLEAR           = 12,       /* ^K */

    /* symbol part. 1 */
    KBD_KEY_SPACE           = 32,       /*   */
    KBD_KEY_EXCLAIM         = 33,       /* ! */
    KBD_KEY_QUOTEDBL        = 34,       /* " */
    KBD_KEY_HASH            = 35,       /* # */
    KBD_KEY_DOLLAR          = 36,       /* $ */
    KBD_KEY_PERCENT         = 37,       /* % */
    KBD_KEY_AMPERSAND       = 38,       /* & */
    KBD_KEY_QUOTE           = 39,       /* ' */
    KBD_KEY_LPAREN          = 40,       /* ( */
    KBD_KEY_RPAREN          = 41,       /* ) */
    KBD_KEY_ASTERISK        = 42,       /* * */
    KBD_KEY_PLUS            = 43,       /* + */
    KBD_KEY_COMMA           = 44,       /* , */
    KBD_KEY_MINUS           = 45,       /* - */
    KBD_KEY_PERIOD          = 46,       /* . */
    KBD_KEY_SLASH           = 47,       /* / */

    /* 0 ~ 9 */
    KBD_KEY_0               = 48,       /* 0 */
    KBD_KEY_1               = 49,       /* 1 */
    KBD_KEY_2               = 50,       /* 2 */
    KBD_KEY_3               = 51,       /* 3 */
    KBD_KEY_4               = 52,       /* 4 */
    KBD_KEY_5               = 53,       /* 5 */
    KBD_KEY_6               = 54,       /* 6 */
    KBD_KEY_7               = 55,       /* 7 */
    KBD_KEY_8               = 56,       /* 8 */
    KBD_KEY_9               = 57,       /* 9 */

    /* symbol part. 2 */
    KBD_KEY_COLON           = 58,       /* : */
    KBD_KEY_SEMICOLON       = 59,       /* ; */
    KBD_KEY_LESS            = 60,       /* < */
    KBD_KEY_EQUAL           = 61,       /* = */
    KBD_KEY_GREATER         = 62,       /* > */
    KBD_KEY_QUESTION        = 63,       /* ? */
    KBD_KEY_AT              = 64,       /* @ */

    /* upper case A ~ Z */
    KBD_KEY_UPPER_A         = 65,       /* A */
    KBD_KEY_UPPER_B         = 66,       /* B */
    KBD_KEY_UPPER_C         = 67,       /* C */
    KBD_KEY_UPPER_D         = 68,       /* D */
    KBD_KEY_UPPER_E         = 69,       /* E */
    KBD_KEY_UPPER_F         = 70,       /* F */
    KBD_KEY_UPPER_G         = 71,       /* G */
    KBD_KEY_UPPER_H         = 72,       /* H */
    KBD_KEY_UPPER_I         = 73,       /* I */
    KBD_KEY_UPPER_J         = 74,       /* J */
    KBD_KEY_UPPER_K         = 75,       /* K */
    KBD_KEY_UPPER_L         = 76,       /* L */
    KBD_KEY_UPPER_M         = 77,       /* M */
    KBD_KEY_UPPER_N         = 78,       /* N */
    KBD_KEY_UPPER_O         = 79,       /* O */
    KBD_KEY_UPPER_P         = 80,       /* P */
    KBD_KEY_UPPER_Q         = 81,       /* Q */
    KBD_KEY_UPPER_R         = 82,       /* R */
    KBD_KEY_UPPER_S         = 83,       /* S */
    KBD_KEY_UPPER_T         = 84,       /* T */
    KBD_KEY_UPPER_U         = 85,       /* U */
    KBD_KEY_UPPER_V         = 86,       /* V */
    KBD_KEY_UPPER_W         = 87,       /* W */
    KBD_KEY_UPPER_X         = 88,       /* X */
    KBD_KEY_UPPER_Y         = 89,       /* Y */
    KBD_KEY_UPPER_Z         = 90,       /* Z */

    /* symbol part. 3 */
    KBD_KEY_LBRACKET        = 91,       /* [ */
    KBD_KEY_BACKSLASH       = 92,       /* \ */
    KBD_KEY_RBRACKET        = 93,       /* ] */
    KBD_KEY_CARET           = 94,       /* ^ */
    KBD_KEY_UNDERSCORE      = 95,       /* _ */
    KBD_KEY_BACKQUOTE       = 96,       /* ` */

    /* lower case a ~ z */
    KBD_KEY_LOWER_A         = 97,       /* a */
    KBD_KEY_LOWER_B         = 98,       /* b */
    KBD_KEY_LOWER_C         = 99,       /* c */
    KBD_KEY_LOWER_D         = 100,      /* d */
    KBD_KEY_LOWER_E         = 101,      /* e */
    KBD_KEY_LOWER_F         = 102,      /* f */
    KBD_KEY_LOWER_G         = 103,      /* g */
    KBD_KEY_LOWER_H         = 104,      /* h */
    KBD_KEY_LOWER_I         = 105,      /* i */
    KBD_KEY_LOWER_J         = 106,      /* j */
    KBD_KEY_LOWER_K         = 107,      /* k */
    KBD_KEY_LOWER_L         = 108,      /* l */
    KBD_KEY_LOWER_M         = 109,      /* m */
    KBD_KEY_LOWER_N         = 110,      /* n */
    KBD_KEY_LOWER_O         = 111,      /* o */
    KBD_KEY_LOWER_P         = 112,      /* p */
    KBD_KEY_LOWER_Q         = 113,      /* q */
    KBD_KEY_LOWER_R         = 114,      /* r */
    KBD_KEY_LOWER_S         = 115,      /* s */
    KBD_KEY_LOWER_T         = 116,      /* t */
    KBD_KEY_LOWER_U         = 117,      /* u */
    KBD_KEY_LOWER_V         = 118,      /* v */
    KBD_KEY_LOWER_W         = 119,      /* w */
    KBD_KEY_LOWER_X         = 120,      /* x */
    KBD_KEY_LOWER_Y         = 121,      /* y */
    KBD_KEY_LOWER_Z         = 122,      /* z */

    /* symbol part. 4 */
    KBD_KEY_LCBARCKET       = 123,      /* { */
    KBD_KEY_PIPE            = 124,      /* | */
    KBD_KEY_RCBARCKET       = 125,      /* } */
    KBD_KEY_TILDE           = 126,      /* ~ */

    /* last control key */
    KBD_KEY_DEL             = 127,      /* ^? */

    /* numeric keypad */
    KBD_KEY_NUM_0           = 128,      /* 0 */
    KBD_KEY_NUM_1           = 129,      /* 1 */
    KBD_KEY_NUM_2           = 130,      /* 2 */
    KBD_KEY_NUM_3           = 131,      /* 3 */
    KBD_KEY_NUM_4           = 132,      /* 4 */
    KBD_KEY_NUM_5           = 133,      /* 5 */
    KBD_KEY_NUM_6           = 134,      /* 6 */
    KBD_KEY_NUM_7           = 135,      /* 7 */
    KBD_KEY_NUM_8           = 136,      /* 8 */
    KBD_KEY_NUM_9           = 137,      /* 9 */
    KBD_KEY_NUM_PERIOD      = 138,      /* . */
    KBD_KEY_NUM_DIVIDE      = 139,      /* / */
    KBD_KEY_NUM_MULTIPLY    = 140,      /* * */
    KBD_KEY_NUM_MINUS       = 141,      /* - */
    KBD_KEY_NUM_PLUS        = 142,      /* + */
    KBD_KEY_NUM_ENTER       = 143,      /* ^J */

    /* arrows and position keys */
    KBD_KEY_UP              = 144,
    KBD_KEY_DOWN            = 145,
    KBD_KEY_LEFT            = 146,
    KBD_KEY_RIGHT           = 147,
    KBD_KEY_HOME            = 148,
    KBD_KEY_END             = 149,
    KBD_KEY_PAGEUP          = 150,
    KBD_KEY_PAGEDOWN        = 151,

    /* function keys */
    KBD_KEY_F1              = 152,
    KBD_KEY_F2              = 153,
    KBD_KEY_F3              = 154,
    KBD_KEY_F4              = 155,
    KBD_KEY_F5              = 156,
    KBD_KEY_F6              = 157,
    KBD_KEY_F7              = 158,
    KBD_KEY_F8              = 159,
    KBD_KEY_F9              = 160,
    KBD_KEY_F10             = 161,
    KBD_KEY_F11             = 162,
    KBD_KEY_F12             = 163,
    KBD_KEY_F13             = 164,
    KBD_KEY_F14             = 165,
    KBD_KEY_F15             = 166,

    /* modifier keys */
    KBD_KEY_NUMLOCK         = 167,
    KBD_KEY_CAPSLOCK        = 168,
    KBD_KEY_LSHIFT          = 169,
    KBD_KEY_RSHIFT          = 170,
    KBD_KEY_LCTRL           = 171,
    KBD_KEY_RCTRL           = 172,
    KBD_KEY_LALT            = 173,
    KBD_KEY_RALT            = 174,
    KBD_KEY_LSUPER          = 175,
    KBD_KEY_RSUPER          = 176,
    
    KBD_KEY_LAST
} KBD_KBD_KEY;

typedef enum {
    KBD_MOD_NONE        = 0x0000,
    KBD_MOD_LSHIFT      = 0x0001,
    KBD_MOD_RSHIFT      = 0x0002,
    KBD_MOD_LCTRL       = 0x0004,
    KBD_MOD_RCTRL       = 0x0008,
    KBD_MOD_LALT        = 0x0010,
    KBD_MOD_RALT        = 0x0020,
    KBD_MOD_LSUPER      = 0x0040,
    KBD_MOD_RSUPER      = 0x0080,
    KBD_MOD_NUM         = 0x0100,
    KBD_MOD_CAPS        = 0x0200
} KBD_KBD_MOD;

typedef enum {
    KBD_KEYDOWN,          /* Keys pressed */
    KBD_KEYUP             /* Keys released */
} KBD_KBD_TYPE;

#ifdef __cplusplus
}
#endif

#endif /* __KBD_KBDDEF_H__ */
