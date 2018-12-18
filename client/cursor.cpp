#include "cursor.hpp"

Cursor::Cursor()
{
    marking = false;

    rect = sf::RectangleShape();
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(1.0f);
    rect.setFillColor(sf::Color(0, 255, 0, 64));
}

void Cursor::start_marking(const sf::Vector2i& mouse_position)
{
    marking = true;

    rect.setPosition(sf::Vector2f(mouse_position));
    rect.setSize(sf::Vector2f(1, 1));
}

void Cursor::continue_marking(const sf::Vector2i& mouse_position)
{
    if (marking)
    {
        rect.setSize(sf::Vector2f(mouse_position.x - rect.getPosition().x, mouse_position.y - rect.getPosition().y));
    }
}

const sf::RectangleShape& Cursor::stop_marking()
{
    marking = false;
    return std::move(rect);
}

void Cursor::draw_marked_rect(sf::RenderWindow& window)
{
    if (marking)
    {
        window.draw(rect);
    }
}
