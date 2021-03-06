// SPDX-License-Identifier: MPL-2.0

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#include "types.hpp"
#include "base.hpp"
#include "bits.hpp"
#include "input.hpp"

#define DISPCNT (reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0000UL))
#define DISPSTAT (reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0004UL))
#define VCOUNT (reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0006UL))
#define PALETTE (reinterpret_cast<volatile u16 *>(GBA_PALETTE_ADDR))
#define VRAM (reinterpret_cast<volatile u16 *>(GBA_VRAM_ADDR))

using isr_t = void (*)();
void master_isr();

#define IRQ_HANDLER (reinterpret_cast<isr_t *>(0x0300'7FFCUL))
#define IE (reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0200UL))
#define IME (reinterpret_cast<volatile u16 *>(GBA_IOREG_ADDR + 0x0208UL))

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 160

#define DISPLAY_MODE3 0x3UL
#define DISPLAY_MODE4 0x4UL
#define DISPLAY_SELECT_FRAME    bit(4)
#define DISPLAY_ENABLE_BG2      bit(10)

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
inline
void
vblank()
{
    // VBlankIntrWait
    asm("svc 0x05" ::: "r0", "r1");
}

static
void
vflip()
{
    *DISPCNT ^= DISPLAY_SELECT_FRAME;
}

int
main()
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

    *IRQ_HANDLER = master_isr;
    // Enable VBLANK interrupt
    *DISPSTAT |= 1 << 3;
    *IE = 1;
    // Enable interrupts
    *IME = 1;

    while (true) {
        vblank();
        key_poll();

        if (key_down(KEY_A))
            vflip();
    }
    return 0;
}
