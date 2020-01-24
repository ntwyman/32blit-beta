#include "game.hpp"
#include <iostream>

using namespace blit;
const uint8_t level1[] = {/* 0cd0 */
                          /*0x0cd0*/ 0x0d,
                          0x04,
                          0x00,
                          0x0a,
                          0x02,
                          0x01,
                          0x00,
                          0x13,
                          0x06,
                          0x01,
                          0x12,
                          0x0b,
                          0x02,
                          0x08,
                          0x0b,
                          0x0e,
                          /*0x0ce0*/ 0x12,
                          0x0c,
                          0x09,
                          0x0a,
                          0x0d,
                          0x0b,
                          0x0c,
                          0x0e,
                          0x0d,
                          0x0e,
                          0x0f,
                          0x0f,
                          0x10,
                          0x10,
                          0x03,
                          0x07,
                          /*0x0cf0*/ 0x11,
                          0x09,
                          0x0b,
                          0x15,
                          0x05,
                          0x09,
                          0x15,
                          0x0b,
                          0x10,
                          0x15,
                          0x12,
                          0x13,
                          0x03,
                          0x07,
                          0x0d,
                          0x07,
                          /*0x0d00*/ 0x02,
                          0x17,
                          0x0b,
                          0x02,
                          0x08,
                          0x10,
                          0x02,
                          0x08,
                          0x04,
                          0x02,
                          0x01,
                          0x07,
                          0x0d,
                          0x07,
                          0x12,
                          0x07,
                          /*0x0d10*/ 0x02,
                          0x0c,
                          0x0a,
                          0x0d,
                          0x11,
                          0x0c,
                          0x04,
                          0x11,
                          0x0a,
                          0x12,
                          0x06,
                          0x16,
                          0x0d,
                          0x16,
                          0x13,
                          0x16,
                          /*0x0d20*/ 0x02,
                          0x02,
                          0x0d,
                          0x02,
                          0x05,
                          0x07,
                          0x0e,
                          0x07,
                          0x05,
                          0x0c,
                          0x0f,
                          0x0c,
                          0x10,
                          0x10,
                          0x0b,
                          0x12,
                          /*0x0d30*/ 0x09,
                          0x16,
                          0x0e,
                          0x16,
                          0x05,
                          0x11,
                          0x08,
                          0x16,
                          0x04,
                          0x0c,
                          0x06,
                          0x07,
                          0x0c,
                          0x02};
const uint8_t level2[] = {/* 0d3e */
                          0x0d,
                          0x08,
                          /*0x0d40*/ 0x00,
                          0x07,
                          0x03,
                          0x01,
                          0x00,
                          0x03,
                          0x01,
                          0x05,
                          0x13,
                          0x06,
                          0x00,
                          0x06,
                          0x06,
                          0x08,
                          0x0a,
                          0x06,
                          /*0x0d50*/ 0x0c,
                          0x0e,
                          0x06,
                          0x10,
                          0x13,
                          0x0b,
                          0x00,
                          0x03,
                          0x0b,
                          0x05,
                          0x0e,
                          0x0b,
                          0x10,
                          0x13,
                          0x10,
                          0x00,
                          /*0x0d60*/ 0x0a,
                          0x10,
                          0x0c,
                          0x13,
                          0x15,
                          0x04,
                          0x0a,
                          0x15,
                          0x0c,
                          0x13,
                          0x02,
                          0x02,
                          0x12,
                          0x04,
                          0x11,
                          0x17,
                          /*0x0d70*/ 0x06,
                          0x07,
                          0x12,
                          0x09,
                          0x02,
                          0x08,
                          0x09,
                          0x0c,
                          0x17,
                          0x0d,
                          0x0c,
                          0x12,
                          0x11,
                          0x02,
                          0x0d,
                          0x11,
                          /*0x0d80*/ 0x11,
                          0x17,
                          0x05,
                          0x02,
                          0x0c,
                          0x02,
                          0x00,
                          0x07,
                          0x04,
                          0x07,
                          0x0d,
                          0x07,
                          0x00,
                          0x0c,
                          0x07,
                          0x0c,
                          /*0x0d90*/ 0x13,
                          0x0c,
                          0x07,
                          0x11,
                          0x07,
                          0x16,
                          0x0f,
                          0x16,
                          0x13,
                          0x16,
                          0x00,
                          0x02,
                          0x03,
                          0x02,
                          0x0f,
                          0x02,
                          /*0x0da0*/ 0x10,
                          0x07,
                          0x00,
                          0x11,
                          0x0a,
                          0x11,
                          0x0c,
                          0x16,
                          0x06,
                          0x16,
                          0x01,
                          0x02,
                          0x12,
                          0x0c,
                          0x0b,
                          0x0c,
                          /*0x0db0*/ 0x0d,
                          0x16};
const uint8_t level3[] = {/* 0db2 */
                          0x18,
                          0x07,
                          0x01,
                          0x0a,
                          0x03,
                          0x01,
                          0x00,
                          0x02,
                          0x02,
                          0x03,
                          0x04,
                          0x01,
                          0x07,
                          0x09,
                          /*0x0dc0*/ 0x01,
                          0x0b,
                          0x13,
                          0x05,
                          0x0f,
                          0x12,
                          0x0a,
                          0x00,
                          0x04,
                          0x0f,
                          0x00,
                          0x03,
                          0x13,
                          0x03,
                          0x04,
                          0x06,
                          /*0x0dd0*/ 0x07,
                          0x0a,
                          0x06,
                          0x0c,
                          0x0c,
                          0x07,
                          0x0e,
                          0x0e,
                          0x08,
                          0x0f,
                          0x0f,
                          0x09,
                          0x11,
                          0x11,
                          0x0a,
                          0x12,
                          /*0x0de0*/ 0x13,
                          0x0c,
                          0x0c,
                          0x0d,
                          0x0c,
                          0x0f,
                          0x0f,
                          0x0f,
                          0x12,
                          0x13,
                          0x10,
                          0x11,
                          0x11,
                          0x11,
                          0x0f,
                          0x0f,
                          /*0x0df0*/ 0x12,
                          0x0c,
                          0x0d,
                          0x13,
                          0x07,
                          0x0b,
                          0x15,
                          0x0d,
                          0x0f,
                          0x14,
                          0x10,
                          0x10,
                          0x14,
                          0x12,
                          0x13,
                          0x01,
                          /*0x0e00*/ 0x02,
                          0x0c,
                          0x03,
                          0x0b,
                          0x15,
                          0x08,
                          0x07,
                          0x15,
                          0x0a,
                          0x07,
                          0x15,
                          0x0d,
                          0x13,
                          0x17,
                          0x12,
                          0x02,
                          /*0x0e10*/ 0x07,
                          0x13,
                          0x0b,
                          0x11,
                          0x05,
                          0x04,
                          0x03,
                          0x0f,
                          0x02,
                          0x10,
                          0x06,
                          0x04,
                          0x0b,
                          0x04,
                          0x14,
                          0x09,
                          /*0x0e20*/ 0x07,
                          0x0f,
                          0x09,
                          0x0f,
                          0x0d,
                          0x01,
                          0x10,
                          0x11,
                          0x11,
                          0x13,
                          0x12,
                          0x13,
                          0x15,
                          0x02,
                          0x02,
                          0x02,
                          /*0x0e30*/ 0x0b,
                          0x07,
                          0x07,
                          0x07,
                          0x14,
                          0x00,
                          0x10,
                          0x0d,
                          0x02,
                          0x0c,
                          0x13,
                          0x0f,
                          0x12,
                          0x0d,
                          0x0d,
                          0x12,
                          /*0x0e40*/ 0x15,
                          0x02,
                          0x10,
                          0x09,
                          0x14,
                          0x11,
                          0x06,
                          0x00,
                          0x02,
                          0x08,
                          0x07};
const uint8_t level4[] = {/* 0e4b */
                          0x1a,
                          0x05,
                          0x01,
                          0x06,
                          0x04,
                          /*0x0e50*/ 0x01,
                          0x00,
                          0x04,
                          0x01,
                          0x06,
                          0x0a,
                          0x01,
                          0x0d,
                          0x13,
                          0x06,
                          0x00,
                          0x04,
                          0x06,
                          0x07,
                          0x0a,
                          0x06,
                          /*0x0e60*/ 0x0d,
                          0x11,
                          0x05,
                          0x13,
                          0x13,
                          0x0c,
                          0x00,
                          0x01,
                          0x0d,
                          0x03,
                          0x03,
                          0x0e,
                          0x05,
                          0x05,
                          0x0f,
                          0x07,
                          /*0x0e70*/ 0x08,
                          0x0b,
                          0x07,
                          0x08,
                          0x0b,
                          0x0d,
                          0x10,
                          0x0a,
                          0x12,
                          0x13,
                          0x10,
                          0x08,
                          0x0a,
                          0x11,
                          0x00,
                          0x00,
                          /*0x0e80*/ 0x12,
                          0x02,
                          0x02,
                          0x13,
                          0x03,
                          0x03,
                          0x14,
                          0x04,
                          0x04,
                          0x15,
                          0x05,
                          0x05,
                          0x15,
                          0x07,
                          0x0a,
                          0x10,
                          /*0x0e90*/ 0x0d,
                          0x0e,
                          0x10,
                          0x10,
                          0x10,
                          0x10,
                          0x12,
                          0x13,
                          0x15,
                          0x0d,
                          0x0f,
                          0x15,
                          0x11,
                          0x13,
                          0x03,
                          0x02,
                          /*0x0ea0*/ 0x08,
                          0x08,
                          0x02,
                          0x17,
                          0x0e,
                          0x0c,
                          0x17,
                          0x0f,
                          0x02,
                          0x08,
                          0x13,
                          0x10,
                          0x17,
                          0x0b,
                          0x00,
                          0x02,
                          /*0x0eb0*/ 0x00,
                          0x0d,
                          0x00,
                          0x12,
                          0x07,
                          0x07,
                          0x09,
                          0x11,
                          0x0d,
                          0x02,
                          0x10,
                          0x07,
                          0x0d,
                          0x0c,
                          0x13,
                          0x0b,
                          /*0x0ec0*/ 0x11,
                          0x10,
                          0x10,
                          0x15,
                          0x10,
                          0x18,
                          0x00,
                          0x07,
                          0x0a,
                          0x02,
                          0x12,
                          0x02,
                          0x05,
                          0x0f,
                          0x09,
                          0x16,
                          /*0x0ed0*/ 0x0d,
                          0x16,
                          0x0a,
                          0x16,
                          0x11,
                          0x16,
                          0x11,
                          0x02,
                          0x04,
                          0x02,
                          0x0a,
                          0x07};
const uint8_t level5[] = {/* 0edc */
                          0x11,
                          0x09,
                          0x01,
                          0x0d,
                          /*0x0ee0*/ 0x04,
                          0x01,
                          0x00,
                          0x01,
                          0x01,
                          0x03,
                          0x0b,
                          0x01,
                          0x0d,
                          0x0f,
                          0x01,
                          0x12,
                          0x13,
                          0x06,
                          0x00,
                          0x05,
                          /*0x0ef0*/ 0x06,
                          0x09,
                          0x0c,
                          0x06,
                          0x0e,
                          0x0f,
                          0x0b,
                          0x00,
                          0x05,
                          0x0b,
                          0x0a,
                          0x0f,
                          0x0b,
                          0x13,
                          0x13,
                          0x10,
                          /*0x0f00*/ 0x00,
                          0x05,
                          0x15,
                          0x03,
                          0x07,
                          0x14,
                          0x09,
                          0x09,
                          0x13,
                          0x0b,
                          0x0d,
                          0x12,
                          0x0e,
                          0x0e,
                          0x16,
                          0x0c,
                          /*0x0f10*/ 0x0f,
                          0x15,
                          0x12,
                          0x13,
                          0x03,
                          0x02,
                          0x08,
                          0x02,
                          0x0c,
                          0x12,
                          0x04,
                          0x0c,
                          0x17,
                          0x07,
                          0x02,
                          0x07,
                          /*0x0f20*/ 0x07,
                          0x0a,
                          0x11,
                          0x0a,
                          0x02,
                          0x08,
                          0x0c,
                          0x07,
                          0x0d,
                          0x0c,
                          0x14,
                          0x18,
                          0x0e,
                          0x02,
                          0x08,
                          0x10,
                          /*0x0f30*/ 0x00,
                          0x02,
                          0x00,
                          0x07,
                          0x00,
                          0x0c,
                          0x00,
                          0x11,
                          0x05,
                          0x07,
                          0x05,
                          0x16,
                          0x09,
                          0x0b,
                          0x0d,
                          0x06,
                          /*0x0f40*/ 0x0b,
                          0x14,
                          0x0d,
                          0x17,
                          0x13,
                          0x0c,
                          0x13,
                          0x16,
                          0x04,
                          0x02,
                          0x05,
                          0x02,
                          0x06,
                          0x02,
                          0x0d,
                          0x02,
                          /*0x0f50*/ 0x0f,
                          0x02,
                          0x12,
                          0x02,
                          0x0a,
                          0x0c,
                          0x0f,
                          0x0c,
                          0x03,
                          0x16,
                          0x06,
                          0x16,
                          0x07,
                          0x16,
                          0x0f,
                          0x17,
                          /*0x0f60*/ 0x12,
                          0x16,
                          0x01,
                          0x07,
                          0x03,
                          0x0c,
                          0x01,
                          0x11,
                          0x0e,
                          0x0c,
                          0x0f,
                          0x07};
const uint8_t level6[] = {
    /* 0f6c */
    0x10,
    0x06,
    0x01,
    0x09,
    /*0x0f70*/ 0x04,
    0x01,
    0x00,
    0x02,
    0x01,
    0x06,
    0x08,
    0x01,
    0x0b,
    0x0e,
    0x06,
    0x00,
    0x01,
    0x06,
    0x03,
    0x05,
    /*0x0f80*/ 0x06,
    0x0c,
    0x0e,
    0x0b,
    0x02,
    0x07,
    0x0b,
    0x0c,
    0x11,
    0x0a,
    0x11,
    0x13,
    0x10,
    0x00,
    0x05,
    0x10,
    /*0x0f90*/ 0x10,
    0x13,
    0x15,
    0x06,
    0x06,
    0x15,
    0x08,
    0x08,
    0x14,
    0x0c,
    0x11,
    0x16,
    0x11,
    0x13,
    0x02,
    0x11,
    /*0x0fa0*/ 0x11,
    0x00,
    0x02,
    0x08,
    0x04,
    0x04,
    0x12,
    0x0e,
    0x07,
    0x0d,
    0x0e,
    0x13,
    0x17,
    0x11,
    0x02,
    0x0d,
    /*0x0fb0*/ 0x11,
    0x10,
    0x18,
    0x09,
    0x02,
    0x02,
    0x10,
    0x02,
    0x05,
    0x07,
    0x0c,
    0x07,
    0x0c,
    0x0c,
    0x10,
    0x0c,
    /*0x0fc0*/ 0x07,
    0x11,
    0x03,
    0x15,
    0x06,
    0x16,
    0x0c,
    0x15,
    0x13,
    0x11,
    0x13,
    0x17,
    0x0b,
    0x02,
    0x0c,
    0x02,
    /*0x0fd0*/ 0x0d,
    0x02,
    0x0e,
    0x02,
    0x00,
    0x11,
    0x02,
    0x11,
    0x03,
    0x11,
    0x07,
    0x0c,
    0x13,
    0x0b,
    0x01,
    0x11,
    /*0x0fe0*/ 0x01,
    0x02,
    0x12,
    0x11,
    0x0d,
    0x07,
    0x12,
    0x0b,
};
const uint8_t level7[] = {
    /* 0fe8 */
    0x17,
    0x07,
    0x01,
    0x04,
    0x03,
    0x15,
    0x0b,
    0x10,
    /*0x0ff0*/ 0x10,
    0x00,
    0x04,
    0x10,
    0x06,
    0x07,
    0x0b,
    0x00,
    0x02,
    0x06,
    0x01,
    0x03,
    0x04,
    0x00,
    0x01,
    0x01,
    /*0x1000*/ 0x03,
    0x04,
    0x02,
    0x05,
    0x06,
    0x01,
    0x07,
    0x08,
    0x02,
    0x09,
    0x09,
    0x03,
    0x09,
    0x09,
    0x03,
    0x0c,
    /*0x1010*/ 0x0c,
    0x08,
    0x05,
    0x08,
    0x09,
    0x05,
    0x05,
    0x0a,
    0x05,
    0x05,
    0x0b,
    0x05,
    0x05,
    0x0c,
    0x05,
    0x05,
    /*0x1020*/ 0x0b,
    0x08,
    0x08,
    0x0c,
    0x08,
    0x08,
    0x0f,
    0x0c,
    0x0f,
    0x0b,
    0x0a,
    0x0b,
    0x09,
    0x0e,
    0x10,
    0x02,
    /*0x1030*/ 0x0f,
    0x10,
    0x01,
    0x02,
    0x12,
    0x03,
    0x02,
    0x08,
    0x05,
    0x14,
    0x18,
    0x07,
    0x14,
    0x18,
    0x09,
    0x14,
    /*0x1040*/ 0x18,
    0x0d,
    0x10,
    0x17,
    0x0f,
    0x0a,
    0x11,
    0x12,
    0x06,
    0x17,
    0x08,
    0x17,
    0x0a,
    0x17,
    0x0f,
    0x16,
    /*0x1050*/ 0x07,
    0x11,
    0x02,
    0x03,
    0x07,
    0x09,
    0x0b,
    0x0c,
    0x10,
    0x0f,
    0x10,
    0x0a,
    0x0c,
    0x04,
    0x11,
    0x02,
    /*0x1060*/ 0x02,
    0x07,
    0x03,
    0x11,
    0x08,
    0x09,
    0x0c,
    0x16,
    0x0d,
    0x16,
    0x01,
    0x11,
    0x0e,
    0x0a,
    0x00,
    0x05,
    /*0x1070*/ 0x02,
    0x0c,
};
const uint8_t level8[] = {
    /* 1072 */
    0x0f,
    0x06,
    0x00,
    0x10,
    0x03,
    0x01,
    0x00,
    0x13,
    0x06,
    0x02,
    0x04,
    0x06,
    0x07,
    0x0d,
    /*0x1080*/ 0x06,
    0x10,
    0x12,
    0x0b,
    0x02,
    0x05,
    0x0b,
    0x08,
    0x0c,
    0x0b,
    0x0f,
    0x12,
    0x10,
    0x03,
    0x06,
    0x10,
    /*0x1090*/ 0x09,
    0x0b,
    0x10,
    0x0e,
    0x11,
    0x15,
    0x03,
    0x03,
    0x15,
    0x06,
    0x06,
    0x15,
    0x08,
    0x0c,
    0x15,
    0x0e,
    /*0x10a0*/ 0x0e,
    0x15,
    0x11,
    0x11,
    0x03,
    0x02,
    0x08,
    0x11,
    0x02,
    0x08,
    0x0a,
    0x07,
    0x0d,
    0x04,
    0x0c,
    0x12,
    /*0x10b0*/ 0x10,
    0x0c,
    0x12,
    0x0a,
    0x11,
    0x17,
    0x05,
    0x06,
    0x0f,
    0x06,
    0x06,
    0x0b,
    0x0e,
    0x0b,
    0x08,
    0x10,
    /*0x10c0*/ 0x0c,
    0x10,
    0x05,
    0x15,
    0x0f,
    0x15,
    0x07,
    0x15,
    0x0d,
    0x15,
    0x03,
    0x18,
    0x11,
    0x18,
    0x01,
    0x02,
    /*0x10d0*/ 0x02,
    0x02,
    0x04,
    0x02,
    0x05,
    0x02,
    0x06,
    0x02,
    0x08,
    0x02,
    0x09,
    0x02,
    0x0a,
    0x02,
    0x0b,
    0x02,
    /*0x10e0*/ 0x0c,
    0x02,
    0x0d,
    0x02,
    0x0e,
    0x02,
    0x0f,
    0x02,
    0x10,
    0x02,
    0x12,
    0x02,
    0x13,
    0x02,
    0x11,
    0x02,
    /*0x10f0*/ 0x0a,
    0x0c,
    0x0a,
    0x16,
    0x03,
    0x11,
    0x11,
    0x11,
    0x55,
    0x42,
    0x28,
    0x34,
    0x29,
    0x3a,
    0x20,
    0x45,
};

const uint8_t *const levels[8] = {&level1[0], &level2[0], &level3[0],
                                  &level4[0], &level5[0], &level6[0],
                                  &level7[0], &level8[0]};

extern const rect &SpriteEgg;
extern const rect &SpriteWall;
extern const rect &SpriteLadder;
extern const rect &SpriteGrain;
extern const rect &SpriteScore;
extern const rect &SpriteBlank;
extern const rect &SpritePlayer;
extern const rect &SpriteBonus;
extern const rect &SpriteLevel;
extern const rect &SpriteTime;
extern const rect &SpriteCage;
extern const rect &SpriteCageOpen;
extern const rect &SpriteDuck;
extern const rect &SpriteDuckStep;
extern const rect &SpriteDuckUp;
extern const rect &SpriteDuckUpStep;
extern const rect &SpriteDuckEat;
extern const rect &SpriteDuckEat2;
extern const rect &SpriteLift;

extern rect SpriteDigits[];
extern rect SpriteHenryWalks[];
extern rect SpriteHenryClimbs[];

Game::Game(size &screen) : screenSize(screen), currentLevel(0) {}

const point Game::tilePosition(int x, int y)
{
  return point(x * TILE_STRIDE, this->screenSize.h - ((y + 1) * TILE_STRIDE));
}

const point Game::tilePosition(point &tile)
{
  return this->tilePosition(tile.x, tile.y);
}

void Game::LoadLevel(int levelNumber)
{

  // Clear out the existing tiles
  bzero(&this->tiles[0], sizeof(this->tiles));
  this->hasBigDuck = levelNumber > 7;

  /* Get faster as we go up through the levels
  i = level_index >> 4;
  if (i > 8) {
      i = 8;
  }
  timer_ticks[0] = 9 - i;
  timer_ticks[1] = 0;
  timer_ticks[2] = 0;
  */

  // Data for the level
  const uint8_t *p = levels[levelNumber];
  int num_walls = *(p++);
  int num_ladders = *(p++);
  this->hasLift = bool(*p++);
  this->numGrain = *(p++);
  this->numDucks = *(p++);

  int x, y;
  while (num_walls--)
  {
    y = *(p++);       // row
    x = *(p++);       // first column
    int end = *(p++); // last column
    while (x <= end)
    {
      setTile(x, y, TILE_WALL);
      x++;
    }
  }

  while (num_ladders--)
  {
    x = *(p++);
    y = *(p++);
    int end = *(p++);
    while (y <= end)
    {
      addToTile(x, y, TILE_LADDER);
      y++;
    }
  }

  if (hasLift)
  {
    this->liftX = int(*(p++)) << 3;
  }

  int eggsLeft = 0;
  for (int i = 0; i < NUM_EGGS; i++)
  {
    x = *(p++);
    y = *(p++);
    setTile(x, y, (i << 4) | TILE_EGG);
    /*    if (player_data->egg[i] == 0) {
          Do_InitTile(x, y, (i << 4) | TILE_EGG);
          eggs_left++;
        }
    */
  }

  for (int i = 0; i < this->numGrain; i++)
  {
    x = *(p++);
    y = *(p++);
    setTile(x, y, (i << 4) | TILE_GRAIN);
    /*        if (player_data->grain[i] == 0) {
                Do_InitTile(x, y, (i << 4) | TILE_GRAIN);
            }
    */
  }

  for (int i = 0; i < MAX_DUCKS; i++)
  {
    ducks[i].tile.x = *(p++);
    ducks[i].tile.y = *(p++);
  }
  this->currentLevel = levelNumber;

  if (this->hasLift)
  {
    this->liftY[0] = 8;
    this->liftY[1] = 0x5a;
    currentLift = 0;
  }

  this->bigDuck.pos = point(4, 36);
  this->bigDuck.dPos = vec2(0, 0);
  this->bigDuck.frame = 0;
  this->bigDuck.dir = 0;
  if ((levelNumber >> 3) == 1)
  {
    this->numDucks = 0;
  }
  if (levelNumber >= 24)
  {
    this->numDucks = 5;
  }

  for (int i = 0; i < this->numDucks; i++)
  {
    Duck *pDuck = &this->ducks[i];
    pDuck->pos = this->tilePosition(pDuck->tile);
    pDuck->pos.y -= 12; // Ducks are tall.
    pDuck->state = BORED;
    pDuck->dir = DIR_R;
  }

  this->henry.tile = { 7, 3};
  this->henry.pos = this->tilePosition(this->henry.tile);
  this->henry.partial = { 7, 0 };
  this->henry.state = WALK;  // player_mode = PLAYER_WALK;
  this->henry.dir = DIR_R;
  // button_ack = 0x1f;
}

void Game::renderBackground(surface &fb)
{
  // WARNING MAGIC NUMBERS ABOUND
  // Score
  fb.sprite(SpriteScore, point(0, 0));
  fb.sprite(SpriteBlank, point(27, 0));

  // Player
  fb.sprite(SpritePlayer, point(0, 12));
  fb.sprite(SpriteDigits[this->currentPlayer + 1], point(27, 13));

  // Level
  fb.sprite(SpriteLevel, point(36, 12));
  int n = this->currentLevel + 1;
  fb.sprite(SpriteDigits[n % 10], point(69, 13));
  n /= 10;
  fb.sprite(SpriteDigits[n % 10], point(64, 13));
  if (n > 10)
  {
    fb.sprite(SpriteDigits[n % 10], point(59, 13));
  }

  // Bonus
  fb.sprite(SpriteBonus, point(78, 12));
  fb.sprite(SpriteDigits[0], point(117, 13));

  // Time
  fb.sprite(SpriteTime, point(126, 12));

  // Level deets
  for (int x = 0; x < COLUMNS; x++)
  {
    for (int y = 0; y < ROWS; y++)
    {
      const point &pos = this->tilePosition(x, y);

      point(x * TILE_STRIDE, fb.bounds.h - ((y + 1) * TILE_STRIDE));
      uint8_t tile = getTile(x, y);
      if (tile & TILE_WALL) {
        fb.sprite(SpriteWall, pos);
      }
      if (tile & TILE_LADDER) {
        fb.sprite(SpriteLadder, pos);
      }
      if (tile & TILE_EGG) {
        fb.sprite(SpriteEgg, pos);
      }
      if (tile & TILE_GRAIN) {
        fb.sprite(SpriteGrain, pos);
      }
    }
  }

  //  Cage
  const rect &cageSprite = this->hasBigDuck ? SpriteCageOpen : SpriteCage;
  fb.sprite(cageSprite, point(0, 20));
}

void Game::renderDucks(surface &fb) {

  for (int i = 0; i < this->numDucks; i++) {

    Duck &duck = this->ducks[i];

    point pos = duck.pos;
    int dir = duck.dir;
    sprite_transform flip = (dir==DIR_L) ? HORIZONTAL : NONE;
    rect sprite = SpriteDuck;

    switch (duck.state) {
      case BORED:
        if (dir & DIR_VERT) { // Going up or down
	        sprite = SpriteDuckUp;
        }
        break;  
      case STEP:
        if (dir & DIR_HORIZ) {
          sprite = SpriteDuckStep;
        } else {
	        sprite = SpriteDuckUpStep;
        }
        break;
      case EAT2:
      case EAT3:
      case EAT4:
        sprite = (duck.state == EAT3) ? SpriteDuckEat2 : SpriteDuckEat;
        if (dir == DIR_L) {
          pos.x -= 8; 
        }
        break;
      default:
        abort();
    }

    fb.sprite(sprite, pos, flip);
  }
}

void Game::renderHenry(surface &fb) {
    
    Henry& h = this->henry;
    sprite_transform flip = NONE;
    rect *sequence;
    int spriteIndex;


    if (h.dir == 0) { // Not going left or right
      sequence = SpriteHenryClimbs;
      spriteIndex = h.pos.y;
    } else {
      sequence = SpriteHenryWalks;
      spriteIndex = h.pos.x;
      if (h.dir == DIR_L) {
        flip = HORIZONTAL;
      }
    }

    spriteIndex = (spriteIndex >> 1) & 0x03; // Change animation every 2 pixels

    if (h.state != CLIMB) {
      if (h.speed.x == 0) {
        spriteIndex = 0;
      }
    } else if (h.speed.y == 0) {
      spriteIndex = 0;
    }
    fb.sprite(sequence[spriteIndex], h.pos, flip);
}

void Game::renderLifts(surface &fb) {
    if (this->hasLift) {
      fb.sprite(SpriteLift, point(this->liftX, this->liftY[0]));
      fb.sprite(SpriteLift, point(this->liftX, this->liftY[1]));
    }

}

void Game::Render(surface &fb) {
  this->renderBackground(fb);
  this->renderDucks(fb);
  this->renderHenry(fb);
  this->renderLifts(fb);
}