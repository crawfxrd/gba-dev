/* SPDX-License-Identifier: MPL-2.0 */

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#ifndef GBA_INPUT_HPP_
#define GBA_INPUT_HPP_

#include "types.hpp"
#include "bits.hpp"

extern u16 input_prev;
extern u16 input_curr;

#define KEY_A       bit(0)
#define KEY_B       bit(1)
#define KEY_SELECT  bit(2)
#define KEY_START   bit(3)
#define KEY_RIGHT   bit(4)
#define KEY_LEFT    bit(5)
#define KEY_UP      bit(6)
#define KEY_DOWN    bit(7)
#define KEY_R       bit(8)
#define KEY_L       bit(9)
#define KEY_MASK    bitmask(9,0)

void key_poll();

static
inline
u32
key_curr_state()
{
    return input_curr;
}

static
inline
u32
key_prev_state()
{
    return input_prev;
}

static
inline
u32
key_is_down(u32 key)
{
    return input_curr & key;
}

static
inline
u32
key_is_up(u32 key)
{
    return ~input_curr & key;
}

static
inline
u32
key_was_down(u32 key)
{
    return input_prev & key;
}

static
inline
u32
key_was_up(u32 key)
{
    return ~input_prev & key;
}

static
inline
u32
key_up(u32 key)
{
    return key_was_down(key) & key_is_up(key);
}

static
inline
u32
key_down(u32 key)
{
    return key_was_up(key) & key_is_down(key);
}

#endif /* GBA_INPUT_HPP_ */
