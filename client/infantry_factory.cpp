#include "infantry_factory.hpp"
#include <vector>
#include "resources_manager.hpp"

extern Resources_Manager resources_manager;

Infantry_Factory::Infantry_Factory(const sf::RenderWindow& window, const sf::Vector2f& pos)
    : Graphical_Factory(resources_manager.get_texture(20), pos)
{
    set_creating_time(15'000u);
    set_price(1000);

    finished_time_rect = sf::RectangleShape(sf::Vector2f(16, 32));
    finished_time_rect.setOrigin(finished_time_rect.getGlobalBounds().width / 2, 0.0f);
    finished_time_rect.setPosition(pos.x, pos.y - get_sprite().getOrigin().y - finished_time_rect.getOrigin().y - 8);
    finished_time_rect.setFillColor(sf::Color(0, 255, 0, 64));

    total_time_rect = sf::RectangleShape(sf::Vector2f(16, 32));
    total_time_rect.setOrigin(finished_time_rect.getGlobalBounds().width / 2, 0.0f);
    total_time_rect.setPosition(pos.x, pos.y - get_sprite().getOrigin().y - finished_time_rect.getOrigin().y - 32 - 8); // Bar will filling from bottom
    total_time_rect.setFillColor(sf::Color(255, 255, 255, 64));

    std::vector<const sf::Texture*> shop_textures;
    shop_textures.push_back(&resources_manager.get_texture(17));
    shop_textures.push_back(&resources_manager.get_texture(18));
    shop_textures.push_back(&resources_manager.get_texture(19));
    m_shopping_menu = std::make_unique<cShoppingMenu>(window, resources_manager.get_texture(15), shop_textures);
}
Infantry_Factory::Infantry_Factory(const sf::RenderWindow& window, float x, float y)
    : Infantry_Factory(window, sf::Vector2f(x, y))
{
    m_is_creating = false;
}

void Infantry_Factory::start_creating(const InfantryType& unit_type)
{
    const auto INFANTRY_POSITION = sf::Vector2u(get_sprite().getPosition().x / 32,
                                                get_sprite().getPosition().y / 32 + 1);

    m_created_infantry = std::make_unique<Infantry>(unit_type, get_team(), INFANTRY_POSITION);

    m_creating_time_clock = sf::Clock();
    m_is_creating = true;
}

unsigned int Infantry_Factory::get_creating_time()
{
    const int DURATION = m_creating_time_clock.getElapsedTime().asMilliseconds();
    const float PERCENTAGE_OF_COMPLETION = static_cast<float>(DURATION) / get_total_time();

    finished_time_rect.setSize(sf::Vector2f(total_time_rect.getGlobalBounds().width,
                                            -total_time_rect.getGlobalBounds().height * PERCENTAGE_OF_COMPLETION));

    return DURATION;
}

unsigned int Infantry_Factory::get_total_time() const
{
    return m_created_infantry->get_creating_time();
}

std::unique_ptr<Infantry> Infantry_Factory::get_infantry()
{
    if (m_created_infantry)
    {
        if (get_creating_time() >= m_created_infantry->get_creating_time())
        {
            m_is_creating = false;
            return std::move(m_created_infantry);
        }
    }
    return nullptr;
}

bool Infantry_Factory::is_creating() const
{
    return m_is_creating;
}
InfantryType Infantry_Factory::get_shop_item_clicked(const sf::RenderWindow& window) const {
    return static_cast<InfantryType>(m_shopping_menu->getClickedItemId(window));
}

void Infantry_Factory::display(sf::RenderWindow& window) const
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
