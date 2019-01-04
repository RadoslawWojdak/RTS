#include "SFML/Graphics.hpp"
#include "engine.hpp"
#include "lobby.hpp"
#include "network_data.hpp"

extern sf::RenderWindow window;
extern Network_Data server;
extern Lobby lobby;

void Client_Engine::lobby_receive_inputs()
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
        case sf::Event::TextEntered:
        {
            lobby.text_entered(event);
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            lobby.mouse_click(window);
            break;
        }
        case sf::Event::MouseMoved:
        {
            lobby.mouse_move(window);
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}

void Client_Engine::lobby_logic()
{
    time = clock.restart();

    if(server.get_network_timeout() > sf::seconds(1))
    {
        return_to_menu();
        return;
    }
    server.add_network_timeout(time);
}

void Client_Engine::lobby_draw_frame()
{
    window.clear();
    lobby.draw(window);
    window.display();
}
