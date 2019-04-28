// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#include <cstdint>

#define GBA_REGISTER_BASE 0x0400'0000UL
#define DISPCNT (reinterpret_cast<volatile uint32_t *>(GBA_REGISTER_BASE + 0x0000UL))
#define VRAM (reinterpret_cast<volatile uint16_t *>(0x0600'0000UL))

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 160
#define DISPLAY_M3 0x3UL
#define DISPLAY_BG2 (1UL << 10)

static
inline
void
display_control(unsigned int mode)
{
    *DISPCNT = mode;
}

static
constexpr
uint16_t
rgb15(unsigned int red, unsigned int green, unsigned int blue)
{
    return red | (green << 5) | (blue << 10);
}

static
inline
void
m3_set_pixel(unsigned int x, unsigned int y, uint16_t color)
{
    VRAM[y * DISPLAY_WIDTH + x] = color;
}

int
main(void)
{
    display_control(DISPLAY_M3 | DISPLAY_BG2);

    for (int y = 0; y < DISPLAY_HEIGHT; ++y) {
        for (int x = 0; x < DISPLAY_WIDTH; ++x) {
            const uint32_t r = x & 0x1F;
            const uint32_t g = y & 0x1F;
            const uint32_t b = (x * y) & 0x1F;

            m3_set_pixel(x, y, rgb15(r, g, b));
        }
    }

    while (1);
    return 0;
}
