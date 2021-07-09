#include "nlohmann_json.hpp"
#include "tiled_nlohmann_converters.h"
#include "map_data.h"
#pragma once

namespace json_parser {

class TiledMapParser {
public:
    explicit TiledMapParser(const std::string& file);

    map_info get_map_info() const;
    std::vector<tile_layer> get_tile_layers() const;
    std::vector<object_layer> get_object_layers() const;
    std::vector<tileset> get_tile_sets() const;

private:
    std::vector<tile_layer> _tile_layers;
    std::vector<object_layer> _object_layers;
    std::vector<tileset> _tile_sets;
    map_info _map_info;
    nlohmann::json _json;
};

}
