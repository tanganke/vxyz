#include "catch2/catch.hpp"
#include "vxyz.h"
#include <iostream>

TEST_CASE("export")
{
    vxyz_t vol_data;
    vol_data.set_comment("volumentic data of grid_size 3x4x5")
        .set_grid_size(3, 4, 5)
        .set_cell_size(1, 1, 1)
        .set_lower_corner(0, 0, 0)
        .set_num_features(1)
        .clear();
    for (int i = 0; i < vol_data.raw_data.size(); i++)
    {
        vol_data.raw_data[i] = i;
    }
    vol_data.save("vol_data.vxyz");
}

TEST_CASE("import")
{
    vxyz_t vol_data;
    vol_data.load("vol_data.vxyz");
    std::cout << vol_data.to_string() << std::endl;
}