#include "graphical_factory.hpp"
#include <math.h>

Graphical_Factory::Graphical_Factory(const sf::Texture& texture, const sf::Vector2f& pos)
{
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(
        m_sprite.getGlobalBounds().width / 2,
        m_sprite.getGlobalBounds().height / 2
    );
    m_sprite.setPosition(pos);

    m_mark_rect = sf::RectangleShape(sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
    m_mark_rect.setOrigin(m_sprite.getOrigin());
    m_mark_rect.setOutlineThickness(1.0f);
    m_mark_rect.setFillColor(sf::Color(255, 255, 255, 0));
    m_mark_rect.setOutlineColor(sf::Color(255, 255, 255, 127));

    adjust_mark_position();

    unmark();
}
Graphical_Factory::Graphical_Factory(const sf::Texture& texture, float x, float y)
    : Graphical_Factory(texture, sf::Vector2f(x, y)) {}

const sf::Texture* Graphical_Factory::get_texture() const
{
    return m_sprite.getTexture();
}

const sf::Sprite& Graphical_Factory::get_sprite() const
{
    return m_sprite;
}

bool Graphical_Factory::is_marked() const
{
    return m_marked;
}

void Graphical_Factory::mark()
{
    m_marked = true;
}

void Graphical_Factory::unmark()
{
    m_marked = false;
}

void Graphical_Factory::display(sf::RenderWindow& window) const
{
    if (is_marked())
    {
        window.draw(m_mark_rect);
    }

    window.draw(m_sprite);
}

void Graphical_Factory::adjust_mark_position()
{
    m_mark_rect.setPosition(m_sprite.getPosition());
}
