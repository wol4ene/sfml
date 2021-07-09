#include "tiled_map_parser.h"
#include "tiled_nlohmann_converters.h"
#include <fstream>

using namespace json_parser;

TiledMapParser::TiledMapParser(const std::string& file)
{
    std::ifstream ifs{file};
    _json = nlohmann::json::parse(ifs);

    _map_info = _json.get<json_parser::map_info>();

    for (const auto& layer : _json.at("layers")) {
        if (layer.at("type") == "tilelayer") {
            _tile_layers.emplace_back(layer.get<json_parser::tile_layer>());
        }
    }

    for (const auto& layer : _json.at("layers")) {
        if (layer.at("type") == "objectgroup") {
            _object_layers.emplace_back(layer.get<json_parser::object_layer>());
        }
    }

    if (_json.contains("tilesets")) {
        for (const auto& tset : _json.at("tilesets")) {
            if (tset.contains("name")) {
                _tile_sets.emplace_back(tset.get<json_parser::tileset>());
            }
        }
    }
}

map_info
TiledMapParser::get_map_info() const {
    return _map_info;
}

std::vector<tile_layer>
TiledMapParser::get_tile_layers() const {
    return _tile_layers;
}

std::vector<object_layer>
TiledMapParser::get_object_layers() const {
    return _object_layers;
}

std::vector<tileset>
TiledMapParser::get_tile_sets() const {
    return _tile_sets;
}

