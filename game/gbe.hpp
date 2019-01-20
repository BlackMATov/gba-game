/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include <cstdint>

namespace gbe
{
    using s8 = std::int8_t;
    using s16 = std::int16_t;
    using s32 = std::int32_t;

    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;

    static_assert(sizeof(s8) == 1, "s8 sizeof check failed");
    static_assert(sizeof(s16) == 2, "s16 sizeof check failed");
    static_assert(sizeof(s32) == 4, "s32 sizeof check failed");

    static_assert(sizeof(u8) == 1, "u8 sizeof check failed");
    static_assert(sizeof(u16) == 2, "u16 sizeof check failed");
    static_assert(sizeof(u32) == 4, "u32 sizeof check failed");
}

namespace gbe
{
    constexpr u16 make_rgb15(u32 r, u32 g, u32 b) noexcept {
        return static_cast<u16>(r | (g << 5) | (b << 10));
    }

    enum class color : u16 {
        red = make_rgb15(31, 0, 0),
        green = make_rgb15(0, 31, 0),
        blue = make_rgb15(0, 0, 31)
    };

    void initialize() noexcept;
}

namespace gbe::raw
{
    inline volatile u32* io32 = reinterpret_cast<u32*>(0x04000000);
    inline volatile u16* vram16 = reinterpret_cast<u16*>(0x06000000);
}

namespace gbe::gfx
{
    inline u32 screen_width = 240;
    inline u32 screen_height = 160;

    void m3_plot(u32 x, u32 y, u16 c) noexcept;
    void m3_plot(u32 x, u32 y, color c) noexcept;
}

namespace gbe::core
{
    enum modes : u32 {
        mode_0 = 0x0000,
        mode_1 = 0x0001,
        mode_2 = 0x0002,
        mode_3 = 0x0003,
        mode_4 = 0x0004,
        mode_5 = 0x0005
    };

    enum layers : u32 {
        layer_bg0 = 0x0100,
        layer_bg1 = 0x0200,
        layer_bg2 = 0x0400,
        layer_bg3 = 0x0800,
        layer_obj = 0x1000
    };

    void change_mode(u32 mode) noexcept;
    void change_layers(u32 layers) noexcept;
}
