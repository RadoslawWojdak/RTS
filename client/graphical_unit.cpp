#include "graphical_unit.hpp"
#include <math.h>

Graphical_Unit::Graphical_Unit(const sf::Texture& texture, const sf::Vector2u& posOnGrid)
{
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(
        m_sprite.getGlobalBounds().width / 2,
        m_sprite.getGlobalBounds().height / 2
    );
    m_sprite.setPosition(posOnGrid.x * 32.0f + 16.0f, posOnGrid.y * 32.0f + 16.0f);
    set_rotation_rad(0.0f);

    m_mark_rect = sf::RectangleShape(sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
    m_mark_rect.setOrigin(m_sprite.getOrigin());
    m_mark_rect.setOutlineThickness(1.0f);
    m_mark_rect.setFillColor(sf::Color(255, 255, 255, 0));
    m_mark_rect.setOutlineColor(sf::Color(255, 255, 255, 127));

    adjust_mark_position();

    time_to_dig = 60;

    unmark();
}
Graphical_Unit::Graphical_Unit(const sf::Texture& texture, uint x, uint y)
    : Graphical_Unit(texture, sf::Vector2u(x, y)) {}

void Graphical_Unit::dig(cDeposit& deposit, unsigned int& resources) {
    resources += deposit.dig();
}

void Graphical_Unit::move(std::deque<cDeposit>& deposits, unsigned int& resources)
{
    if (has_target())
    {
        time_to_dig = DIGGING_TIME;

        const sf::Vector2f POSITION = m_sprite.getPosition();

        //ROTATION
        const float DISTANCE_X = get_target_x() * 32 - m_sprite.getPosition().x + m_sprite.getTextureRect().width / 2.0f;
        const float DISTANCE_Y = get_target_y() * 32 - m_sprite.getPosition().y + m_sprite.getTextureRect().height / 2.0f;
        const float UNIT_TARGET_RADIANS = atan2(DISTANCE_Y, DISTANCE_X);
        set_rotation_rad(UNIT_TARGET_RADIANS);

        //MOVE
        const float GAME_SPEED = 10;//1 sec in life == ? secs in game
        const float METER_TO_PX = 3;//1 meter == ? pixels
        const float PX_PER_SEC = ((get_speed() * (1000 * METER_TO_PX)) / 3600.0f) * GAME_SPEED;
        const float FRAMERATE = 60.0f;
        const float PX_PER_FRAME = PX_PER_SEC / FRAMERATE;

        const sf::Vector2f MOVE(
            cos(get_rotation_rad()) * PX_PER_FRAME,
            sin(get_rotation_rad()) * PX_PER_FRAME
        );

        m_sprite.move(MOVE);
        adjust_mark_position();

        if (std::fabs(DISTANCE_X) < 1 && std::fabs(DISTANCE_Y) < 1)
        {
            unset_target();
        }
    } else {
        const auto IS_HARVESTING  = ((get_abilities() & HARVESTING) != 0);
        if (IS_HARVESTING) {
            time_to_dig--;
            if (time_to_dig == 0) {
                time_to_dig = DIGGING_TIME;
                for (auto i = 0; i < deposits.size(); i++) {
                    const unsigned int GRID_X = m_sprite.getPosition().x / 32;
                    const unsigned int GRID_Y = m_sprite.getPosition().y / 32;
                    const unsigned int DEPOSIT_GRID_X = deposits[i].get_sprite().getPosition().x / 32;
                    const unsigned int DEPOSIT_GRID_Y = deposits[i].get_sprite().getPosition().y / 32;

                    if (GRID_X == DEPOSIT_GRID_X && GRID_Y == DEPOSIT_GRID_Y) {
                        dig(deposits[i], resources);
                        if (deposits[i].is_empty()) {
                            deposits.erase(deposits.begin() + i);
                        }
                        return;
                    }
                }

                auto distance = 9999999.9f;
                auto closest_deposit = -1;
                for (auto i = 0; i < deposits.size(); i++) {
                    const auto DEPOSIT_X = deposits[i].get_sprite().getPosition().x;
                    const auto DEPOSIT_Y = deposits[i].get_sprite().getPosition().y;
                    const auto DISTANCE_X = std::fabs(DEPOSIT_X - m_sprite.getPosition().x + m_sprite.getTextureRect().width / 2.0f);
                    const auto DISTANCE_Y = std::fabs(DEPOSIT_Y - m_sprite.getPosition().y + m_sprite.getTextureRect().height / 2.0f);
                    const auto DISTANCE = std::sqrt(std::pow(DISTANCE_X, 2) + std::pow(DISTANCE_Y, 2));

                    if (DISTANCE < distance) {
                        distance = DISTANCE;
                        closest_deposit = i;
                    }
                }
                time_to_dig = DIGGING_TIME;

                if (closest_deposit != -1) {
                    const auto DEPOSIT_X = static_cast<unsigned int>(deposits[closest_deposit].get_sprite().getPosition().x / 32);
                    const auto DEPOSIT_Y = static_cast<unsigned int>(deposits[closest_deposit].get_sprite().getPosition().y / 32);

                    set_target(sf::Vector2u(DEPOSIT_X, DEPOSIT_Y));
                }
            }
        }
    }
}

sf::Vector2u Graphical_Unit::get_target() const
{
    return sf::Vector2u(get_target_x(), get_target_y());
}

void Graphical_Unit::set_target(const sf::Vector2u& posOnGrid)
{
    Unit::set_target(posOnGrid.x, posOnGrid.y);
    target = posOnGrid;
}

const sf::Texture* Graphical_Unit::get_texture() const
{
    return m_sprite.getTexture();
}

const sf::Sprite& Graphical_Unit::get_sprite() const
{
    return m_sprite;
}

bool Graphical_Unit::is_marked() const
{
    return m_marked;
}

void Graphical_Unit::mark()
{
    m_marked = true;
}

void Graphical_Unit::unmark()
{
    m_marked = false;
}

float Graphical_Unit::get_rotation_rad() const
{
    return m_rotation;
}

void Graphical_Unit::set_rotation_rad(float angle)
{
    m_rotation = angle;
    // const auto IS_GOING_LEFT = (angle < 2 * 3.14 - (3.14 / 2) && angle > (3.14 / 2));

    // if (IS_GOING_LEFT)
    // {
    //     m_sprite.setScale(-1.0f, 1.0f);
    // }
    // else
    // {
    //     m_sprite.setScale(1.0f, 1.0f);
    // }
    m_sprite.setRotation(rad_to_deg(angle));
}

void Graphical_Unit::set_rotation_deg(float angle)
{
    m_rotation = deg_to_rad(angle);
    set_rotation_rad(m_rotation);
}

float Graphical_Unit::deg_to_rad(float angle)
{
    return angle * (M_PI / 180.0f);
}

float Graphical_Unit::rad_to_deg(float angle)
{
    return angle * (180.0f / M_PI);
}

void Graphical_Unit::display(sf::RenderWindow& window) const
{
    if (is_marked())
    {
        window.draw(m_mark_rect);
    }

    window.draw(m_sprite);
}

void Graphical_Unit::adjust_mark_position()
{
    m_mark_rect.setPosition(m_sprite.getPosition());
}
