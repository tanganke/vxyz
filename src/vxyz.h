#pragma once
#include <string>
#include <vector>

/**
 * @brief This is the class to import and export volumetric data, the data format is described as http://paulbourke.net/dataformats/volumetric/.
 * @details 
 * **Header**
 * 
 * > The header consists of a number of lines (5) separated by linefeed characters, ASCII Hex "0a". The header lines are described as follows:
 * > 1. The first line consists of a comment, the comment can be as long as need be as long as it doesn't contain a linefeed.
 * > 2. The second line consists of three integers giving the size of the volume grid in the three directions, from now on referred here as x, y, z. These dimensions must be positive, they may be 1 but not 0.
 * > 3. The third line consists of three floating point numbers indicating the size of the cells in each direction. This gives support of non cubic cells, of course this is only interpreted by the display or analysis software. The size of a cell must be greater than 0.
 * > 4. The fourth line consists of three floating point numbers giving the real world coordinates of the lower corner of the volumetric dataset. The upper corner can be calculated given the number of cells and the cell size. Similarly the real world coordinates of any cell can be computed.
 * > 5. (*modified*) the fifth line indicates the number of features for each cell, and the binary data type is always float (32 bits) in little endian.
 * 
 * **Binary Data Block**
 */
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
    /** default constructor */
    vxyz_t();
    /** load volumetric data from file `filename` */
    vxyz_t(const char *filename);

    /** load volumetric data from file `filename` */
    void load(const char *filename);
    /** save volumetric data to file `filename` */
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
