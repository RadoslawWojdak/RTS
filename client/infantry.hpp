#ifndef INFANTRY_HPP_INCLUDED
#define INFANTRY_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include "graphical_unit.hpp"

enum InfantryType
{
    INFANTRY_NONE = -1,
    INFANTRY_A = 0,
    INFANTRY_B,
    INFANTRY_C
};

class Infantry : public Graphical_Unit
{
public:
    Infantry(const InfantryType& type, ushort team, const sf::Vector2f& pos);
    Infantry(const InfantryType& type, ushort team, float x, float y);

    void shot();

protected:
    const sf::Texture& get_texture(const InfantryType& type);
    void set_parameters(const InfantryType& type);
};

#endif // INFANTRY_HPP_INCLUDED
