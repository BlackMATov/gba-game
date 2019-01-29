/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#pragma once

#include <vector>
#include <ostream>
#include <cstdint>
#include <cstddef>

namespace toolbox
{
    struct bitmap8p_t {
        std::size_t width = 0u;
        std::size_t height = 0u;

        using indices_t = std::vector<std::uint8_t>;
        indices_t indices;

        using palette_t = std::vector<std::uint16_t>;
        palette_t palette;
    };

    struct bitmap16b_t {
        std::size_t width = 0;
        std::size_t height = 0;

        using colors_t = std::vector<std::uint16_t>;
        colors_t colors;
    };

    bitmap8p_t load_bitmap8p(const char* filename, std::uint8_t min_alpha);
    bitmap16b_t load_bitmap16b(const char* filename, std::uint8_t min_alpha);
}

namespace toolbox
{
    namespace detail
    {
        class stream_flags_saver {
        public:
            stream_flags_saver() = delete;
            stream_flags_saver(const stream_flags_saver&) = delete;
            stream_flags_saver& operator=(const stream_flags_saver&) = delete;

            explicit stream_flags_saver(std::ios_base& s)
            : s_(s)
            , f_(s.flags()) {}

            ~stream_flags_saver() noexcept {
                s_.flags(f_);
            }
        private:
            std::ios_base& s_;
            std::ios_base::fmtflags f_;
        };
    }

    template < typename Iter, typename CharT, typename Traits >
    std::basic_ostream<CharT, Traits>& hex_data_to_stream(
        Iter first,
        Iter last,
        std::basic_ostream<CharT, Traits>& ost,
        const char* indent = "",
        std::size_t align = std::size_t(-1))
    {
        detail::stream_flags_saver stream_flags(ost);

        ost << indent;
        std::size_t count = 0;
        for ( auto iter = first; iter != last; ++iter ) {
            if ( iter != first ) {
                if ( !(count % align) ) {
                    ost << "," << std::endl << indent;
                } else {
                    ost << ", ";
                }
            }
            ++count;
            ost << std::hex << std::showbase
                << static_cast<std::uintmax_t>(*iter);
        }
        return ost;
    }

    template < typename Range, typename CharT, typename Traits >
    std::basic_ostream<CharT, Traits>& hex_data_to_stream(
        Range range,
        std::basic_ostream<CharT, Traits>& ost,
        const char* indent = "",
        std::size_t align = std::size_t(-1))
    {
        return hex_data_to_stream(
            std::begin(range),
            std::end(range),
            ost,
            indent,
            align);
    }
}
