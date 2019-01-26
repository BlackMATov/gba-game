/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include "engine/headers/all.hpp"
using namespace engine;

#include "data/zombie_0.png.data.hpp"
#include "data/zombie_1.png.data.hpp"

namespace
{
    struct game_state_t {
        u32 t = 0u;
        s32 x = gfx::screen_width_s / 2;
        s32 y = gfx::screen_height_s / 2;
    } s_game_state;
}

int main() noexcept
{
    core::initialize(core::mode_3, core::layer_bg2);

    while(true) {
        gfx::vsync();
        input::poll();

        {
            ++s_game_state.t;

            const u16* image_data = ((s_game_state.t >> 4) % 2)
                ? embedded_data::zombie_0
                : embedded_data::zombie_1;

            gfx::m3_image(
                s_game_state.x - (embedded_data::zombie_0_width >> 1),
                s_game_state.y - (embedded_data::zombie_0_height >> 1),
                image_data,
                embedded_data::zombie_0_width,
                embedded_data::zombie_0_height);
        }

        input::is_pressed(input::key_a | input::key_b);

        if ( input::is_pressed(input::key_a) ) {
            s_game_state.x += (math::rnd_u32(3) - 1);
            s_game_state.y += (math::rnd_u32(3) - 1);

            gfx::m3_plot(
                static_cast<s32>(math::rnd_u32(0u, gfx::screen_width)),
                static_cast<s32>(math::rnd_u32(0u, gfx::screen_height)),
                make_rgb15(math::rnd_u32(32), math::rnd_u32(32), math::rnd_u32(32)));
        }

        if ( input::is_pressed(input::key_b) ) {
            if ( input::is_just_pressed(input::key_left) ) {
                --s_game_state.x;
            }

            if ( input::is_just_pressed(input::key_right) ) {
                ++s_game_state.x;
            }

            if ( input::is_just_pressed(input::key_up) ) {
                --s_game_state.y;
            }

            if ( input::is_just_pressed(input::key_down) ) {
                ++s_game_state.y;
            }
        } else {
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
        }
    }
}
