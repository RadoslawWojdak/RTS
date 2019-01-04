#include "tank_factory.hpp"
#include <vector>
#include "resources_manager.hpp"

extern Resources_Manager resources_manager;

Tank_Factory::Tank_Factory(const sf::RenderWindow& window, const sf::Vector2f& pos)
    : Graphical_Factory(resources_manager.get_texture(12), pos)
{
    set_creating_time(45'000u);
    set_price(3000);

    finished_time_rect = sf::RectangleShape(sf::Vector2f(16, 32));
    finished_time_rect.setOrigin(finished_time_rect.getGlobalBounds().width / 2, 0.0f);
    finished_time_rect.setPosition(pos.x, pos.y - get_sprite().getOrigin().y - finished_time_rect.getOrigin().y - 8);
    finished_time_rect.setFillColor(sf::Color(0, 255, 0, 64));

    total_time_rect = sf::RectangleShape(sf::Vector2f(16, 32));
    total_time_rect.setOrigin(finished_time_rect.getGlobalBounds().width / 2, 0.0f);
    total_time_rect.setPosition(pos.x, pos.y - get_sprite().getOrigin().y - finished_time_rect.getOrigin().y - 32 - 8); // Bar will filling from bottom
    total_time_rect.setFillColor(sf::Color(255, 255, 255, 64));

    std::vector<const sf::Texture*> shop_textures;
    shop_textures.push_back(&resources_manager.get_texture(1));
    shop_textures.push_back(&resources_manager.get_texture(16));
    m_shopping_menu = std::make_unique<cShoppingMenu>(window, resources_manager.get_texture(15), shop_textures);
}
Tank_Factory::Tank_Factory(const sf::RenderWindow& window, float x, float y)
    : Tank_Factory(window, sf::Vector2f(x, y))
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
    const int DURATION = m_creating_time_clock.getElapsedTime().asMilliseconds();
    const float PERCENTAGE_OF_COMPLETION = static_cast<float>(DURATION) / get_total_time();

    finished_time_rect.setSize(sf::Vector2f(total_time_rect.getGlobalBounds().width,
                                            -total_time_rect.getGlobalBounds().height * PERCENTAGE_OF_COMPLETION));

    return DURATION;
}

unsigned int Tank_Factory::get_total_time() const
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

bool Tank_Factory::is_creating() const
{
    return m_is_creating;
}

TankType Tank_Factory::get_shop_item_clicked(const sf::RenderWindow& window) const {
    return static_cast<TankType>(m_shopping_menu->getClickedItemId(window));
}

void Tank_Factory::display(sf::RenderWindow& window) const
{
    Graphical_Factory::display(window);

    if (is_creating())
    {
        window.draw(total_time_rect);
        window.draw(finished_time_rect);
    }

    if (is_marked()) {
        m_shopping_menu->display(window);
    }
}
