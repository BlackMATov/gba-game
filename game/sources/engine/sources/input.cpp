/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include "../headers/input.hpp"
#include "../headers/mem.hpp"

namespace
{
    using namespace engine;

    struct input_state_t {
        u16 prev_keys = 0;
        u16 curr_keys = 0;
    } s_input_state;
}

namespace engine::input
{
    void poll() noexcept {
        volatile u16& reg_key_input = *(mem::reg_ptr<u16>(0x0130));
        s_input_state.prev_keys = s_input_state.curr_keys;
        s_input_state.curr_keys = ~reg_key_input & 0x03FF;
    }

    bool is_pressed(key keys) noexcept {
        return s_input_state.curr_keys & keys;
    }

    bool is_released(key keys) noexcept {
        return ~s_input_state.curr_keys & keys;
    }

    bool is_just_pressed(key keys) noexcept {
        return (s_input_state.curr_keys & ~s_input_state.prev_keys) & keys;
    }

    bool is_just_released(key keys) noexcept {
        return (~s_input_state.curr_keys & s_input_state.prev_keys) & keys;
    }
}
