#include "infantry.hpp"
#include "resources_manager.hpp"

extern Resources_Manager resources_manager;

Infantry::Infantry(const InfantryType& type, ushort team, const sf::Vector2f& pos)
    : Graphical_Unit(get_texture(type), pos)
{
    set_unit_type(UNIT_TANK);
    set_parameters(type);
    set_team(team);

    set_hp(get_max_hp());
}
Infantry::Infantry(const InfantryType& type, ushort team, float x, float y)
    : Infantry(type, team, sf::Vector2f(x, y)) {}

void Infantry::shot()
{
    if(get_abilities() == (get_abilities() | ABILITY_SHOOTING))
    {
        /*
        hits immediately
        */
    }
}

const sf::Texture& Infantry::get_texture(const InfantryType& type)
{
    switch(type)
    {
    case INFANTRY_A: return resources_manager.get_texture(17);
    case INFANTRY_B: return resources_manager.get_texture(18);
    case INFANTRY_C: return resources_manager.get_texture(19);
    default:         return resources_manager.get_texture(17);
    }
}

void Infantry::set_parameters(const InfantryType& type)
{
    switch(type)
    {
    case INFANTRY_A:
    {
        set_strength(UNIT_INFANTRY, 10.0f);
        set_strength(UNIT_TANK, 5.0f);
        set_nationality(NATIONALITY_ALL);
        set_max_hp(50.0f);
        set_armor(0.05f);
        set_speed(10.0f);
        set_shot_frequency(1.0f);
        set_range(20.0f);
        set_abilities(ABILITY_SHOOTING);
        set_price(30u);
        set_creating_time(0'500u);
    }
    case INFANTRY_B:
    {
        set_strength(UNIT_INFANTRY, 3.0f);
        set_strength(UNIT_TANK, 25.0f);
        set_nationality(NATIONALITY_ALL);
        set_max_hp(50.0f);
        set_armor(0.15f);
        set_speed(6.0f);
        set_shot_frequency(0.5f);
        set_range(20.0f);
        set_abilities(ABILITY_SHOOTING);
        set_price(50u);
        set_creating_time(1'000u);
    }
    case INFANTRY_C:
    {
        set_nationality(NATIONALITY_ALL);
        set_max_hp(50.0f);
        set_armor(0.10f);
        set_speed(12.0f);
        set_range(20.0f);
        set_abilities(CAPTURE_BUILDING);
        set_price(150u);
        set_creating_time(3'500u);
    }
    }
}
