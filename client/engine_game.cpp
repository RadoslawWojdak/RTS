#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include "network_data.hpp"
#include "cursor.hpp"
#include "infantry.hpp"
#include "tank.hpp"

extern sf::RenderWindow window;
extern Network_Data server;

Cursor cursor;

void Client_Engine::init_game()
{
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 256, 256));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 256, 288));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 288, 288));
    units.emplace_back(std::make_unique<Tank>(TankType::TANK_A, 1, 288, 256));
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
                unmark_units();
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
                    mark_covered_units(marking_rect);
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

    cursor.display_marked_rect(window);

    window.display();
}

void Client_Engine::mark_covered_units(const sf::RectangleShape& rect)
{
    const auto MATH_RECT = rect.getGlobalBounds();

    for (auto& unit : units)
    {
        if (MATH_RECT.intersects(unit->get_sprite().getGlobalBounds()))
        {
            unit->mark();
        }
    }
}

void Client_Engine::unmark_units()
{
    for (auto& unit : units)
    {
        unit->unmark();
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
