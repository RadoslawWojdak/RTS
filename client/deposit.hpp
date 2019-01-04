#ifndef DEPOSIT_HPP
#define DEPOSIT_HPP

#include "SFML/Graphics.hpp"

class cDeposit {

public:
    cDeposit(const sf::Vector2u& posOnGrid, unsigned int amount = 700);
    cDeposit(unsigned int gridX, unsigned int gridY, unsigned int amount = 700);

    unsigned int dig(unsigned int amount = 100);

    void display(sf::RenderWindow& window) const;

    const sf::Sprite& get_sprite();
    bool is_empty() const;

private:
    static constexpr auto MAX_AMOUNT = 1200;

    void adjustSprite();

    sf::Sprite sprite;

    unsigned int amount;
};

#endif // DEPOSIT_HPP
