// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#include "input.hpp"
#include "base.hpp"

u16 input_prev = KEY_MASK;
u16 input_curr = KEY_MASK;

static auto KEYINPUT = reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0130);

void
key_poll()
{
    input_prev = input_curr;
    input_curr = ~(*KEYINPUT) & KEY_MASK;
}
