#include <iostream>
#include <vector>
#pragma once

namespace json_parser {
struct property {
    std::string name;
    std::string type;
    uint32_t uval;
    std::string sval;
    bool bval;
};

struct tile_layer {
    std::string name;
    uint32_t id;
    uint32_t num_tiles_x;  // col count, width
    uint32_t num_tiles_y;  // row count, height
    std::vector<uint32_t> tile_ids;
    std::vector<property> properties;
};

struct object {
    std::string name;
    std::string type;
    uint32_t id;
    uint32_t height_pixels;
    uint32_t width_pixels;
    uint32_t top_left_x;  //pixel
    uint32_t top_left_y;  //pixel  
    std::vector<property> properties;
};

struct object_layer {
    std::string name;
    uint32_t id;
    std::vector<object> objects;
};

struct tileset {
    std::string name;
    uint32_t num_tiles_x;  // col count, width;
    uint32_t firstgid;
    uint32_t imageheight_pixels;
    uint32_t imagewidth_pixels;
    uint32_t margin;
    uint32_t spacing;
    uint32_t tilecount;
    uint32_t tileheight;
    uint32_t tilewidth;
};

struct map_info {
    uint32_t num_tiles_x; // col count, width
    uint32_t num_tiles_y; // row count, height
    uint32_t tile_height_pixels;
    uint32_t tile_width_pixels;
};

}

