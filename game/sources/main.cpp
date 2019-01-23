/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include "engine/engine.hpp"
using namespace engine;

namespace
{
    u32 s_rnd_u32_seed = 0;

    // range: (l, r>
    u32 rnd_u32(u32 l, u32 r) noexcept {
        s_rnd_u32_seed = 214013u * s_rnd_u32_seed + 2531011u;
        return l + (s_rnd_u32_seed ^ s_rnd_u32_seed >> 15) % (r - l);
    }

    // range: (0, r>
    u32 rnd_u32(u32 r) noexcept {
        return rnd_u32(0u, r);
    }

    struct game_state_t {
        u32 x = 0u;
        u32 y = 0u;
    } s_game_state;
}

int main() noexcept
{
    core::initialize();

    while(true) {
        input::poll();

        if ( input::is_pressed(input::key_left) ) {
            --s_game_state.x;
        }

        if ( input::is_pressed(input::key_right) ) {
            ++s_game_state.x;
        }

        if ( input::is_pressed(input::key_up) ) {
            --s_game_state.y;
        }

        if ( input::is_pressed(input::key_down) ) {
            ++s_game_state.y;
        }

        gfx::m3_plot(
            s_game_state.x,
            s_game_state.y,
            make_rgb15(rnd_u32(32u), rnd_u32(32u), rnd_u32(32u)));

        gfx::vsync();
    }
}
