/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#pragma once

#include "base.hpp"

namespace engine::math
{
    template < typename T >
    inline T min(T l, T r) noexcept {
        return l < r ? l : r;
    }

    template < typename T >
    inline T max(T l, T r) noexcept {
        return l < r ? r : l;
    }

    template < typename T >
    inline T clamp(T v, T vmin, T vmax) noexcept {
        return min(max(v, vmin), vmax);
    }
}

namespace engine::math
{
    u32 rnd_seed() noexcept;
    u32 rnd_seed(u32 s) noexcept;

    // range: (0, r>
    u32 rnd_u32(u32 r) noexcept;

    // range: (l, r>
    u32 rnd_u32(u32 l, u32 r) noexcept;
}
