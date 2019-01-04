#include "deposit.hpp"
#include "resources_manager.hpp"

extern Resources_Manager resources_manager;

cDeposit::cDeposit(const sf::Vector2u& posOnGrid, unsigned int amount) {
    this->amount = (amount > MAX_AMOUNT ? MAX_AMOUNT : amount);

    sprite.setTexture(resources_manager.get_texture(21));

    adjustSprite();

    sprite.setPosition(posOnGrid.x * 32.0f + 16.0f, posOnGrid.y * 32.0f + 16.0f);
    sprite.setOrigin(sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height / 2.0f);
}
cDeposit::cDeposit(unsigned int gridX, unsigned int gridY, unsigned int amount)
    : cDeposit(sf::Vector2u(gridX, gridY), amount) {}

unsigned int cDeposit::dig(unsigned int amount) {
    if (this->amount < amount) {
        amount = this->amount;
    }
    this->amount -= amount;

    adjustSprite();

    return amount;
}

const sf::Sprite& cDeposit::get_sprite() {
    return sprite;
}

bool cDeposit::is_empty() const {
    return amount == 0;
}

void cDeposit::adjustSprite() {
    constexpr auto GRID_SIZE = 32;

    if (amount <= 300) {
        sprite.setTextureRect(sf::IntRect(0, GRID_SIZE * 2, GRID_SIZE, GRID_SIZE));
    } else if (amount <= 700) {
        sprite.setTextureRect(sf::IntRect(0, GRID_SIZE * 1, GRID_SIZE, GRID_SIZE));
    } else {
        sprite.setTextureRect(sf::IntRect(0, GRID_SIZE * 0, GRID_SIZE, GRID_SIZE));
    }
}

void cDeposit::display(sf::RenderWindow& window) const {
    window.draw(sprite);
}
