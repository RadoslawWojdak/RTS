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
                cursor.start_marking(sf::Mouse::getPosition(window));
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                cursor.stop_marking();
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
