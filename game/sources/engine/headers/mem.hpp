/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#pragma once

#include "base.hpp"

#define GBAE_DISPCNT_MODE_MASK    0x0007
#define GBAE_DISPCNT_MODE_SHIFT   0

#define GBAE_DISPCNT_LAYERS_MASK  0x1F00
#define GBAE_DISPCNT_LAYERS_SHIFT 8

#define GBAE_VCOUNT_MASK          0xFF
#define GBAE_VCOUNT_SHIFT         0

// .-----------------------------------------------------------------------------.
// | REG_DISPCNT @ 0400:0000h                                                    |
// |-----------------------------------------------------------------------------|
// | F  | E  | D  | C   | B   | A   | 9   | 8   | 7  | 6  | 5  | 4  | 3  | 2 1 0 |
// |-----------------------------------------------------------------------------|
// | OW | W1 | W0 | Obj | BG3 | BG2 | BG1 | BG0 | FB | OM | HB | PS | GB | Mode  |
// '-----------------------------------------------------------------------------'

// .-----------------------------------------------------------.
// | REG_DISPSTAT @ 0400:0004h                                 |
// |-----------------------------------------------------------|
// | F E D C B A 9 8 | 7 6 |  5  |  4  |  3  |  2  |  1  |  0  |
// |-----------------------------------------------------------|
// |       VcT       |  -  | VcI | HbI | VbI | VcS | HbS | VbS |
// '-----------------------------------------------------------'

// .-----------------------------------.
// | REG_VCOUNT @ 0400:0006h           |
// |-----------------------------------|
// | F E D C B A 9 8 | 7 6 5 4 3 2 1 0 |
// |-----------------------------------|
// |        -        |        Vc       |
// '-----------------------------------'

namespace engine::mem
{
    struct reg_dispcnt_t {
        u8 ow : 1;
        u8 w1 : 1;
        u8 w0 : 1;
        u8 obj : 1;
        u8 bg3 : 1;
        u8 bg2 : 1;
        u8 bg1 : 1;
        u8 bg0 : 1;
        u8 fb : 1;
        u8 om : 1;
        u8 hb : 1;
        u8 ps : 1;
        u8 gb : 1;
        u8 mode : 3;
    };

    static_assert(
        sizeof(reg_dispcnt_t) == sizeof(u16),
        "reg_dispcnt_t sizeof check failed");

    struct reg_dispstat_t {
        u8 vct : 8;
        u8 _empty0 : 2;
        u8 vci : 1;
        u8 hbi : 1;
        u8 vbi : 1;
        u8 vcs : 1;
        u8 hbs : 1;
        u8 vbs : 1;
    };

    static_assert(
        sizeof(reg_dispstat_t) == sizeof(u16),
        "reg_dispstat_t sizeof check failed");

    struct reg_vcount_t {
        u8 _empty0 : 8;
        u8 vc : 8;
    };

    static_assert(
        sizeof(reg_vcount_t) == sizeof(u16),
        "reg_vcount_t sizeof check failed");
}

namespace engine::mem
{
    template < typename T >
    inline volatile T* reg_ptr(std::size_t offset = 0u) noexcept {
        return reinterpret_cast<T*>(0x04000000 + offset);
    }

    template < typename T >
    inline volatile T* vram_ptr(std::size_t offset = 0u) noexcept {
        return reinterpret_cast<T*>(0x06000000 + offset);
    }

    inline volatile u16& reg_dispcnt_ref() noexcept {
        return *reg_ptr<u16>(0x0000);
    }

    inline volatile u16& reg_dispstat_ref() noexcept {
        return *reg_ptr<u16>(0x0004);
    }

    inline volatile u16& reg_vcount_ref() noexcept {
        return *reg_ptr<u16>(0x0006);
    }
}
