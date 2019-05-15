// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#include <cstdint>

using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;

#define BIT(nr) (1UL << (nr))

#define GBA_EWRAM_ADDR      0x0200'0000UL
#define GBA_IWRAM_ADDR      0x0300'0000UL
#define GBA_IOREG_ADDR      0x0400'0000UL
#define GBA_PALETTE_ADDR    0x0500'0000UL
#define GBA_VRAM_ADDR       0x0600'0000UL
#define GBA_OAM_ADDR        0x0700'0000UL
#define GBA_GAME_ROM_ADDR   0x0800'0000UL
#define GBA_GAME_SRAM_ADDR  0x0E00'0000UL

#define DISPCNT (reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0000UL))
#define PALETTE (reinterpret_cast<volatile u16 *>(GBA_PALETTE_ADDR))
#define VRAM (reinterpret_cast<volatile u16 *>(GBA_VRAM_ADDR))

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 160

#define DISPLAY_MODE3 0x3UL
#define DISPLAY_MODE4 0x4UL
#define DISPLAY_ENABLE_BG2      BIT(10)

static
constexpr
u16
rgb15(unsigned int red, unsigned int green, unsigned int blue)
{
    return red | (green << 5) | (blue << 10);
}

static u16 palette[8] = {
    rgb15(0x00, 0x00, 0x00),
    rgb15(0x1F, 0x1F, 0x1F),
    rgb15(0x18, 0x19, 0x19),
    rgb15(0x0D, 0x10, 0x10),
    rgb15(0x0A, 0x0D, 0x0D),
};

static u16 copyright[32] = {
    0x0000, 0x0102, 0x0201, 0x0000,
    0x0100, 0x0000, 0x0000, 0x0001,
    0x0002, 0x0104, 0x0301, 0x0200,
    0x0001, 0x0001, 0x0000, 0x0100,
    0x0001, 0x0001, 0x0000, 0x0100,
    0x0002, 0x0104, 0x0301, 0x0200,
    0x0100, 0x0000, 0x0000, 0x0001,
    0x0000, 0x0102, 0x0201, 0x0000,
};

static
inline
void
display_control(u16 val)
{
    *DISPCNT = val;
}

int
main(void)
{
    for (int i = 0; i < 8; ++i)
        *(PALETTE + i) = palette[i];

    for (int i = 0; i < 32; i += 4) {
        VRAM[(i / 4) * 120 + 0] = copyright[i];
        VRAM[(i / 4) * 120 + 1] = copyright[i + 1];
        VRAM[(i / 4) * 120 + 2] = copyright[i + 2];
        VRAM[(i / 4) * 120 + 3] = copyright[i + 3];
    }

    display_control(DISPLAY_MODE4 | DISPLAY_ENABLE_BG2);

    while (true);
    return 0;
}
