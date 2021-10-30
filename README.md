importer and exporter for volumetric dataformat described at [http://paulbourke.net/dataformats/volumetric/](http://paulbourke.net/dataformats/volumetric/).

**Modified Part:**

the fifth line indicates the number of features for each cell, and the binary data type is always float (32 bits) in little endian.
$$\boldsymbol{C}^{i,j,k}=\left[c_{i,j,k}^{0}, c_{i,j,k}^{1}, c_{i,j,k}^{2},\dots,c_{i,j,k}^{N_c}\right]$$
the binary data is a **vector of floats** with a total lenght of $N_{x}\times N_{y}\times N_{z}\times N_{c}$.
$$\left[
    \boldsymbol{C}_{0,0,0}
    \boldsymbol{C}_{0,0,1},
    \dots,
    \boldsymbol{C}_{N_{x},N_{y},N_{z}}
\right]$$

## Example Code Snippts:

export to file:

```cpp
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
```

import from file:

```cpp
vxyz_t vol_data;
vol_data.load("vol_data.vxyz");
std::cout << vol_data.to_string() << std::endl;
// comment: volumentic data of grid_size 3x4x5, grid_size: 3x4x5, cell_size: 1x1x1, lower_corner: 0x0x0, num_features: 1
```
