#ifndef TANK_HPP_INCLUDED
#define TANK_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include "graphical_unit.hpp"

enum TankType
{
    TANK_A = 0,
    TANK_B
};

class Tank : public GraphicalUnit
{
public:
    Tank(const TankType& type, ushort team, const sf::Vector2f& pos);
    Tank(const TankType& type, ushort team, float x, float y);

    void shot();

protected:
    const sf::Texture& get_texture(const TankType& type);
    void set_parameters(const TankType& type);
};

#endif // TANK_HPP_INCLUDED