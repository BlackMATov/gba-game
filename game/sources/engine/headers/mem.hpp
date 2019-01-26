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
#define GBAE_INPUT_MASK           0x03FF

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

// .-----------------------------------------.
// |  Register   | length |     address      |
// |-----------------------------------------|
// | REG_BGxCNT  |    2   | 0400:0008h + 2·x |
// | REG_BGxHOFS |    2   | 0400:0010h + 4·x |
// | REG_BGxVOFS |    2   | 0400:0012h + 4·x |
// '-----------------------------------------'

// .---------------------------------------------------.
// | REG_BGxCNT @ 0400:0008 + 2x                       |
// |---------------------------------------------------|
// | F E | D  | C B A 9 8 | 7  |  6  | 5 4 | 3 2 | 1 0 |
// |---------------------------------------------------|
// | Sz  | Wr |    SBB    | CM | Mos |  -  | CBB | Pr  |
// '---------------------------------------------------'

// regular bg sizes
// .---------------------------------------------.
// | Sz-flag |    define    | (tiles) | (pixels) |
// |---------------------------------------------|
// |   00    | BG_REG_32x32 |  32x32  | 256x256  |
// |   01    | BG_REG_64x32 |  64x32  | 512x256  |
// |   10    | BG_REG_32x64 |  32x64  | 256x512  |
// |   11    | BG_REG_64x64 |  64x64  | 512x512  |
// '---------------------------------------------'

// affine bg sizes
// .-------------------------------------------------.
// | Sz-flag |     define     | (tiles)  |  (pixels) |
// |-------------------------------------------------|
// |   00    | BG_AFF_16x16   |  16x16   | 128x128   |
// |   01    | BG_AFF_32x32   |  32x32   | 256x256   |
// |   10    | BG_AFF_64x64   |  64x64   | 512x512   |
// |   11    | BG_AFF_128x128 |  128x128 | 1024x1024 |
// '-------------------------------------------------'

// .-------------------------------------------------------------------------.
// | REG_KEYINPUT (REG_P1) @ 0400:0130h                                      |
// |-------------------------------------------------------------------------|
// | F E D C B A | 9 | 8 |  7   | 6  |  5   |   4   |   3   |   2    | 1 | 0 |
// |-------------------------------------------------------------------------|
// |      -      | L | R | down | up | left | right | start | select | B | A |
// '-------------------------------------------------------------------------'

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

    struct reg_bgcnt_t {
        u8 sz : 2;
        u8 wr : 1;
        u8 sbb : 5;
        u8 cm : 1;
        u8 mos : 1;
        u8 _empty0 : 2;
        u8 cbb : 2;
        u8 pr : 2;
    };

    static_assert(
        sizeof(reg_bgcnt_t) == sizeof(u16),
        "reg_bgcnt_t sizeof check failed");
}

namespace engine::mem
{
    template < typename T >
    inline volatile T* io_ptr(std::size_t offset = 0u) noexcept {
        return reinterpret_cast<T*>(0x04000000 + offset);
    }

    template < typename T >
    inline T* io_unsafe_ptr(std::size_t offset = 0u) noexcept {
        return reinterpret_cast<T*>(0x04000000 + offset);
    }

    template < typename T >
    inline volatile T* vram_ptr(std::size_t offset = 0u) noexcept {
        return reinterpret_cast<T*>(0x06000000 + offset);
    }

    template < typename T >
    inline T* vram_unsafe_ptr(std::size_t offset = 0u) noexcept {
        return reinterpret_cast<T*>(0x06000000 + offset);
    }

    inline volatile u16& reg_dispcnt_ref() noexcept {
        return *io_ptr<u16>(0x0000);
    }

    inline volatile u16& reg_dispstat_ref() noexcept {
        return *io_ptr<u16>(0x0004);
    }

    inline volatile u16& reg_vcount_ref() noexcept {
        return *io_ptr<u16>(0x0006);
    }

    inline volatile u16& reg_bgcnt_ref(std::size_t n) noexcept {
        assert(n < 4);
        return *io_ptr<u16>(0x0008 + n * 0x0002);
    }

    inline void reg_bg_hofs(std::size_t n, u16 ofs) noexcept {
        assert(n < 4);
        *io_ptr<u16>(0x0010 + n * 0x0004) = ofs;
    }

    inline void reg_bg_vofs(std::size_t n, u16 ofs) noexcept {
        assert(n < 4);
        *io_ptr<u16>(0x0012 + n * 0x0004) = ofs;
    }

    inline volatile u16& reg_input_ref() noexcept {
        return *io_ptr<u16>(0x0130);
    }
}

namespace engine::mem
{
    inline void memcpy16(u16* dst, const u16* src, std::size_t hwcount) noexcept {
        while ( hwcount-- ) {
            *dst++ = *src++;
        }
    }

    inline void memcpy32(u32* dst, const u32* src, std::size_t wcount) noexcept {
        while ( wcount-- ) {
            *dst++ = *src++;
        }
    }
}
