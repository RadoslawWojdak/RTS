#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "SFML/Graphics.hpp"

#define STANDARD_TEXTBOX_SIZE sf::Vector2f(192.0f, 24.0f)

class TextBox : protected sf::RectangleShape
{
    sf::Text m_text;
    bool marked;

public:
    TextBox(const sf::Vector2f& pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f& size = STANDARD_TEXTBOX_SIZE, const sf::String& text = "");

    void display(sf::RenderWindow& window) const;

    bool is_mouse_on(const sf::RenderWindow& window) const;
    bool is_pressed(const sf::RenderWindow& window) const;
    bool is_marked() const;

    void mark();
    void unmark();
    void enter_text(sf::Uint32 unicode);
    void set_string(sf::String string);
    sf::String get_string() const;
    sf::Vector2f get_position() const;
    void set_position(const sf::Vector2f& pos);
    void set_fill_color(const sf::Color& color);
    void set_text_color(const sf::Color& color);
};

#endif // TEXTBOX_HPP_INCLUDED
