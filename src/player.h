#include <SFML/Graphics.hpp>
#pragma once

class Player : public sf::Drawable {
public:
    Player(const sf::Texture& texture,
           int grid_size,
           float velocity) : 
        _animation_row {0},
        _animation_col {0},
        _grid_size {grid_size},
        _velocity {velocity},
        _character {texture, {0,0,grid_size,grid_size}} {}

    void update(const sf::Time& delta_time);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    int _animation_row;
    int _animation_col;
    int _grid_size;
    float _velocity;
    sf::Sprite _character;
};
