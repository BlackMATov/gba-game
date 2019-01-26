/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#pragma once

#include "base.hpp"

// .------------------------------.
// | mode | BG0 | BG1 | BG2 | BG3 |
// |------------------------------|
// |  0   | reg | reg | reg | reg |
// |  1   | reg | reg | aff |  -  |
// |  2   |  -  |  -  | aff | aff |
// `------------------------------`

namespace engine::core
{
    enum mode : u16 {
        mode_0 = 0x0000,
        mode_1 = 0x0001,
        mode_2 = 0x0002,
        mode_3 = 0x0003,
        mode_4 = 0x0004,
        mode_5 = 0x0005
    };

    enum layer : u16 {
        layer_bg0 = 0x0100,
        layer_bg1 = 0x0200,
        layer_bg2 = 0x0400,
        layer_bg3 = 0x0800,
        layer_obj = 0x1000
    };

    void initialize(mode mode, u16 layers) noexcept;

    void change_mode(mode mode) noexcept;
    void change_layers(u16 layers) noexcept;

    mode current_mode() noexcept;
    u16 current_layers() noexcept;
}
