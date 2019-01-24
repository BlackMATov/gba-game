/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include "../headers/core.hpp"

#include "../headers/mem.hpp"

namespace
{
    using namespace engine;
}

namespace engine::core
{
    void initialize(mode mode, layer layers) noexcept {
        volatile u16& dispcnt = mem::reg_dispcnt_ref();
        dispcnt = mode | layers;
    }

    void change_mode(mode mode) noexcept {
        volatile u16& dispcnt = mem::reg_dispcnt_ref();
        dispcnt = (dispcnt & ~GBAE_DISPCNT_MODE_MASK) | mode;
    }

    void change_layers(layer layers) noexcept {
        volatile u16& dispcnt = mem::reg_dispcnt_ref();
        dispcnt = (dispcnt & ~GBAE_DISPCNT_LAYERS_MASK) | layers;
    }

    mode current_mode() noexcept {
        return static_cast<mode>(
            mem::reg_dispcnt_ref() & GBAE_DISPCNT_MODE_MASK);
    }

    layer current_layers() noexcept {
        return static_cast<layer>(
            mem::reg_dispcnt_ref() & GBAE_DISPCNT_LAYERS_MASK);
    }
}
