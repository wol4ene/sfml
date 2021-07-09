#include "map_renderer.h"
#include <iostream>

MapRenderer::MapRenderer(const std::string& tile_atlas,
                         size_t num_layers)
    : _layers(num_layers)
{
    if (!_tile_atlas.loadFromFile(tile_atlas)) {
        std::cout << "Error\n";
    }    
}

void
MapRenderer::load(uint32_t layer_id,
                  uint32_t numRows,
                  uint32_t numCols,
                  uint32_t tile_height,
                  uint32_t tile_width,
                  uint32_t tileset_column_count,
                  std::vector<uint32_t> tile_ids)
{
    static bool show = false;
    _layers[layer_id].setPrimitiveType(sf::Quads);
    _layers[layer_id].resize(numCols * numRows * 4);
    uint32_t x = 0;

    /* Paint the layer left to right, top to bottom */
    for (uint32_t i = 0; i < numRows; ++i) {
        for (uint32_t j = 0; j < numCols; ++j) {
            int tileNumber = tile_ids[x] == 0 ? 0 : tile_ids[x]-1;
            x++;
            if (tileNumber != 0) {

                /* Get the X and Y index of the desired tile in the tile atlas */
                int tx = tileNumber % tileset_column_count;
                int ty = tileNumber / tileset_column_count;

                if (show) {
                    printf("i=%d, j=%d tileNumber: %d, quad %d, x_idx=%d y_idx=%d\n",
                            i, j, tileNumber, (i*numCols+j)*4,tx, ty);
                    printf("q0: x,y = %d, %d\n", (j+0) * tile_width, (i+0) * tile_height);
                    printf("q1: x,y = %d, %d\n", (j+1) * tile_width, (i+0) * tile_height);
                    printf("q2: x,y = %d, %d\n", (j+1) * tile_width, (i+1) * tile_height);
                    printf("q3: x,y = %d, %d\n", (j+0) * tile_width, (i+1) * tile_height);

                }

                /* Get the quad associated with this i,j */
                sf::Vertex *quad = &_layers[layer_id][(i * numCols + j) * 4];

                /* Set the quad's 4 vertices clockwise from top left.
                 * This defines the quad location on screen */
                quad[0].position = sf::Vector2f((j+0) * tile_width, (i+0) * tile_height);
                quad[1].position = sf::Vector2f((j+1) * tile_width, (i+0) * tile_height);
                quad[2].position = sf::Vector2f((j+1) * tile_width, (i+1) * tile_height);
                quad[3].position = sf::Vector2f((j+0) * tile_width, (i+1) * tile_height);

                /* Set the quad's texture clockwise from top left
                 * This defines contents of the quad, the tile to pull
                 * from the tileset/atlas */
                quad[0].texCoords = sf::Vector2f((tx+0) * tile_width, (ty+0) * tile_height);
                quad[1].texCoords = sf::Vector2f((tx+1) * tile_width, (ty+0) * tile_height);
                quad[2].texCoords = sf::Vector2f((tx+1) * tile_width, (ty+1) * tile_height);
                quad[3].texCoords = sf::Vector2f((tx+0) * tile_width, (ty+1) * tile_height);
            }
        }
    }
    show = false;
}

void
MapRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.texture = &_tile_atlas;
    for (const auto& layer : _layers) {
        target.draw(layer, states);
    }
}
