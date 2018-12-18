#include "cursor.hpp"
#include <math.h>

Cursor::Cursor()
{
    m_marking = false;

    m_rect = sf::RectangleShape();
    m_rect.setOutlineColor(sf::Color::Green);
    m_rect.setOutlineThickness(1.0f);
    m_rect.setFillColor(sf::Color(0, 255, 0, 64));
}

void Cursor::start_marking(const sf::Vector2i& mouse_position)
{
    m_marking = true;

    m_rect.setPosition(sf::Vector2f(mouse_position));
    m_rect.setSize(sf::Vector2f(1, 1));
}

void Cursor::continue_marking(const sf::Vector2i& mouse_position)
{
    if (m_marking)
    {
        m_rect.setSize(sf::Vector2f(mouse_position.x - m_rect.getPosition().x, mouse_position.y - m_rect.getPosition().y));
    }
}

const sf::RectangleShape& Cursor::stop_marking()
{
    m_marking = false;

    if (std::fabs(m_rect.getSize().x) < 1 || std::fabs(m_rect.getSize().y) < 1)   //For marking single unit
    {
        m_rect.setSize(sf::Vector2f(1.0f, 1.0f));
    }

    return std::move(m_rect);
}

void Cursor::display_marked_rect(sf::RenderWindow& window)
{
    if (m_marking)
    {
        window.draw(m_rect);
    }
}
