#include "factory.hpp"

Factory::Factory()
{

}

Nationality Factory::get_nationality() const
{
    return m_nationality;
}

void Factory::set_nationality(const Nationality& nationality)
{
    m_nationality = nationality;
}

FactoryType Factory::get_factory_type() const
{
    return m_factory_type;
}

void Factory::set_factory_type(const FactoryType& factory_type)
{
    m_factory_type = factory_type;
}

float Factory::get_hp() const
{
    return m_actual_hp;
}

void Factory::set_hp(float hp)
{
    m_actual_hp = hp;
    if(m_actual_hp < 0.0f)
        m_actual_hp = 0.0f;
}

void Factory::add_hp(float hp)
{
    m_actual_hp += hp;
    if(m_actual_hp > m_base_hp)
        m_actual_hp = m_base_hp;
}

void Factory::subtract_hp(float hp)
{
    m_actual_hp -= hp;
    if(m_actual_hp < 0.0f)
        m_actual_hp = 0.0f;
}

float Factory::get_max_hp() const
{
    return m_base_hp;
}

void Factory::set_max_hp(float hp)
{
    m_base_hp = hp;
    if(m_base_hp < 0.0f)
        m_base_hp = 0.0f;
}

unsigned int Factory::get_price() const
{
    return m_price;
}

void Factory::set_price(unsigned int price)
{
    m_price = price;
}

unsigned int Factory::get_creating_time() const
{
    return m_creating_time;
}

void Factory::set_creating_time(unsigned int time)
{
    m_creating_time = time;
}

unsigned short Factory::get_team() const
{
    return m_team;
}

void Factory::set_team(unsigned short team)
{
    m_team = team;
}
