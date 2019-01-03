#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include "network_data.hpp"
#include "cursor.hpp"
#include "infantry.hpp"
#include "tank.hpp"

extern sf::RenderWindow window;
extern Network_Data server;

Cursor cursor;

void Client_Engine::init_game(const sf::RenderWindow& window)
{
    m_game_stats = std::make_unique<Graphical_Statistics>(window, 5000u, 15u);

    tankFactories.emplace_back(std::make_unique<Tank_Factory>(window, 512, 256));
    infantryFactories.emplace_back(std::make_unique<Infantry_Factory>(window, 608, 256));

    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 256, 256));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 256, 288));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 288, 288));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 288, 256));

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
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                is_marking = true;
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
                    if (!is_marking) {
                        for (auto& factory : tankFactories) {
                            if (factory->is_marked()) {
                                if (factory->get_shop_item_clicked(window) != TankType::TANK_NONE) {
                                    start_creating(window, *factory);
                                    break;
                                }
                            }
                        }
                        for (auto& factory : infantryFactories) {
                            if (factory->is_marked()) {
                                if (factory->get_shop_item_clicked(window) != InfantryType::INFANTRY_NONE) {
                                    start_creating(window, *factory);
                                    break;
                                }
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
                    sf::Vector2i pos_on_grid(((sf::Mouse::getPosition(window).x + 16) / 32) * 32,
                                             ((sf::Mouse::getPosition(window).y + 16) / 32) * 32);
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
    window.clear();

    for (auto& unit : units)
    {
        unit->display(window);
    }

    for (auto& factory : tankFactories)
    {
        factory->display(window);
    }
    for (auto& factory : infantryFactories)
    {
        factory->display(window);
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
            }
        }
        for (auto& factory : infantryFactories)
        {
            if (MATH_RECT.intersects(factory->get_sprite().getGlobalBounds()))
            {
                factory->mark();
                marked_factories++;
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

void Client_Engine::point_destination(const sf::Vector2i& target)
{
    for (auto& unit : units)
    {
        if (unit->is_marked())
        {
            unit->set_target(sf::Vector2f(target));
        }
    }
}

void Client_Engine::move_units()
{
    for (auto& unit : units)
    {
        unit->move();
    }
}

void Client_Engine::start_creating(const sf::RenderWindow& window, Tank_Factory& factory)
{
    if (m_game_stats->get_max_units_capacity() > m_game_stats->get_current_units_number())
    {
        const auto TANK_TYPE = factory.get_shop_item_clicked(window);
        const auto TANK_PRICE = Tank(TANK_TYPE, 1, sf::Vector2f(0,0)).get_price();

        if (TANK_PRICE < m_game_stats->get_resources() && !factory.is_creating())
        {
            factory.start_creating(TANK_TYPE);
            m_game_stats->subtract_resources(TANK_PRICE);
        }
    }
}

void Client_Engine::start_creating(const sf::RenderWindow& window, Infantry_Factory& factory)
{
    if (m_game_stats->get_max_units_capacity() > m_game_stats->get_current_units_number())
    {
        const auto INFANTRY_TYPE = factory.get_shop_item_clicked(window);
        const auto INFANTRY_PRICE = Infantry(INFANTRY_TYPE, 1, sf::Vector2f(0,0)).get_price();

        if (INFANTRY_PRICE < m_game_stats->get_resources() && !factory.is_creating())
        {
            factory.start_creating(INFANTRY_TYPE);
            m_game_stats->subtract_resources(INFANTRY_PRICE);
        }
    }
}
