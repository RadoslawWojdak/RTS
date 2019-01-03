#ifndef INFANTRY_FACTORY_HPP_INCLUDED
#define INFANTRY_FACTORY_HPP_INCLUDED

#include <memory>
#include <SFML/Graphics.hpp>
#include "shopping_menu.hpp"
#include "graphical_factory.hpp"
#include "infantry.hpp"

class Infantry_Factory : public Graphical_Factory
{
    sf::RectangleShape finished_time_rect;
    sf::RectangleShape total_time_rect;
    std::unique_ptr<Infantry> m_created_infantry;
    sf::Clock m_creating_time_clock;
    bool m_is_creating;
    std::unique_ptr<cShoppingMenu> m_shopping_menu;

public:
    Infantry_Factory(const sf::RenderWindow& window, const sf::Vector2f& pos);
    Infantry_Factory(const sf::RenderWindow& window, float x, float y);

    void start_creating(const InfantryType& unit_type);

    std::unique_ptr<Infantry> get_infantry();

    bool is_creating() const;
    InfantryType get_shop_item_clicked(const sf::RenderWindow& window) const;

    void display(sf::RenderWindow& window) const;

protected:
    unsigned int get_creating_time();
    unsigned int get_total_time() const;
};

#endif // INFANTRY_FACTORY_HPP_INCLUDED
