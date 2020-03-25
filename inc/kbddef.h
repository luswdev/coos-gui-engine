/**
 *******************************************************************************
 * @file       kbddef.h
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      This is a file for keyboard define.
 *******************************************************************************
 */ 

#ifndef __GUI_KBDDEF_H__
#define __GUI_KBDDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/**< key mapping according to ASCII table */
typedef enum {
    GUI_KEY_FIRST           = 0,
    
    /* control character */
    GUI_KEY_UNKNOW          = 0,        /* ^@ */
    GUI_KEY_BACKSPACE       = 8,        /* ^H */
    GUI_KEY_TAB             = 9,        /* ^I */
    GUI_KEY_ENTER           = 10,       /* ^J */
    GUI_KEY_CLEAR           = 12,       /* ^K */

    /* symbol part. 1 */
    GUI_KEY_SPACE           = 32,       /*   */
    GUI_KEY_EXCLAIM         = 33,       /* ! */
    GUI_KEY_QUOTEDBL        = 34,       /* " */
    GUI_KEY_HASH            = 35,       /* # */
    GUI_KEY_DOLLAR          = 36,       /* $ */
    GUI_KEY_PERCENT         = 37,       /* % */
    GUI_KEY_AMPERSAND       = 38,       /* & */
    GUI_KEY_QUOTE           = 39,       /* ' */
    GUI_KEY_LPAREN          = 40,       /* ( */
    GUI_KEY_RPAREN          = 41,       /* ) */
    GUI_KEY_ASTERISK        = 42,       /* * */
    GUI_KEY_PLUS            = 43,       /* + */
    GUI_KEY_COMMA           = 44,       /* , */
    GUI_KEY_MINUS           = 45,       /* - */
    GUI_KEY_PERIOD          = 46,       /* . */
    GUI_KEY_SLASH           = 47,       /* / */

    /* 0 ~ 9 */
    GUI_KEY_0               = 48,       /* 0 */
    GUI_KEY_1               = 49,       /* 1 */
    GUI_KEY_2               = 50,       /* 2 */
    GUI_KEY_3               = 51,       /* 3 */
    GUI_KEY_4               = 52,       /* 4 */
    GUI_KEY_5               = 53,       /* 5 */
    GUI_KEY_6               = 54,       /* 6 */
    GUI_KEY_7               = 55,       /* 7 */
    GUI_KEY_8               = 56,       /* 8 */
    GUI_KEY_9               = 57,       /* 9 */

    /* symbol part. 2 */
    GUI_KEY_COLON           = 58,       /* : */
    GUI_KEY_SEMICOLON       = 59,       /* ; */
    GUI_KEY_LESS            = 60,       /* < */
    GUI_KEY_EQUAL           = 61,       /* = */
    GUI_KEY_GREATER         = 62,       /* > */
    GUI_KEY_QUESTION        = 63,       /* ? */
    GUI_KEY_AT              = 64,       /* @ */

    /* upper case A ~ Z */
    GUI_KEY_UPPER_A         = 65,       /* A */
    GUI_KEY_UPPER_B         = 66,       /* B */
    GUI_KEY_UPPER_C         = 67,       /* C */
    GUI_KEY_UPPER_D         = 68,       /* D */
    GUI_KEY_UPPER_E         = 69,       /* E */
    GUI_KEY_UPPER_F         = 70,       /* F */
    GUI_KEY_UPPER_G         = 71,       /* G */
    GUI_KEY_UPPER_H         = 72,       /* H */
    GUI_KEY_UPPER_I         = 73,       /* I */
    GUI_KEY_UPPER_J         = 74,       /* J */
    GUI_KEY_UPPER_K         = 75,       /* K */
    GUI_KEY_UPPER_L         = 76,       /* L */
    GUI_KEY_UPPER_M         = 77,       /* M */
    GUI_KEY_UPPER_N         = 78,       /* N */
    GUI_KEY_UPPER_O         = 79,       /* O */
    GUI_KEY_UPPER_P         = 80,       /* P */
    GUI_KEY_UPPER_Q         = 81,       /* Q */
    GUI_KEY_UPPER_R         = 82,       /* R */
    GUI_KEY_UPPER_S         = 83,       /* S */
    GUI_KEY_UPPER_T         = 84,       /* T */
    GUI_KEY_UPPER_U         = 85,       /* U */
    GUI_KEY_UPPER_V         = 86,       /* V */
    GUI_KEY_UPPER_W         = 87,       /* W */
    GUI_KEY_UPPER_X         = 88,       /* X */
    GUI_KEY_UPPER_Y         = 89,       /* Y */
    GUI_KEY_UPPER_Z         = 90,       /* Z */

    /* symbol part. 3 */
    GUI_KEY_LBRACKET        = 91,       /* [ */
    GUI_KEY_BACKSLASH       = 92,       /* \ */
    GUI_KEY_RBRACKET        = 93,       /* ] */
    GUI_KEY_CARET           = 94,       /* ^ */
    GUI_KEY_UNDERSCORE      = 95,       /* _ */
    GUI_KEY_BACKQUOTE       = 96,       /* ` */

    /* lower case a ~ z */
    GUI_KEY_LOWER_A         = 97,       /* a */
    GUI_KEY_LOWER_B         = 98,       /* b */
    GUI_KEY_LOWER_C         = 99,       /* c */
    GUI_KEY_LOWER_D         = 100,      /* d */
    GUI_KEY_LOWER_E         = 101,      /* e */
    GUI_KEY_LOWER_F         = 102,      /* f */
    GUI_KEY_LOWER_G         = 103,      /* g */
    GUI_KEY_LOWER_H         = 104,      /* h */
    GUI_KEY_LOWER_I         = 105,      /* i */
    GUI_KEY_LOWER_J         = 106,      /* j */
    GUI_KEY_LOWER_K         = 107,      /* k */
    GUI_KEY_LOWER_L         = 108,      /* l */
    GUI_KEY_LOWER_M         = 109,      /* m */
    GUI_KEY_LOWER_N         = 110,      /* n */
    GUI_KEY_LOWER_O         = 111,      /* o */
    GUI_KEY_LOWER_P         = 112,      /* p */
    GUI_KEY_LOWER_Q         = 113,      /* q */
    GUI_KEY_LOWER_R         = 114,      /* r */
    GUI_KEY_LOWER_S         = 115,      /* s */
    GUI_KEY_LOWER_T         = 116,      /* t */
    GUI_KEY_LOWER_U         = 117,      /* u */
    GUI_KEY_LOWER_V         = 118,      /* v */
    GUI_KEY_LOWER_W         = 119,      /* w */
    GUI_KEY_LOWER_X         = 120,      /* x */
    GUI_KEY_LOWER_Y         = 121,      /* y */
    GUI_KEY_LOWER_Z         = 122,      /* z */

    /* symbol part. 4 */
    GUI_KEY_LCBARCKET       = 123,      /* { */
    GUI_KEY_PIPE            = 124,      /* | */
    GUI_KEY_RCBARCKET       = 125,      /* } */
    GUI_KEY_TILDE           = 126,      /* ~ */

    /* last control key */
    GUI_KEY_DEL             = 127,      /* ^? */

    /* numeric keypad */
    GUI_KEY_NUM_0           = 128,      /* 0 */
    GUI_KEY_NUM_1           = 129,      /* 1 */
    GUI_KEY_NUM_2           = 130,      /* 2 */
    GUI_KEY_NUM_3           = 131,      /* 3 */
    GUI_KEY_NUM_4           = 132,      /* 4 */
    GUI_KEY_NUM_5           = 133,      /* 5 */
    GUI_KEY_NUM_6           = 134,      /* 6 */
    GUI_KEY_NUM_7           = 135,      /* 7 */
    GUI_KEY_NUM_8           = 136,      /* 8 */
    GUI_KEY_NUM_9           = 137,      /* 9 */
    GUI_KEY_NUM_PERIOD      = 138,      /* . */
    GUI_KEY_NUM_DIVIDE      = 139,      /* / */
    GUI_KEY_NUM_MULTIPLY    = 140,      /* * */
    GUI_KEY_NUM_MINUS       = 141,      /* - */
    GUI_KEY_NUM_PLUS        = 142,      /* + */
    GUI_KEY_NUM_ENTER       = 143,      /* ^J */

    /* arrows and position keys */
    GUI_KEY_UP              = 144,
    GUI_KEY_DOWN            = 145,
    GUI_KEY_LEFT            = 146,
    GUI_KEY_RIGHT           = 147,
    GUI_KEY_HOME            = 148,
    GUI_KEY_END             = 149,
    GUI_KEY_PAGEUP          = 150,
    GUI_KEY_PAGEDOWN        = 151,

    /* function keys */
    GUI_KEY_F1              = 152,
    GUI_KEY_F2              = 153,
    GUI_KEY_F3              = 154,
    GUI_KEY_F4              = 155,
    GUI_KEY_F5              = 156,
    GUI_KEY_F6              = 157,
    GUI_KEY_F7              = 158,
    GUI_KEY_F8              = 159,
    GUI_KEY_F9              = 160,
    GUI_KEY_F10             = 161,
    GUI_KEY_F11             = 162,
    GUI_KEY_F12             = 163,
    GUI_KEY_F13             = 164,
    GUI_KEY_F14             = 165,
    GUI_KEY_F15             = 166,

    /* modifier keys */
    GUI_KEY_NUMLOCK         = 167,
    GUI_KEY_CAPSLOCK        = 168,
    GUI_KEY_LSHIFT          = 169,
    GUI_KEY_RSHIFT          = 170,
    GUI_KEY_LCTRL           = 171,
    GUI_KEY_RCTRL           = 172,
    GUI_KEY_LALT            = 173,
    GUI_KEY_RALT            = 174,
    GUI_KEY_LSUPER          = 175,
    GUI_KEY_RSUPER          = 176,
    
    GUI_KEY_LAST
} GUI_KBD_KEY;

typedef enum {
    GUI_KBD_MOD_NONE        = 0x0000,
    GUI_KBD_MOD_LSHIFT      = 0x0001,
    GUI_KBD_MOD_RSHIFT      = 0x0002,
    GUI_KBD_MOD_LCTRL       = 0x0004,
    GUI_KBD_MOD_RCTRL       = 0x0008,
    GUI_KBD_MOD_LALT        = 0x0010,
    GUI_KBD_MOD_RALT        = 0x0020,
    GUI_KBD_MOD_LSUPER      = 0x0040,
    GUI_KBD_MOD_RSUPER      = 0x0080,
    GUI_KBD_MOD_NUM         = 0x0100,
    GUI_KBD_MOD_CAPS        = 0x0200
} GUI_KBD_MOD;

typedef enum {
    GUI_KEYDOWN,          /* Keys pressed */
    GUI_KEYUP             /* Keys released */
} GUI_KBD_TYPE;

#ifdef __cplusplus
}
#endif

#endif /* __GUI_KBDDEF_H__ */
