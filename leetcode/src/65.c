/*
 * Returns a boolean value of true if the input string is a valid number.
 * Heavily optimized solution that utilizes branch prediction builtin's provided by
 * GCC and clang.
 * Uses a 4-bit bitset to track state of the program.
 *
 * Copyright (C) Mustafa Aamir <mustafa.290101@gmail.com>
 * */


/* Defining branch prediction and inline macros */
#if defined(__GNUC__) || defined(__clang__)
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define _force_inline __attribute__((always_inline)) static inline
#else
#define likely(x) x
#define unlikely(x) x
#define _force_inline static inline
#endif

/* stdbool compatibility */
#ifndef __STDBOOL_H
#define bool int
#define true 1
#define false 0
#endif


/* Bitset to track the state of the program
 * Going from MSB to LSB, a high value for each bit represents the following values:
 * 1. decimal: '.' used
 * 2. sign '+' or '-' seen
 * 3. exponential 'E' or 'e' seen
 * 4. Integer value {0..9} seen
 */
typedef struct {
    unsigned flag : 4;
} state_t;

_force_inline bool isDigit(const char c) {
    return (unsigned char)(c - '0') < 10;
}

_force_inline bool isNumber(const char *s) {
    // initializing state bitset
    state_t state = {0};

    // performing checks on the first char of the input
    if (unlikely(*s == '\0')) {
        return false;
    } else if (likely(isDigit(*s))) {
        state.flag |= 0x1;
    } else if (likely(*s == '+' || *s == '-')) {
        state.flag |= 0x4;
    } else if (*s == '.') {
        state.flag |= 0x8;
    } else {
      return false;
    }

    // iterating over subsequent characters of the input string
    while (likely(*++s != '\0')) {
        if (likely(isDigit(*s))) {
            state.flag |= 1;
            continue;
        }
        switch (*s) {
            case 'E': case 'e':
                if (state.flag & 2 || !(state.flag & 1)) return false;
                state.flag = 2; break;
            case '+': case '-':
                if (state.flag & 13) return false; // check for exp?
                state.flag |= 4; break;
            case '.':
                if (unlikely(state.flag & 10)) return false;
                state.flag |= 8; break;
            default:
                return false;
        }
    }
    return state.flag & 1;
}
