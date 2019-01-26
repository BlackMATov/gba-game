/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include "../headers/math.hpp"

namespace
{
    using namespace engine;

    struct math_state_t {
        u32 rnd_seed = 0u;
    } s_math_state;
}

namespace engine::math
{
    u32 rnd_seed() noexcept {
        return s_math_state.rnd_seed;
    }

    u32 rnd_seed(u32 s) noexcept {
        u32 last_seed = s_math_state.rnd_seed;
        s_math_state.rnd_seed = s;
        return last_seed;
    }

    u32 rnd_u32(u32 r) noexcept {
        return rnd_u32(0u, r);
    }

    u32 rnd_u32(u32 l, u32 r) noexcept {
        const u32 last_seed = rnd_seed(214013u * s_math_state.rnd_seed + 2531011u);
        return l + (last_seed ^ last_seed >> 15) % (r - l);
    }
}
