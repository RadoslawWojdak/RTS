#ifndef TANK_HPP_INCLUDED
#define TANK_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include "graphical_unit.hpp"

enum TankType
{
    TANK_NONE = -1,
    TANK_A = 0,
    TANK_B,
    TANK_SCRAPER
};

class Tank : public Graphical_Unit
{
public:
    Tank(const TankType& type, ushort team, const sf::Vector2u& pos);
    Tank(const TankType& type, ushort team, uint x, uint y);

    void shot();

protected:
    const sf::Texture& get_texture(const TankType& type);
    void set_parameters(const TankType& type);
};

#endif // TANK_HPP_INCLUDED