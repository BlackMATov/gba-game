/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include "../headers/gfx.hpp"

#include "../headers/mem.hpp"
#include "../headers/core.hpp"

namespace engine::gfx
{
    void m3_plot(u32 x, u32 y, u16 c) noexcept {
        assert(core::current_mode() == core::mode_3);
        assert(x < screen_width && y < screen_height);
        mem::vram_ptr<u16>()[y * screen_width + x] = c;
    }

    void vsync() noexcept {
        while(vcount() >= 160) {} // wait till VDraw
        while(vcount() < 160) {}  // wait till VBlank
    }

    u32 vcount() noexcept {
        return mem::reg_vcount_ref() & GBAE_VCOUNT_MASK;
    }
}
