#ifndef UNIT_HPP_INCLUDED
#define UNIT_HPP_INCLUDED

#include <map>
#include "nationality.hpp"

enum UnitType
{
    UNIT_INFANTRY = 0,
    UNIT_TANK
};

enum Ability
{
    ABILITY_SHOOTING = 1,
    AREA_DAMAGE = 2,
    CAPTURE_BUILDING = 4,
    CAPTURE_UNITS = 8,
    CRUSHING_UNITS = 16,
    DEFENSE_AGAINST_CRUSHING = 32,
    HARVESTING = 64
};

class Unit
{
    std::map<UnitType, float> m_strength_against;
    Nationality m_nationality;//Which nationality can recruit it
    UnitType m_unit_type;
    float m_base_hp;
    float m_actual_hp;
    float m_armor;//0.00 - 1.00 (how much damage absorbs)
    float m_speed;//km/h
    float m_shot_frequency;//shots per second
    float m_range;//meters
    float m_target_x;
    float m_target_y;
    uint m_abilities;
    uint m_price;
    uint m_creating_time;//ms
    ushort m_team;
    bool m_has_target;

public:
    Unit();

    float get_strength(UnitType against) const;
    Nationality get_nationality() const;
    UnitType get_unit_type() const;
    float get_hp() const;
    void add_hp(float hp);
    void subtract_hp(float hp);
    float get_max_hp() const;
    float get_armor() const;
    float get_speed() const;
    float get_shot_frequency() const;
    float get_range() const;
    float get_target_x() const;
    float get_target_y() const;
    void set_target(float x, float y);
    void unset_target();
    bool has_target() const;
    uint get_abilities() const;
    uint get_price() const;
    uint get_creating_time() const;
    ushort get_team() const;
    void set_team(ushort team);

protected:

    void set_strength(const UnitType& against, float strength);
    void set_nationality(const Nationality& nationality);
    void set_unit_type(const UnitType& unit_type);
    void set_hp(float hp);
    void set_max_hp(float hp);
    void set_armor(float armor);
    void set_speed(float speed);
    void set_shot_frequency(float speed);
    void set_range(float range);
    void set_abilities(uint abilities);
    void clear_abilities();
    void add_abilitiy(const Ability& ability);
    void set_price(uint price);
    void set_creating_time(uint time);
};

#endif // TANK_HPP_INCLUDED