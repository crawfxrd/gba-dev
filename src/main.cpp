// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#include "types.hpp"
#include "base.hpp"
#include "bits.hpp"

#define DISPCNT (reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0000UL))
#define VCOUNT (reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0006UL))
#define PALETTE (reinterpret_cast<volatile u16 *>(GBA_PALETTE_ADDR))
#define VRAM (reinterpret_cast<volatile u16 *>(GBA_VRAM_ADDR))

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 160

#define DISPLAY_MODE3 0x3UL
#define DISPLAY_MODE4 0x4UL
#define DISPLAY_SELECT_FRAME    bit(4)
#define DISPLAY_ENABLE_BG2      bit(10)

#define KEYINPUT (reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0130UL))

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

static u16 __key_prev;
static u16 __key_curr;

static
inline
u32
key_curr_state()
{
    return __key_curr;
}

static
inline
u32
key_prev_state()
{
    return __key_prev;
}

static
inline
void
key_poll()
{
    __key_prev = __key_curr;
    __key_curr = ~(*KEYINPUT) & KEY_MASK;
}

static
inline
u32
key_is_down(u32 key)
{
    return __key_curr & key;
}

static
inline
u32
key_is_up(u32 key)
{
    return ~__key_curr & key;
}

static
inline
u32
key_was_down(u32 key)
{
    return __key_prev & key;
}

static
inline
u32
key_was_up(u32 key)
{
    return ~__key_prev & key;
}

static
inline
u32
key_up(u32 key)
{
    //return key_was_down(key) & key_is_up(key);
    return (__key_prev & ~__key_curr) & key;
}

static
inline
u32
key_down(u32 key)
{
    //return key_was_up(key) & key_is_down(key);
    return (~__key_prev & __key_curr) & key;
}

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

static
void
vblank()
{
    while (*VCOUNT >= 160);
    while (*VCOUNT < 160);
}

static
void
vflip()
{
    *DISPCNT ^= DISPLAY_SELECT_FRAME;
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

    while (true) {
        vblank();
        key_poll();

        if (key_down(KEY_A))
            vflip();
    }
    return 0;
}
