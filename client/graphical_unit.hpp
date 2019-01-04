#ifndef GRAPHICAL_UNIT_HPP_INCLUDED
#define GRAPHICAL_UNIT_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include <deque>
#include "../common/unit.hpp"
#include "deposit.hpp"

class Graphical_Unit : public Unit
{
    sf::Sprite m_sprite;
    sf::RectangleShape m_mark_rect;
    sf::Vector2u target;
    float m_rotation;//rad
    bool m_marked;

public:
    Graphical_Unit(const sf::Texture& texture, const sf::Vector2u& posOnGrid);
    Graphical_Unit(const sf::Texture& texture, uint x, uint y);

    virtual ~Graphical_Unit() {};

    virtual void shot() = 0;
    void move(std::deque<cDeposit>& deposits, unsigned int& resources);

    sf::Vector2u get_target() const;
    void set_target(const sf::Vector2u& posOnGrid);
    const sf::Texture* get_texture() const;
    const sf::Sprite& get_sprite() const;
    float get_rotation_rad() const;
    void set_rotation_rad(float angle);
    void set_rotation_deg(float angle);
    void display(sf::RenderWindow& window) const;
    bool is_marked() const;
    void mark();
    void unmark();

private:
    static constexpr auto DIGGING_TIME = 120;    //FRAMES

    void dig(cDeposit& deposit, unsigned int& resources);
    void adjust_mark_position();

    float deg_to_rad(float angle);
    float rad_to_deg(float angle);

    unsigned int time_to_dig;
};

#endif // GRAPHICAL_UNIT_HPP_INCLUDED