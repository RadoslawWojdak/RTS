#include "unit.hpp"

Unit::Unit()
{
    m_strength_against.emplace(UNIT_INFANTRY, 0.0f);
    m_strength_against.emplace(UNIT_TANK, 0.0f);

    unset_target();
}

float Unit::get_strength(UnitType against) const
{
    return m_strength_against.at(against);
}

void Unit::set_strength(const UnitType& against, float strength)
{
    m_strength_against.at(against) = strength;
    if(m_strength_against.at(against) < 0.0f)
        m_strength_against.at(against) = 0.0f;
}

Nationality Unit::get_nationality() const
{
    return m_nationality;
}

void Unit::set_nationality(const Nationality& nationality)
{
    m_nationality = nationality;
}

UnitType Unit::get_unit_type() const
{
    return m_unit_type;
}

void Unit::set_unit_type(const UnitType& unit_type)
{
    m_unit_type = unit_type;
}

float Unit::get_hp() const
{
    return m_actual_hp;
}

void Unit::set_hp(float hp)
{
    m_actual_hp = hp;
    if(m_actual_hp < 0.0f)
        m_actual_hp = 0.0f;
}

void Unit::add_hp(float hp)
{
    m_actual_hp += hp;
    if(m_actual_hp > m_base_hp)
        m_actual_hp = m_base_hp;
}

void Unit::subtract_hp(float hp)
{
    m_actual_hp -= hp;
    if(m_actual_hp < 0.0f)
        m_actual_hp = 0.0f;
}

float Unit::get_max_hp() const
{
    return m_base_hp;
}

void Unit::set_max_hp(float hp)
{
    m_base_hp = hp;
    if(m_base_hp < 0.0f)
        m_base_hp = 0.0f;
}

float Unit::get_armor() const
{
    return m_armor;
}

void Unit::set_armor(float armor)
{
    m_armor = armor;
    if(m_armor < 0.0f)
        m_armor = 0.0f;
    else if(m_armor > 1.0f)
        m_armor = 1.0f;
}

float Unit::get_speed() const
{
    return m_speed;
}

void Unit::set_speed(float speed)
{
    m_speed = speed;
    if(m_speed < 0.0f)
        m_speed = 0.0f;
}

float Unit::get_shot_frequency() const
{
    return m_shot_frequency;
}

void Unit::set_shot_frequency(float speed)
{
    m_shot_frequency = speed;
    if(m_shot_frequency < 0.0f)
        m_shot_frequency = 0.0f;
}

float Unit::get_range() const
{
    return m_range;
}

void Unit::set_range(float range)
{
    m_range = range;
    if(m_range < 0.0f)
        m_range = 0.0f;
}

float Unit::get_target_x() const
{
    return m_target_x;
}

float Unit::get_target_y() const
{
    return m_target_y;
}

void Unit::set_target(float x, float y)
{
    m_target_x = x;
    if(m_target_x < 0.0f)
        m_target_x = 0.0f;

    m_target_y = y;
    if(m_target_y < 0.0f)
        m_target_y = 0.0f;

    m_has_target = true;
}

void Unit::unset_target()
{
    m_has_target = false;
}

bool Unit::has_target() const
{
    return m_has_target;
}

uint Unit::get_abilities() const
{
    return m_abilities;
}

void Unit::set_abilities(uint abilities)
{
    m_abilities = abilities;
}

void Unit::clear_abilities()
{
    m_abilities = 0;
}

void Unit::add_abilitiy(const Ability& ability)
{
    m_abilities |= ability;
}

uint Unit::get_price() const
{
    return m_price;
}

void Unit::set_price(uint price)
{
    m_price = price;
}

uint Unit::get_creating_time() const
{
    return m_creating_time;
}

void Unit::set_creating_time(uint time)
{
    m_creating_time = time;
}

ushort Unit::get_team() const
{
    return m_team;
}

void Unit::set_team(ushort team)
{
    m_team = team;
}
