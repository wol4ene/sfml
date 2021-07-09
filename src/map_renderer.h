#include <SFML/Graphics.hpp>
#pragma once

class MapRenderer : public sf::Drawable {

public:

    /* Load the given tileset/atlas as a texture, and prepare
     * a vector of sf::VertexArrays, one per layer */
    MapRenderer(const std::string& tile_atlas,
                size_t num_layers);

    void load(uint32_t layer_id,
              uint32_t numRows,
              uint32_t numCols,
              uint32_t tile_height,
              uint32_t tile_width,
              uint32_t tilesets_column_count,
              std::vector<uint32_t> tile_ids);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::vector<sf::VertexArray> _layers;
    sf::VertexArray _vertices;
    sf::Texture _tile_atlas;
};
