#ifndef FACTORY_HPP_INCLUDED
#define FACTORY_HPP_INCLUDED

#include "nationality.hpp"

enum FactoryType
{
    FACTORY_NONE = -1,
    FACTORY_INFANTRY = 0,
    FACTORY_TANK
};

class Factory
{
    Nationality m_nationality;//Which nationality can recruit it
    FactoryType m_factory_type;
    float m_base_hp;
    float m_actual_hp;
    unsigned int m_price;
    unsigned int m_creating_time;
    unsigned short m_team;

public:
    Factory();

    Nationality get_nationality() const;
    FactoryType get_factory_type() const;
    float get_hp() const;
    void add_hp(float hp);
    void subtract_hp(float hp);
    float get_max_hp() const;
    unsigned int get_price() const;
    unsigned int get_creating_time() const;
    unsigned short get_team() const;
    void set_team(unsigned short team);

protected:

    void set_nationality(const Nationality& nationality);
    void set_factory_type(const FactoryType& factory_type);
    void set_hp(float hp);
    void set_max_hp(float hp);
    void set_price(unsigned int price);
    void set_creating_time(unsigned int time);

public:
};

#endif // FACTORY_HPP_INCLUDED