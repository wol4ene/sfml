#include "map_data.h"
#include "nlohmann_json.hpp"
#pragma once

namespace json_parser {

void from_json(const nlohmann::json &j, map_info &m);
void from_json(const nlohmann::json &j, property& m);
void from_json(const nlohmann::json &j, tile_layer& m);
void from_json(const nlohmann::json &j, object& m);
void from_json(const nlohmann::json &j, object_layer& m);
void from_json(const nlohmann::json &j, tileset& m);

}
