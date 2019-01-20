/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include <cassert>

#include "gbe.hpp"
using namespace gbe;

namespace
{
    struct core_state_t {
        u32 mode = core::mode_3;
        u32 layers = core::layer_bg2;
    } s_core_state;

    inline volatile u32& s_reg_dispcnt = *(raw::io32 + 0x0000);
}

namespace gbe
{
    void initialize() noexcept {
        core::change_mode(s_core_state.mode);
        core::change_layers(s_core_state.layers);
    }
}

namespace gbe::gfx
{
    void m3_plot(u32 x, u32 y, u16 c) noexcept {
        assert(s_core_state.mode == core::mode_3);
        assert(x < screen_width && y < screen_height);
        raw::vram16[x * screen_width + y] = c;
    }

    void m3_plot(u32 x, u32 y, color c) noexcept {
        m3_plot(x, y, static_cast<u16>(c));
    }
}

namespace gbe::core
{
    void change_mode(u32 mode) noexcept {
        s_core_state.mode = mode;
        s_reg_dispcnt = mode | s_core_state.layers;
    }

    void change_layers(u32 layers) noexcept {
        s_core_state.layers = layers;
        s_reg_dispcnt = s_core_state.mode | layers;
    }
}
