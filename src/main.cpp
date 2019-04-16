// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#include <cstdint>

#define GBA_REGISTER_BASE 0x0400'0000UL
#define DISPCNT ((uint32_t *)(GBA_REGISTER_BASE + 0x0000UL))
#define VRAM ((uint16_t *)0x0600'0000UL)

using color_t = uint16_t;

static
constexpr
color_t
rgb15(unsigned int red, unsigned int green, unsigned int blue)
{
    return red | (green << 5) | (blue << 10);
}

int
main(void)
{
    *DISPCNT = 0x0403;

    VRAM[104 + (80 * 240)] = rgb15(0x1F, 0, 0);
    VRAM[120 + (80 * 240)] = rgb15(0, 0x1F, 0);
    VRAM[136 + (80 * 240)] = rgb15(0, 0, 0x1F);

    while (1);
    return 0;
}
