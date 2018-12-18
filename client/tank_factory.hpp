#ifndef TANK_FACTORY_HPP_INCLUDED
#define TANK_FACTORY_HPP_INCLUDED

#include <memory>
#include <SFML/Graphics.hpp>
#include "graphical_factory.hpp"
#include "tank.hpp"

class Tank_Factory : public Graphical_Factory
{
    std::unique_ptr<Tank> m_created_tank;
    sf::Clock m_creating_time_clock;
    bool m_is_creating;

public:
    Tank_Factory(const sf::Vector2f& pos);
    Tank_Factory(float x, float y);

    void start_creating(const TankType& unit_type);

    std::unique_ptr<Tank> get_tank();

    bool is_creating();

protected:
    unsigned int get_creating_time();
    unsigned int get_total_time();
};

#endif // TANK_FACTORY_HPP_INCLUDED
