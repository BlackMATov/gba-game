#include "gbe.hpp"
using namespace gbe;

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
}

int main() noexcept
{
    core::initialize();

    while(true) {
        gfx::m3_plot(
            rnd_u32(gfx::screen_width),
            rnd_u32(gfx::screen_height),
            make_rgb15(rnd_u32(32u), rnd_u32(32u), rnd_u32(32u)));
    }
}
