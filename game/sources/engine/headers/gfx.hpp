/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#pragma once

#include "base.hpp"

// .------------------------------------.
// | subject  | length         | cycles |
// |------------------------------------|
// | pixel    | 1              | 4      |
// | HDraw    | 240px          | 960    |
// | HBlank   | 68px           | 272    |
// | scanline | Hdraw + Hbl    | 1232   |
// | VDraw    | 160 * scanline | 197120 |
// | VBlank   | 68 * scanline  | 83776  |
// | refresh  | VDraw + Vbl    | 280896 |
// `------------------------------------`

namespace engine::gfx
{
    inline u32 screen_width = 240u;
    inline u32 screen_height = 160u;

    void m3_plot(u32 x, u32 y, u16 c) noexcept;

    void vsync() noexcept;
    u32 vcount() noexcept;
}
