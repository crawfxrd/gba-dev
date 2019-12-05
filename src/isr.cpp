// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#include "types.hpp"

#define BIOS_IF (reinterpret_cast<volatile u16 *>(0x0300'7FF8UL))
#define IF (reinterpret_cast<volatile u16 *>(0x0400'0202UL))

void
master_isr()
{
    // Acknowledge VBLANK interrupt
    *IF = 1;
    *BIOS_IF |= 1;
}
