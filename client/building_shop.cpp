#include "building_shop.hpp"
#include <vector>
#include "resources_manager.hpp"
#include "infantry_factory.hpp"
#include "tank_factory.hpp"
#include "house.hpp"

extern Resources_Manager resources_manager;

cBuildingShop::cBuildingShop(const sf::RenderWindow& window) {
    const auto RECT_SIZE  = resources_manager.get_texture(14).getSize();
    const auto RECT_POS_Y = window.getSize().y - RECT_SIZE.y / 2.0f;

    finished_time_rect = sf::RectangleShape(sf::Vector2f(RECT_SIZE));
    finished_time_rect.setOrigin(RECT_SIZE.x / 2.0f, RECT_SIZE.y / 2.0f);
    finished_time_rect.setPosition(0.0f, RECT_POS_Y + RECT_SIZE.y); // Bar will filling from bottom
    finished_time_rect.setFillColor(sf::Color(0, 255, 0, 64));

    total_time_rect = sf::RectangleShape(finished_time_rect.getSize());
    total_time_rect.setOrigin(finished_time_rect.getOrigin());
    total_time_rect.setPosition(finished_time_rect.getPosition());
    total_time_rect.setFillColor(sf::Color(255, 255, 255, 128));

    std::vector<const sf::Texture*> shop_textures;
    shop_textures.push_back(&resources_manager.get_texture(12));
    shop_textures.push_back(&resources_manager.get_texture(20));
    shop_textures.push_back(&resources_manager.get_texture(23));
    m_shopping_menu = std::make_unique<cShoppingMenu>(window, resources_manager.get_texture(14), shop_textures);

    m_is_creating = false;
    m_current_building = BUILDING_NONE;
    m_current_building_texture_id = -1;
}

void cBuildingShop::start_creating(const sf::RenderWindow& window, const BuildingType& building_type) {
    const auto RECT_SIZE  = resources_manager.get_texture(14).getSize();

    switch (building_type) {
        case BUILDING_INFANTRY_FACTORY: {
            Infantry_Factory factory(window, sf::Vector2f(16.0f, 16.0f));
            this->price = factory.Factory::get_price();
            this->time = factory.Factory::get_creating_time();
            m_current_building_texture_id = 20;
            finished_time_rect.setPosition(RECT_SIZE.x + RECT_SIZE.x / 2.0f, finished_time_rect.getPosition().y);
            total_time_rect.setPosition(finished_time_rect.getPosition());
            break;
        }
        case BUILDING_TANK_FACTORY: {
            Tank_Factory factory(window, sf::Vector2f(0.0f, 0.0f));
            this->price = factory.Factory::get_price();
            this->time = factory.Factory::get_creating_time();
            m_current_building_texture_id = 12;
            finished_time_rect.setPosition(RECT_SIZE.x / 2.0f, finished_time_rect.getPosition().y);
            total_time_rect.setPosition(finished_time_rect.getPosition());
            break;
        }
        case BUILDING_HOUSE: {
            this->price = cHouse(0, 0).get_price();
            this->time = cHouse(0, 0).get_creating_time();
            m_current_building_texture_id = 23;
            finished_time_rect.setPosition(2 * RECT_SIZE.x + RECT_SIZE.x / 2.0f, finished_time_rect.getPosition().y);
            total_time_rect.setPosition(finished_time_rect.getPosition());
            break;
        }
        case BUILDING_NONE: { return; }
    }

    m_current_building = building_type;
    m_creating_time_clock = sf::Clock();
    m_is_creating = true;
}

unsigned int cBuildingShop::get_creating_time() {
    const int DURATION = m_creating_time_clock.getElapsedTime().asMilliseconds();
    const float PERCENTAGE_OF_COMPLETION = static_cast<float>(DURATION) / get_total_time();

    if (PERCENTAGE_OF_COMPLETION <= 1.0f) {
        finished_time_rect.setSize(sf::Vector2f(total_time_rect.getGlobalBounds().width,
                                   -total_time_rect.getGlobalBounds().height * PERCENTAGE_OF_COMPLETION));
    }
    
    return DURATION;
}

unsigned int cBuildingShop::get_total_time() const {
    return time;
}

// std::unique_ptr<Factory> cBuildingShop::get_factory() {
//     if (is_finished()) {
//         m_is_creating = false;
//         m_current_building = BUILDING_NONE;
//         return std::move(m_created_factory);
//     }
//     return nullptr;
// }

void cBuildingShop::remove_factory() {
    m_is_creating = false;
    m_current_building = BUILDING_NONE;
    // m_created_factory = nullptr;
}

bool cBuildingShop::is_creating() const {
    return m_is_creating;
}

bool cBuildingShop::is_finished() {
    if (is_creating()) {
        if (get_creating_time() >= time) {
            return true;
        }
    }
    return false;
}

BuildingType cBuildingShop::get_shop_item_clicked(const sf::RenderWindow& window) const {
    return static_cast<BuildingType>(m_shopping_menu->getClickedItemId(window));
}

BuildingType cBuildingShop::get_current_building() const {
    return m_current_building;
}

int cBuildingShop::get_current_buidling_texture_id() const {
    return m_current_building_texture_id;
}

void cBuildingShop::display(sf::RenderWindow& window) {
    m_shopping_menu->display(window);

    if (is_creating())
    {
        get_creating_time();
        window.draw(total_time_rect);
        window.draw(finished_time_rect);
    }
}
