#ifndef LOBBY_HPP_INCLUDED
#define LOBBY_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include <deque>
#include <map>
#include "button.hpp"
#include "textbox.hpp"

class Lobby
{
    std::deque <Button> m_buttons;
    std::map <uint, sf::Text> m_players;
    std::deque <uint> m_players_id;
    std::deque <sf::Text> m_texts;
    TextBox m_textbox;
    sf::Sprite background;
    sf::RectangleShape m_chat_rect;

public:
    void init(const sf::RenderWindow& window);
    void clear();

    void mouse_click(const sf::RenderWindow& window);
    void mouse_move(const sf::RenderWindow& window);
    void text_entered(const sf::Event& event);
    void draw(sf::RenderWindow& window);

    void debug_show_size() const;

private:
    sf::Uint8 get_button_id_from_press(const sf::RenderWindow& window) const;

    void create_gui(const sf::RenderWindow& window);

    void add_lobby_message(const sf::String& message, sf::Color message_color = sf::Color::Black);
    void send_message(const sf::String& message);
    void refresh_players();
    void join_player(uint id, const sf::String& player_name);
    void disconnect_player(uint id);
};

#endif // LOBBY_HPP_INCLUDED
