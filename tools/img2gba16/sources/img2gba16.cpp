/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/gba-game"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019 Matvey Cherevko
 ******************************************************************************/

#include <cstddef>
#include <cstdint>
#include <cassert>

#include <ios>
#include <memory>
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

namespace fs = boost::filesystem;
namespace po = boost::program_options;

namespace
{
    void print_success_message(std::string_view header) {
        std::cerr << "\033[32m" << header << "\033[m" << std::endl;
    }

    void print_failure_message(std::string_view header, std::string_view message) {
        std::cerr << "\033[31m" << header << "\033[m" << message << std::endl;
    }

    void print_help_message(po::options_description opts) {
        std::cout
            << "-= Simple bitmap converter to GBA embedded data =-" << std::endl
            << opts
            << "Supported bitmap formats:\n  - .png\n  - .tga\n  - .bmp" << std::endl;
    }

    using bitmap_data_uptr = std::unique_ptr<stbi_uc, decltype(&stbi_image_free)>;

    template < typename CharT, typename Traits >
    std::size_t bitmap_data_to_stream(
        std::uint32_t min_alpha,
        const bitmap_data_uptr& data,
        const std::size_t width,
        const std::size_t height,
        const std::size_t channels,
        std::basic_ostream<CharT, Traits>& ost)
    {
        assert(width > 0 && height > 0);
        assert(channels >= 1 && channels <= 4);
        boost::io::ios_flags_saver ost_flags(ost);

        ost << "namespace {" << std::endl
            << "    __attribute__((section(\".ewram\")))" << std::endl
            << "    const std::uint16_t EWRAM_raw_data[] = {" << std::endl;

        std::uint8_t* raw = data.get();
        for ( std::size_t y = 0; y < height; ++y ) {
            ost << "        ";
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

                std::uint16_t c = a >= min_alpha
                    ? static_cast<std::uint16_t>(
                        ((r >> 3) <<  0) |
                        ((g >> 3) <<  5) |
                        ((b >> 3) << 10))
                    : 0;

                ost << std::hex
                    << std::showbase
                    << c;

                if ( x < width - 1 || y < height - 1 ) {
                    ost << ", ";
                }
            }
            ost << std::endl;
        }

        ost << "    };" << std::endl;
        ost << "}" << std::endl;

        return width * height * sizeof(std::uint16_t);
    }

    void process_bitmap(const fs::path& path, std::uint32_t min_alpha) {
        std::cout << "... bitmap processing: " << path << std::endl;

        int width = 0, height = 0, channels = 0;
        stbi_uc* bitmap_data_raw = stbi_load(path.c_str(), &width, &height, &channels, 0);
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

        std::string bitmap_id = path.stem().string();

        fs::path header_data_path = path;
        header_data_path.concat(".data.hpp");

        fs::path source_data_path = path;
        source_data_path.concat(".data.cpp");

        std::ofstream header_data_ost(header_data_path.c_str());
        std::ofstream source_data_ost(source_data_path.c_str());

        if ( !header_data_ost || !source_data_ost ) {
            throw std::logic_error("failed to open output files");
        }

        {
            auto& ost = header_data_ost;
            ost << "#pragma once" << std::endl
                << std::endl
                << "#include <cstdint>" << std::endl
                << "#include <cstddef>" << std::endl
                << std::endl
                << "namespace embedded_data {" << std::endl
                << "    extern const std::uint16_t* " << bitmap_id.c_str() << ";" << std::endl
                << "    extern const std::size_t " << bitmap_id.c_str() << "_bytes;" << std::endl
                << "    extern const std::uint16_t " << bitmap_id.c_str() << "_width;" << std::endl
                << "    extern const std::uint16_t " << bitmap_id.c_str() << "_height;" << std::endl
                << "}" << std::endl;
        }

        {
            auto& ost = source_data_ost;
            ost << "#include " << header_data_path.filename() << "" << std::endl;

            ost << std::endl;
            std::size_t bitmap_bytes = bitmap_data_to_stream(
                min_alpha,
                bitmap_data,
                static_cast<std::size_t>(width),
                static_cast<std::size_t>(height),
                static_cast<std::size_t>(channels),
                ost);
            ost << std::endl;

            ost << "namespace embedded_data {" << std::endl
                << "    const std::uint16_t* " << bitmap_id.c_str() << " = EWRAM_raw_data;" << std::endl
                << "    const std::size_t " << bitmap_id.c_str() << "_bytes = " << bitmap_bytes << ";" << std::endl
                << "    const std::uint16_t " << bitmap_id.c_str() << "_width = " << width << ";" << std::endl
                << "    const std::uint16_t " << bitmap_id.c_str() << "_height = " << height << ";" << std::endl
                << "}" << std::endl;
        }

        print_success_message("OK.");
    }

    void process_bitmap_or_directory(const fs::path& path, bool recursive, std::uint32_t min_alpha) {
        const auto check_image_ext = [](const fs::path& p){
            const auto ext = p.extension();
            return ext == ".png"
                || ext == ".tga"
                || ext == ".bmp";
        };

        if ( fs::is_directory(path) ) {
            for ( fs::directory_iterator iter(path);
                iter != fs::directory_iterator();
                ++iter )
            {
                if ( fs::is_regular_file(*iter) && check_image_ext(*iter) ) {
                    process_bitmap(*iter, min_alpha);
                } else if ( fs::is_directory(*iter) && recursive ) {
                    process_bitmap_or_directory(*iter, recursive, min_alpha);
                }
            }
        } else {
            process_bitmap(path, min_alpha);
        }
    }
}

int main(int argc, char* argv[])
{
    po::options_description opts("Allowed options");
    opts.add_options()
        ("help,h", "show help")
        ("recursive,r", "process bitmaps directory recursively")
        ("input,i", po::value<std::string>(), "input bitmap or bitmaps directory")
        ("alpha,a", po::value<std::uint32_t>()
                        ->default_value(127)
                        ->implicit_value(127), "minimal alpha [0;255]");

    po::positional_options_description p_opts;
    p_opts.add("input", -1);

    try {
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv)
            .options(opts).positional(p_opts).run(), vm);
        po::notify(vm);

        if ( vm.count("help") || argc == 1 ) {
            print_help_message(opts);
        }

        if ( vm.count("input") ) {
            try {
                process_bitmap_or_directory(
                    vm["input"].as<std::string>(),
                    vm.count("recursive"),
                    vm["alpha"].as<std::uint32_t>());
            } catch (std::exception& e) {
                print_failure_message("Error: ", e.what());
                return 1;
            }
        }
    } catch (std::exception&) {
        print_help_message(opts);
        return 1;
    }

    return 0;
}
