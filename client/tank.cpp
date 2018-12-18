#include "tank.hpp"
#include "resources_manager.hpp"

extern Resources_Manager resources_manager;

Tank::Tank(const TankType& type, ushort team, const sf::Vector2f& pos)
    : Graphical_Unit(get_texture(type), pos)
{
    set_unit_type(UNIT_TANK);
    set_parameters(type);
    set_team(team);

    set_hp(get_max_hp());
}
Tank::Tank(const TankType& type, ushort team, float x, float y)
    : Tank(type, team, sf::Vector2f(x, y)) {}

void Tank::shot()
{
    if(get_abilities() == (get_abilities() | ABILITY_SHOOTING))
    {
        /*
        creates a bullet that must reach another unit
        */
    }
}

const sf::Texture& Tank::get_texture(const TankType& type)
{
    switch(type)
    {
    case TANK_A: return resources_manager.get_texture(1);
    case TANK_B: return resources_manager.get_texture(1);
    default:     return resources_manager.get_texture(1);
    }
}

void Tank::set_parameters(const TankType& type)
{
    switch(type)
    {
    case TANK_A:
    {
        set_strength(UNIT_INFANTRY, 10.0f);
        set_strength(UNIT_TANK, 50.0f);
        set_nationality(NATIONALITY_ALL);
        set_max_hp(150.0f);
        set_armor(0.2f);
        set_speed(3.2f);
        set_shot_frequency(0.65f);
        set_range(50.0f);
        set_abilities(ABILITY_SHOOTING | CRUSHING_UNITS | DEFENSE_AGAINST_CRUSHING);
        set_price(200u);
        set_creating_time(5'000u);
    }
    case TANK_B:
    {
        set_strength(UNIT_INFANTRY, 40.0f);
        set_strength(UNIT_TANK, 10.0f);
        set_nationality(NATIONALITY_ALL);
        set_max_hp(150.0f);
        set_armor(0.15f);
        set_speed(3.2f);
        set_shot_frequency(0.5f);
        set_range(50.0f);
        set_abilities(ABILITY_SHOOTING | AREA_DAMAGE | CRUSHING_UNITS | DEFENSE_AGAINST_CRUSHING);
        set_price(150u);
        set_creating_time(5'000u);
    }
    }
}
