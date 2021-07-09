#include "tiled_nlohmann_converters.h"

namespace json_parser {

void from_json(const nlohmann::json &j, map_info& m)
{
    j.at("height").get_to(m.num_tiles_y);
    j.at("width").get_to(m.num_tiles_x);
    j.at("tileheight").get_to(m.tile_height_pixels);
    j.at("tilewidth").get_to(m.tile_width_pixels);
}

void from_json(const nlohmann::json &j, property& m)
{
    j.at("name").get_to(m.name);
    j.at("type").get_to(m.type);

    if (j.at("type") == "bool") {
        j.at("value").get_to(m.bval);
    }
    if (j.at("type") == "string") {
        j.at("value").get_to(m.sval);
    }
    if (j.at("type") == "int") {
        j.at("value").get_to(m.uval);
    }
}

void from_json(const nlohmann::json &j, tile_layer& m)
{
    j.at("name").get_to(m.name);
    j.at("id").get_to(m.id);
    j.at("width").get_to(m.num_tiles_x);
    j.at("height").get_to(m.num_tiles_y);
    j.at("data").get_to(m.tile_ids);
    if (j.contains("properties")) {
        j.at("properties").get_to(m.properties);
    }
}

void from_json(const nlohmann::json &j, object& m)
{
    j.at("name").get_to(m.name);
    j.at("type").get_to(m.type);
    j.at("id").get_to(m.id);
    j.at("height").get_to(m.height_pixels);
    j.at("width").get_to(m.width_pixels);
    j.at("x").get_to(m.top_left_x);
    j.at("y").get_to(m.top_left_y);
    if (j.contains("properties")) {
        j.at("properties").get_to(m.properties);
    }
}

void from_json(const nlohmann::json &j, object_layer& m)
{
    j.at("name").get_to(m.name);
    j.at("id").get_to(m.id);
    if (j.contains("objects")) {
        j.at("objects").get_to(m.objects);
    }
}

void from_json(const nlohmann::json &j, tileset& m)
{
    j.at("name").get_to(m.name);
    j.at("columns").get_to(m.num_tiles_x);
    j.at("firstgid").get_to(m.firstgid);
    j.at("imageheight").get_to(m.imageheight_pixels);
    j.at("imagewidth").get_to(m.imagewidth_pixels);
    j.at("margin").get_to(m.margin);
    j.at("spacing").get_to(m.spacing);
    j.at("tilecount").get_to(m.tilecount);
    j.at("tileheight").get_to(m.tileheight);
    j.at("tilewidth").get_to(m.tilewidth);
}

} // namespace
