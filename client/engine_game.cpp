#include "SFML/Graphics.hpp"
#include "engine.hpp"
#include "network_data.hpp"
#include "cursor.hpp"
#include "infantry.hpp"
#include "tank.hpp"
#include "resources_manager.hpp"

extern sf::RenderWindow window;
extern Network_Data server;
extern Resources_Manager resources_manager;

Cursor cursor;

void Client_Engine::init_game()
{
    buildingShop = std::make_unique<cBuildingShop>(window);
    keepingObjectSprite.setColor(sf::Color(255, 255, 255, 127));

    m_game_stats = std::make_unique<Graphical_Statistics>(window, 5000u, 15u);

    tankFactories.emplace_back(std::make_unique<Tank_Factory>(window, 512, 256));
    infantryFactories.emplace_back(std::make_unique<Infantry_Factory>(window, 624, 256));

    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 8, 8));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 8, 9));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 9, 9));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_SCRAPER, 1, 9, 8));

    deposits.emplace_back(10, 11, 300);
    deposits.emplace_back(11, 11, 700);
    deposits.emplace_back(12, 11, 1100);
    deposits.emplace_back(13, 11, 700);
    deposits.emplace_back(14, 11, 700);
    deposits.emplace_back(15, 11, 300);

    deposits.emplace_back(24, 16, 300);
    deposits.emplace_back(24, 15, 300);
    deposits.emplace_back(24, 14, 300);
    deposits.emplace_back(24, 13, 300);
    deposits.emplace_back(23, 16, 300);
    deposits.emplace_back(23, 15, 700);
    deposits.emplace_back(23, 14, 1100);
    deposits.emplace_back(22, 17, 300);
    deposits.emplace_back(22, 16, 700);
    deposits.emplace_back(22, 15, 700);
    deposits.emplace_back(22, 14, 300);
    deposits.emplace_back(21, 18, 300);
    deposits.emplace_back(21, 17, 700);
    deposits.emplace_back(21, 16, 300);
    deposits.emplace_back(20, 18, 300);

    m_game_stats->increase_current_units_number(4u);
}

void Client_Engine::game_receive_inputs()
{
    static bool is_marking = false;
    sf::Event event;
    while( window.pollEvent(event) )
    {
        switch(event.type)
        {
        case sf::Event::Closed:
        {
            quit_engine();
            break;
        }
        case sf::Event::Resized:
        {
            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == sf::Mouse::Left && !keep_building)
            {
                is_marking = true;

                if (marked_building) {
                    for (auto& factory : tankFactories) {
                        if (factory->is_marked()) {
                            if (factory->get_shop_item_clicked(window) != TankType::TANK_NONE) {
                                is_marking = false;
                                break;
                            }
                        }
                    }
                    for (auto& factory : infantryFactories) {
                        if (factory->is_marked()) {
                            if (factory->get_shop_item_clicked(window) != InfantryType::INFANTRY_NONE) {
                                is_marking = false;
                                break;
                            }
                        }
                    }
                } else {
                    if (buildingShop->get_shop_item_clicked(window) != BuildingType::BUILDING_NONE) {
                        is_marking = false;
                        break;
                    }
                }

                if (is_marking) {
                    unmark_objects();
                    cursor.start_marking(sf::Mouse::getPosition(window));
                }
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            switch (event.mouseButton.button)
            {
                case sf::Mouse::Left:
                {
                    if (!is_marking || keep_building) {
                        if (marked_building) {
                            for (auto& factory : tankFactories) {
                                if (factory->is_marked()) {
                                    if (factory->get_shop_item_clicked(window) != TankType::TANK_NONE) {
                                        start_creating(*factory);
                                        break;
                                    }
                                }
                            }
                            for (auto& factory : infantryFactories) {
                                if (factory->is_marked()) {
                                    if (factory->get_shop_item_clicked(window) != InfantryType::INFANTRY_NONE) {
                                        start_creating(*factory);
                                        break;
                                    }
                                }
                            }
                        } else {
                            if (buildingShop->get_shop_item_clicked(window) != BuildingType::BUILDING_NONE) {
                                if (buildingShop->get_shop_item_clicked(window) == buildingShop->get_current_building() &&
                                    buildingShop->is_finished() &&
                                    !keep_building) {

                                    keep_building = true;
                                } else {
                                    start_creating(*buildingShop);
                                }
                            } else if (keep_building) {
                                const auto POSITION = sf::Mouse::getPosition(window);
                                switch (buildingShop->get_current_building()) {
                                    case BUILDING_INFANTRY_FACTORY: {
                                        infantryFactories.emplace_back(std::make_unique<Infantry_Factory>(window, sf::Vector2f(POSITION)));
                                        break;
                                    }
                                    case BUILDING_TANK_FACTORY: {
                                        tankFactories.emplace_back(std::make_unique<Tank_Factory>(window, sf::Vector2f(POSITION)));
                                        break;
                                    }
                                    case BUILDING_NONE: { break; }
                                }
                                buildingShop->get_factory();
                                keep_building = false;
                            }
                        }
                    } else {
                        sf::RectangleShape marking_rect = cursor.stop_marking();
                        mark_covered_objects(marking_rect);
                    }
                    break;
                }
                case sf::Mouse::Right:
                {
                    sf::Vector2u pos_on_grid(((sf::Mouse::getPosition(window).x) / 32),
                                             ((sf::Mouse::getPosition(window).y) / 32));
                    point_destination(pos_on_grid);

                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}

void Client_Engine::game_logic()
{
    time = clock.restart();

    cursor.continue_marking(sf::Mouse::getPosition(window));
    move_units();

    for (auto& factory : tankFactories)
    {
        if (factory->is_creating())
        {
            std::unique_ptr<Tank> tank = factory->get_tank();
            if (tank != nullptr)
            {
                m_game_stats->increase_current_units_number(1);
                units.push_back(std::move(tank));
            }
        }
    }
    for (auto& factory : infantryFactories)
    {
        if (factory->is_creating())
        {
            std::unique_ptr<Infantry> infantry = factory->get_infantry();
            if (infantry != nullptr)
            {
                m_game_stats->increase_current_units_number(1);
                units.push_back(std::move(infantry));
            }
        }
    }

    if(server.get_network_timeout() > sf::seconds(1))
    {
        return_to_menu();
        return;
    }
    server.add_network_timeout(time);
}

void Client_Engine::game_draw_frame()
{
    adjust_keeping_object();

    window.clear();

    for (auto& deposit : deposits) {
        deposit.display(window);
    }

    for (auto& unit : units) {
        unit->display(window);
    }

    for (auto& factory : tankFactories) {
        factory->display(window);
    }
    for (auto& factory : infantryFactories) {
        factory->display(window);
    }

    if (!marked_building) {
        buildingShop->display(window);
    }
    if (keep_building) {
        window.draw(keepingObjectSprite);
    }

    cursor.display_marked_rect(window);

    m_game_stats->display(window);

    window.display();
}

void Client_Engine::mark_covered_objects(const sf::RectangleShape& rect)
{
    const auto MATH_RECT = rect.getGlobalBounds();

    bool marked_any_unit = false;

    for (auto& unit : units)
    {
        if (MATH_RECT.intersects(unit->get_sprite().getGlobalBounds()))
        {
            marked_any_unit = true;
            unit->mark();
        }
    }

    int marked_factories = 0;
    if (!marked_any_unit)
    {
        for (auto& factory : tankFactories)
        {
            if (MATH_RECT.intersects(factory->get_sprite().getGlobalBounds()))
            {
                factory->mark();
                marked_factories++;
                marked_building = true;
            }
        }
        for (auto& factory : infantryFactories)
        {
            if (MATH_RECT.intersects(factory->get_sprite().getGlobalBounds()))
            {
                factory->mark();
                marked_factories++;
                marked_building = true;
            }
        }
    }
    if (marked_factories > 1)
    {
        unmark_objects();
    }
}

void Client_Engine::unmark_objects()
{
    marked_building = false;
    for (auto& unit : units)
    {
        unit->unmark();
    }
    for (auto& factory : tankFactories)
    {
        factory->unmark();
    }
    for (auto& factory : infantryFactories)
    {
        factory->unmark();
    }
}

void Client_Engine::point_destination(const sf::Vector2u& target)
{
    for (auto& unit : units)
    {
        if (unit->is_marked())
        {
            unit->set_target(target);
        }
    }
}

void Client_Engine::move_units()
{
    for (auto& unit : units)
    {
        unsigned int extra_resources = 0;

        unit->move(deposits, extra_resources);
        m_game_stats->add_resources(extra_resources);
    }
}

void Client_Engine::start_creating(Tank_Factory& factory)
{
    if (m_game_stats->get_max_units_capacity() > m_game_stats->get_current_units_number())
    {
        const auto TANK_TYPE = factory.get_shop_item_clicked(window);
        const auto TANK_PRICE = Tank(TANK_TYPE, 1, sf::Vector2u(0,0)).get_price();

        if (TANK_PRICE <= m_game_stats->get_resources() && !factory.is_creating())
        {
            factory.start_creating(TANK_TYPE);
            m_game_stats->subtract_resources(TANK_PRICE);
        }
    }
}

void Client_Engine::start_creating(Infantry_Factory& factory)
{
    if (m_game_stats->get_max_units_capacity() > m_game_stats->get_current_units_number())
    {
        const auto INFANTRY_TYPE = factory.get_shop_item_clicked(window);
        const auto INFANTRY_PRICE = Infantry(INFANTRY_TYPE, 1, sf::Vector2u(0,0)).get_price();

        if (INFANTRY_PRICE <= m_game_stats->get_resources() && !factory.is_creating())
        {
            factory.start_creating(INFANTRY_TYPE);
            m_game_stats->subtract_resources(INFANTRY_PRICE);
        }
    }
}

void Client_Engine::start_creating(cBuildingShop& shop)
{
    const auto BUILDING_TYPE = shop.get_shop_item_clicked(window);
    unsigned int buildingPrice;
    switch (BUILDING_TYPE) {
        case BUILDING_INFANTRY_FACTORY: {
            buildingPrice = Infantry_Factory(window, sf::Vector2f(0,0)).get_price();
            break;
        }
        case BUILDING_TANK_FACTORY: {
            buildingPrice = Tank_Factory(window, sf::Vector2f(0,0)).get_price();
            break;
        }
        case BUILDING_NONE: { break; }
    }

    if (buildingPrice <= m_game_stats->get_resources() && !buildingShop->is_creating())
    {
        buildingShop->start_creating(window, BUILDING_TYPE);
        m_game_stats->subtract_resources(buildingPrice);
    }
}

void Client_Engine::adjust_keeping_object() {
    const auto KEEPING_TEXTURE_ID = buildingShop->get_current_buidling_texture_id();
    if (keep_building) {
        if (KEEPING_TEXTURE_ID != -1) {
            window.setMouseCursorVisible(false);
            keepingObjectSprite.setTexture(resources_manager.get_texture(KEEPING_TEXTURE_ID));
            keepingObjectSprite.setOrigin(keepingObjectSprite.getTextureRect().width / 2.0f,
                                          keepingObjectSprite.getTextureRect().height / 2.0f);
        }
        keepingObjectSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
    } else {
        window.setMouseCursorVisible(true);
    }
}
