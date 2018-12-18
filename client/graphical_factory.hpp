#ifndef GRAPHICAL_FACTORY_HPP_INCLUDED
#define GRAPHICAL_FACTORY_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include "../common/factory.hpp"

class Graphical_Factory : public Factory
{
    sf::Sprite m_sprite;
    sf::RectangleShape m_mark_rect;
    bool m_marked;

public:
    Graphical_Factory(const sf::Texture& texture, const sf::Vector2f& pos);
    Graphical_Factory(const sf::Texture& texture, float x, float y);

    virtual ~Graphical_Factory() {};

    const sf::Texture* get_texture() const;
    const sf::Sprite& get_sprite() const;
    void display(sf::RenderWindow& window) const;
    bool is_marked() const;
    void mark();
    void unmark();

private:
    void adjust_mark_position();
};

#endif // GRAPHICAL_FACTORY_HPP_INCLUDED