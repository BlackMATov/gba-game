/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#pragma once

#include <cstdint>
#include <cstddef>
#include <cassert>

namespace engine
{
    using s8 = std::int8_t;
    using s16 = std::int16_t;
    using s32 = std::int32_t;

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;

    static_assert(sizeof(s8) == 1, "s8 sizeof check failed");
    static_assert(sizeof(s16) == 2, "s16 sizeof check failed");
    static_assert(sizeof(s32) == 4, "s32 sizeof check failed");

    static_assert(sizeof(u8) == 1, "u8 sizeof check failed");
    static_assert(sizeof(u16) == 2, "u16 sizeof check failed");
    static_assert(sizeof(u32) == 4, "u32 sizeof check failed");
}

namespace engine
{
    constexpr u16 make_rgb15(u32 r, u32 g, u32 b) noexcept {
        return static_cast<u16>(r | (g << 5) | (b << 10));
    }

    enum rgb15 : u16 {
        rgb15_black   = make_rgb15( 0,  0,  0),
        rgb15_white   = make_rgb15(31, 31, 31),
        rgb15_red     = make_rgb15(31,  0,  0),
        rgb15_green   = make_rgb15( 0, 31,  0),
        rgb15_blue    = make_rgb15( 0,  0, 31),
        rgb15_yellow  = make_rgb15(31, 31,  0),
        rgb15_magenta = make_rgb15(31,  0, 31),
        rgb15_cyan    = make_rgb15( 0, 31, 31)
    };
}
