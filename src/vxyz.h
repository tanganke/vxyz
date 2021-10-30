#pragma once
#include <string>
#include <vector>

class vxyz_t
{
public:
    // header information
    std::string comment;
    size_t grid_size[3];
    float cell_size[3];
    float lower_corner[3];
    size_t num_features;

    // raw data
    std::vector<float> raw_data;

private:
    inline size_t get_raw_index(size_t i, size_t j, size_t k) const
    {
        return (i * grid_size[1] * grid_size[2] +
                j * grid_size[2] +
                k) *
               num_features;
    }

public:
    vxyz_t();
    vxyz_t(const char *filename);
    void load(const char *filename);
    void save(const char *filename);

    inline vxyz_t &set_comment(const char *comment_)
    {
        comment.assign(comment_);
        return *this;
    }

    inline vxyz_t &set_grid_size(size_t x, size_t y, size_t z)
    {
        grid_size[0] = x;
        grid_size[1] = y;
        grid_size[2] = z;
        return *this;
    }

    inline vxyz_t &set_cell_size(size_t x, size_t y, size_t z)
    {
        cell_size[0] = x;
        cell_size[1] = y;
        cell_size[2] = z;
        return *this;
    }

    inline vxyz_t &set_lower_corner(float x, float y, float z)
    {
        lower_corner[0] = x;
        lower_corner[1] = y;
        lower_corner[2] = z;
        return *this;
    }

    inline vxyz_t &set_num_features(size_t n)
    {
        num_features = n;
        return *this;
    }

    inline vxyz_t &clear()
    {
        raw_data = std::vector<float>(grid_size[0] * grid_size[1] * grid_size[2] * num_features);
        for (size_t i = 0; i < raw_data.size(); ++i)
        {
            raw_data[i] = 0;
        }
        return *this;
    }

    inline float &get(size_t i, size_t j, size_t k)
    {
        return raw_data[get_raw_index(i, j, k)];
    }

    inline const float &get(size_t i, size_t j, size_t k) const
    {
        return raw_data[get_raw_index(i, j, k)];
    }

    std::string to_string() const;
};
