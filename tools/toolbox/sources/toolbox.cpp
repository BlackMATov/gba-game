/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include <toolbox/toolbox.hpp>


#include <set>
#include <string>
#include <cassert>
#include <algorithm>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "3rdparty/stb/stb_image.h"

namespace
{
    using namespace toolbox;
    using bitmap_data_uptr = std::unique_ptr<stbi_uc, decltype(&stbi_image_free)>;

    bitmap16b_t convert_raw_bitmap_to_bitmap16b(
        std::uint8_t min_alpha,
        const bitmap_data_uptr& data,
        std::size_t width,
        std::size_t height,
        std::size_t channels)
    {
        assert(data);
        assert(width > 0 && height > 0);
        assert(channels >= 1 && channels <= 4);

        bitmap16b_t bitmap16;
        bitmap16.width = width;
        bitmap16.height = height;

        const std::uint8_t* raw = data.get();
        bitmap16.colors.reserve(width * height);

        for ( std::size_t y = 0; y < height; ++y ) {
            for ( std::size_t x = 0; x < width; ++x ) {
                std::uint8_t r = 0, g = 0, b = 0, a = 0;
                std::size_t i = y * width * channels + x * channels;
                switch ( channels ) {
                    case 1:
                        r = raw[i + 0];
                        g = raw[i + 0];
                        b = raw[i + 0];
                        a = 255u;
                        break;
                    case 2:
                        r = raw[i + 0];
                        g = raw[i + 0];
                        b = raw[i + 0];
                        a = raw[i + 1];
                        break;
                    case 3:
                        r = raw[i + 0];
                        g = raw[i + 1];
                        b = raw[i + 2];
                        a = 255u;
                        break;
                    case 4:
                        r = raw[i + 0];
                        g = raw[i + 1];
                        b = raw[i + 2];
                        a = raw[i + 3];
                        break;
                    default:
                        throw std::logic_error("internal error");
                }
                const std::uint16_t c = a >= min_alpha
                    ? static_cast<std::uint16_t>(
                        ((r >> 3) <<  0) |
                        ((g >> 3) <<  5) |
                        ((b >> 3) << 10))
                    : 0;
                bitmap16.colors.push_back(c);
            }
        }

        return bitmap16;
    }

    bitmap8p_t convert_bitmap16b_to_bitmap8p(const bitmap16b_t& bitmap16) {
        std::set<std::uint16_t> palette_set(
            bitmap16.colors.begin(),
            bitmap16.colors.end());

        if ( palette_set.size() > 256 ) {
            throw std::logic_error(
                "palette size overflow: " +
                std::to_string(palette_set.size()));
        }

        std::vector<std::uint16_t> palette_vec;
        palette_vec.reserve(palette_set.size());
        palette_vec.assign(palette_set.begin(), palette_set.end());

        std::vector<std::uint8_t> indices_vec;
        indices_vec.reserve(palette_vec.size());

        for ( std::uint16_t c : bitmap16.colors ) {
            const auto iter = std::lower_bound(
                palette_vec.begin(), palette_vec.end(), c);
            if ( iter == palette_vec.end() || *iter != c ) {
                throw std::logic_error("internal error");
            }
            auto index = std::distance(palette_vec.begin(), iter);
            if ( index < 0 || index > 255 ) {
                throw std::logic_error("internal error");
            }
            indices_vec.push_back(static_cast<uint8_t>(index));
        }

        bitmap8p_t bitmap8;
        bitmap8.width = bitmap16.width;
        bitmap8.height = bitmap16.height;
        bitmap8.indices = std::move(indices_vec);
        bitmap8.palette = std::move(palette_vec);
        return bitmap8;
    }
}

namespace toolbox
{
    bitmap8p_t load_bitmap8p(const char* filename, std::uint8_t min_alpha) {
        return convert_bitmap16b_to_bitmap8p(
            load_bitmap16b(filename, min_alpha));
    }

    bitmap16b_t load_bitmap16b(const char* filename, std::uint8_t min_alpha) {
        int width = 0, height = 0, channels = 0;
        stbi_uc* bitmap_data_raw = stbi_load(filename, &width, &height, &channels, 0);
        if ( !bitmap_data_raw ) {
            throw std::logic_error(stbi_failure_reason());
        }

        bitmap_data_uptr bitmap_data(bitmap_data_raw, &stbi_image_free);

        if ( width < 1 || height < 1 ) {
            throw std::logic_error("unsupported bitmap size");
        }

        if ( channels < 1 || channels > 4 ) {
            throw std::logic_error("unsupported bitmap format");
        }

        return convert_raw_bitmap_to_bitmap16b(
            min_alpha,
            bitmap_data,
            static_cast<std::size_t>(width),
            static_cast<std::size_t>(height),
            static_cast<std::size_t>(channels));
    }
}
