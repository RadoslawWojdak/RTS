#include "house.hpp"
#include "resources_manager.hpp"

extern Resources_Manager resources_manager;

cHouse::cHouse(const sf::Vector2u& posOnGrid, unsigned short sizeId) {
    set_price(750);
    set_creating_time(10'000);

    switch(sizeId) {
        case 1: {
            population = 5;
            sprite.setTexture(resources_manager.get_texture(23));
            break;
        }
    }

    sprite.setOrigin(sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height / 2.0f);
    sprite.setPosition(posOnGrid.x * 32, posOnGrid.y * 32);
}
cHouse::cHouse(unsigned int gridX, unsigned int gridY, unsigned short sizeId)
    : cHouse(sf::Vector2u(gridX, gridY), sizeId) {}

void cHouse::display(sf::RenderWindow& window) const {
    window.draw(sprite);
}

unsigned short cHouse::getPopulation() const {
    return population;
}
