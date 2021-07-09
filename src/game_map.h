#include "tiled_map_parser.h"
#include "map_renderer.h"
#include <SFML/Graphics.hpp>

#pragma once
class GameMap : public sf::Drawable {
public:
    GameMap(const std::string& map_json_file,
            const std::string& tile_atlas);

    void update();
    void dump_map_info();
    void dump_tile_layers();
    void dump_object_layers();
    void dump_tile_sets();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates stats) const override;

private:
    json_parser::TiledMapParser _map_parser;
    MapRenderer _map_renderer;
};
