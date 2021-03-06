#ifndef CURSOR_HPP_INCLUDED
#define CURSOR_HPP_INCLUDED

#include "SFML/Graphics.hpp"

class Cursor
{
    sf::RectangleShape m_rect;
    bool m_marking;

public:
    Cursor();

    void start_marking(const sf::Vector2i& mouse_position);
    void continue_marking(const sf::Vector2i& mouse_position);
    const sf::RectangleShape& stop_marking();
    void display_marked_rect(sf::RenderWindow& window);
};

#endif // CURSOR_HPP_INCLUDED
