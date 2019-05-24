/* SPDX-License-Identifier: MPL-2.0 */

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#ifndef GBA_BITS_HPP_
#define GBA_BITS_HPP_

#include "types.hpp"

static constexpr u32 BITS_PER_BYTE = 8;
static constexpr u32 BITS_PER_LONG = 32;

/*
 * Convert a bit offset to a value.
 */
static
constexpr
u32
bit(u32 nr)
{
    return 1U << nr;
}

/*
 * Create a contiguous bit mask.
 */
static
constexpr
u32
bitmask(u32 high, u32 low)
{
    return (~0U >> (BITS_PER_LONG - 1 - high)) & (~0U - (1 << low) + 1);
}

#endif /* GBA_BITS_HPP_ */
