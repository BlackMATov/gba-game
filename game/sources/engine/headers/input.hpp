/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#pragma once

#include "base.hpp"

namespace engine::input
{
    enum key : u16 {
        key_a      = 0x0001,
        key_b      = 0x0002,
        key_select = 0x0004,
        key_start  = 0x0008,
        key_right  = 0x0010,
        key_left   = 0x0020,
        key_up     = 0x0040,
        key_down   = 0x0080,
        key_r      = 0x0100,
        key_l      = 0x0200
    };

    void poll() noexcept;

    bool is_pressed(u16 keys) noexcept;
    bool is_released(u16 keys) noexcept;

    bool is_just_pressed(u16 keys) noexcept;
    bool is_just_released(u16 keys) noexcept;
}
