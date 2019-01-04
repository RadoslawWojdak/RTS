#ifndef HOUSE_HPP_INCLUDED
#define HOUSE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "../common/factory.hpp"

class cHouse : public Factory {

public:
    cHouse(const sf::Vector2u& posOnGrid, unsigned short sizeId = 1);
    cHouse(unsigned int gridX, unsigned int gridY, unsigned short sizeId = 1);

    void display(sf::RenderWindow& window) const;

    unsigned short getPopulation() const;

private:
    sf::Sprite sprite;
    unsigned short population;
};

#endif // HOUSE_HPP_INCLUDED
