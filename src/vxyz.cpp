#include "vxyz.h"
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <fstream>
#include <iostream>
#include <functional>
#include <algorithm>
#include <bit>
#include <memory>
#include <sstream>

vxyz_t::vxyz_t()
    : grid_size{}, cell_size{}, lower_corner{}, num_features{}
{
}

vxyz_t::vxyz_t(const char *filename)
    : vxyz_t()
{
    load(filename);
}

void vxyz_t::load(const char *filename)
{
    std::ifstream fs{filename, std::ios_base::binary};
    if (!fs.is_open())
    {
        spdlog::error("failed to open file {}", filename);
        return;
    }

    auto get_line_sstream = [](std::ifstream &fs) -> std::istringstream
    {
        std::string line;
        std::getline(fs, line);
        return std::istringstream(line);
    };

    std::getline(fs, comment);
    get_line_sstream(fs) >> grid_size[0] >> grid_size[1] >> grid_size[2];
    get_line_sstream(fs) >> cell_size[0] >> cell_size[1] >> cell_size[2];
    get_line_sstream(fs) >> lower_corner[0] >> lower_corner[1] >> lower_corner[2];
    get_line_sstream(fs) >> num_features;
    raw_data = std::vector<float>(grid_size[0] * grid_size[1] * grid_size[2] * num_features);
    fs.read((char *)raw_data.data(), raw_data.size() * sizeof(float));
}

void vxyz_t::save(const char *filename)
{
    std::ofstream fs{filename, std::ios_base::binary};
    fs << comment << '\n';
    fs << fmt::format("{}\t{}\t{}\n",
                      grid_size[0],
                      grid_size[1],
                      grid_size[2]);
    fs << fmt::format("{}\t{}\t{}\n",
                      cell_size[0],
                      cell_size[1],
                      cell_size[2]);
    fs << fmt::format("{}\t{}\t{}\n",
                      lower_corner[0],
                      lower_corner[1],
                      lower_corner[2]);
    fs << fmt::format("{}\n", num_features);
    if (std::endian::native == std::endian::little)
        fs.write((const char *)raw_data.data(), raw_data.size() * sizeof(float));
    else
    {
        char *buf = new char[raw_data.size() * sizeof(float)];
        for (int i = 0; i < raw_data.size(); i++)
        {
            char *f = (char *)&raw_data[i];
            buf[4 * i] = f[3];
            buf[4 * i + 1] = f[2];
            buf[4 * i + 2] = f[1];
            buf[4 * i + 3] = f[0];
        }
        fs.write(const_cast<const char *>(buf), raw_data.size() * sizeof(float));
        delete[] buf;
    }
}

std::string vxyz_t::to_string() const
{
    return fmt::format("comment: {}, grid_size: {}x{}x{}, cell_size: {}x{}x{}, lower_corner: {}x{}x{}, num_features: {}",
                       comment,
                       grid_size[0], grid_size[1], grid_size[2],
                       cell_size[0], cell_size[1], cell_size[2],
                       lower_corner[0], lower_corner[1], lower_corner[2],
                       num_features);
}