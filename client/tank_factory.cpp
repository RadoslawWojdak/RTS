#include "tank_factory.hpp"
#include "resources_manager.hpp"

extern Resources_Manager resources_manager;

Tank_Factory::Tank_Factory(const sf::Vector2f& pos)
    : Graphical_Factory(resources_manager.get_texture(12), pos)
{

}
Tank_Factory::Tank_Factory(float x, float y)
    : Tank_Factory(sf::Vector2f(x, y))
{
    m_is_creating = false;
}

void Tank_Factory::start_creating(const TankType& unit_type)
{
    const auto TANK_POSITION = sf::Vector2f(get_sprite().getPosition().x,
                                            get_sprite().getPosition().y + get_sprite().getOrigin().y + 32);

    m_created_tank = std::make_unique<Tank>(unit_type, get_team(), TANK_POSITION);

    m_creating_time_clock = sf::Clock();
    m_is_creating = true;
}

unsigned int Tank_Factory::get_creating_time()
{
    return m_creating_time_clock.getElapsedTime().asMilliseconds();
}

unsigned int Tank_Factory::get_total_time()
{
    return m_created_tank->get_creating_time();
}

std::unique_ptr<Tank> Tank_Factory::get_tank()
{
    if (m_created_tank)
    {
        if (get_creating_time() >= m_created_tank->get_creating_time())
        {
            m_is_creating = false;
            return std::move(m_created_tank);
        }
    }
    return nullptr;
}

bool Tank_Factory::is_creating()
{
    return m_is_creating;
}
