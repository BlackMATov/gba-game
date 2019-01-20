#include "gbe.hpp"

int main()
{
    gbe::initialize();

    gbe::gfx::m3_plot(10, 10, gbe::color::red);
    gbe::gfx::m3_plot(20, 10, gbe::color::green);
    gbe::gfx::m3_plot(10, 20, gbe::color::blue);

    while(true) {
    }

    return 0;
}
