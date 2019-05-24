/* SPDX-License-Identifier: MPL-2.0 */

/*
 * Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
 */

#ifndef GBA_BASE_HPP_
#define GBA_BASE_HPP_

#include "types.hpp"

static constexpr u32 GBA_EWRAM_ADDR = 0x0200'0000;
static constexpr u32 GBA_IWRAM_ADDR = 0x0300'0000;
static constexpr u32 GBA_IOREG_ADDR = 0x0400'0000;
static constexpr u32 GBA_PALETTE_ADDR = 0x0500'0000;
static constexpr u32 GBA_VRAM_ADDR = 0x0600'0000;
static constexpr u32 GBA_OAM_ADDR = 0x0700'0000;
static constexpr u32 GBA_GAME_ROM_ADDR = 0x0800'0000;
static constexpr u32 GBA_GAME_SRAM_ADDR = 0x0E00'0000;

#endif /* GBA_BASE_HPP_ */
