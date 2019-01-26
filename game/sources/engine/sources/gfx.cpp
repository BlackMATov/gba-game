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
    void m3_plot(s32 x, s32 y, u16 c) noexcept {
        assert(core::current_mode() == core::mode_3);

        if ( x < 0 || y < 0 ) {
            return;
        }

        if ( x >= screen_width_s || y >= screen_height_s ) {
            return;
        }

        volatile u16* vram = mem::vram_ptr<u16>();
        *(vram + y * screen_width_s + x) = c;
    }

    void m3_image(s32 x, s32 y, const u16* rgb15, u16 w, u16 h) noexcept {
        assert(rgb15);
        assert(core::current_mode() == core::mode_3);

        if ( x < 0 && x + w <= 0 ) {
            return;
        }

        if ( y < 0 && y + h <= 0 ) {
            return;
        }

        if ( x > 0 && x >= screen_width_s ) {
            return;
        }

        if ( y > 0 && y >= screen_height_s ) {
            return;
        }

        s32 yy = 0;
        s32 hh = h;

        if ( y < 0 ) {
            yy += -y;
        }

        if ( y + hh > screen_height_s ) {
            hh = screen_height_s - y;
        }

        s32 xx = 0;
        s32 ww = w;

        if ( x < 0 ) {
            xx += -x;
        }

        if ( x + ww > screen_width_s ) {
            ww = screen_width_s - x;
        }

        u16* vram = mem::vram_unsafe_ptr<u16>();
        for ( s32 i = yy; i < hh; ++i ) {
            u16* vram_line = vram + (i + y) * screen_width_s + (x + xx);
            const u16* rgb15_line = rgb15 + (i * w) + xx;
            mem::memcpy16(vram_line, rgb15_line, static_cast<std::size_t>(ww - xx));
        }
    }

    void vsync() noexcept {
        while(vcount() >= 160) {} // wait till VDraw
        while(vcount() < 160) {}  // wait till VBlank
    }

    u32 vcount() noexcept {
        return mem::reg_vcount_ref() & GBAE_VCOUNT_MASK;
    }
}
