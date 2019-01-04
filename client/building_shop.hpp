#ifndef BUILDING_SHOP_HPP_INCLUDED
#define BUILDING_SHOP_HPP_INCLUDED

#include <memory>
#include "SFML/Graphics.hpp"
#include "graphical_factory.hpp"
#include "shopping_menu.hpp"

enum BuildingType
{
    BUILDING_NONE = -1,
    BUILDING_TANK_FACTORY = 0,
    BUILDING_INFANTRY_FACTORY
};

class cBuildingShop {

public:
    cBuildingShop(const sf::RenderWindow& window);

    void start_creating(const sf::RenderWindow& window, const BuildingType& unit_type);

    std::unique_ptr<Graphical_Factory> get_factory();

    bool is_creating() const;
    bool is_finished();
    
    BuildingType get_shop_item_clicked(const sf::RenderWindow& window) const;
    BuildingType get_current_building() const;
    int get_current_buidling_texture_id() const;

    void display(sf::RenderWindow& window);

protected:
    unsigned int get_creating_time();
    unsigned int get_total_time() const;

private:
    sf::RectangleShape finished_time_rect;
    sf::RectangleShape total_time_rect;
    std::unique_ptr<Graphical_Factory> m_created_factory;
    sf::Clock m_creating_time_clock;
    bool m_is_creating;
    std::unique_ptr<cShoppingMenu> m_shopping_menu;

    BuildingType m_current_building;
    int m_current_building_texture_id;
};

#endif // BUILDING_SHOP_HPP_INCLUDED
