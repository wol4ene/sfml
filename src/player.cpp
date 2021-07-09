#include "player.h"

void
Player::update(const sf::Time& delta_time)
{
    bool moved = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _character.move(0, -(_velocity * delta_time.asSeconds()));
        _animation_row = 0;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _character.move(-(_velocity * delta_time.asSeconds()), 0);
        _animation_row = 1;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _character.move(0, _velocity * delta_time.asSeconds());
        _animation_row = 2;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _character.move(_velocity * delta_time.asSeconds(), 0);
        _animation_row = 3;
        moved = true;
    }

    if (moved) {
        _animation_col = ((_animation_col +1) % 8);
        _character.setTextureRect({(_animation_col + 1) * _grid_size, /*+1 since 0th is idle */
                                 _animation_row * _grid_size,
                                 _grid_size,
                                 _grid_size});
    } else {
        _character.setTextureRect({0,
                                 _animation_row * _grid_size,
                                 _grid_size,
                                 _grid_size});
    }
}

sf::Vector2f
Player::get_position() const
{
    return _character.getPosition();
}

void
Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_character, states);
}
