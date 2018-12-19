#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include "network_data.hpp"
#include "cursor.hpp"
#include "infantry.hpp"
#include "tank.hpp"
#include "tank_factory.hpp"

extern sf::RenderWindow window;
extern Network_Data server;

Cursor cursor;

void Client_Engine::init_game(const sf::RenderWindow& window)
{
    m_game_stats = std::make_unique<Graphical_Statistics>(window, 5000u, 15u);

    factories.emplace_back(std::make_unique<Tank_Factory>(512, 256));

    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 256, 256));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 256, 288));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 288, 288));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 288, 256));

    m_game_stats->increase_current_units_number(4u);
}

void Client_Engine::game_receive_inputs()
{
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
                unmark_objects();
                cursor.start_marking(sf::Mouse::getPosition(window));
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            switch (event.mouseButton.button)
            {
                case sf::Mouse::Left:
                {
                    sf::RectangleShape marking_rect = cursor.stop_marking();
                    mark_covered_objects(marking_rect);
                    break;
                }
                case sf::Mouse::Right:
                {
                    sf::Vector2i pos_on_grid(((sf::Mouse::getPosition(window).x + 16) / 32) * 32,
                                             ((sf::Mouse::getPosition(window).y + 16) / 32) * 32);
                    point_destination(pos_on_grid);

                    for (auto& factory : factories)
                    {
                        if (factory->is_marked())
                        {
                            if (factory->get_sprite().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                            {
                                start_creating(*factory);
                            }
                            break;
                        }
                    }

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

    for (auto& factory : factories)
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

    for (auto& factory : factories)
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
        for (auto& factory : factories)
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
    for (auto& factory : factories)
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

void Client_Engine::start_creating(Tank_Factory& factory)
{
    if (m_game_stats->get_max_units_capacity() > m_game_stats->get_current_units_number())
    {
        const auto TANK_TYPE = TankType::TANK_A;
        const auto TANK_PRICE = Tank(TANK_TYPE, 1, sf::Vector2f(0,0)).get_price();

        if (TANK_PRICE < m_game_stats->get_resources() && !factory.is_creating())
        {
            factory.start_creating(TANK_TYPE);
            m_game_stats->subtract_resources(TANK_PRICE);
        }
    }
}
