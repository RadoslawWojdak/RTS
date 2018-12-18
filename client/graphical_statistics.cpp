#include "graphical_statistics.hpp"
#include "resources_manager.hpp"

extern Resources_Manager resources_manager;

Graphical_Statistics::Graphical_Statistics(const sf::RenderWindow& window, unsigned int resources)
    : Statistics_Manager(resources)
{
    m_stats_bar.setSize(sf::Vector2f(window.getSize().x, 20.0f));
    m_stats_bar.setPosition(0.0f, 0.0f);
    m_stats_bar.setFillColor(sf::Color::Blue);

    m_resources_sprite.setTexture(resources_manager.get_texture(11));
    m_resources_sprite.setPosition(4.0f, 4.0f);

    m_resources_text.setFont(resources_manager.get_font());
    m_resources_text.setPosition(20.0f, 2.0f);
    m_resources_text.setCharacterSize(14u);
    m_resources_text.setFillColor(sf::Color::White);

    refresh();
}

unsigned int Graphical_Statistics::get_resources()
{
    return Statistics_Manager::get_resources();
}

void Graphical_Statistics::add_resources(unsigned int amount)
{
    Statistics_Manager::add_resources(amount);
    refresh();
}

void Graphical_Statistics::subtract_resources(unsigned int amount)
{
    Statistics_Manager::subtract_resources(amount);
    refresh();
}

void Graphical_Statistics::refresh()
{
    m_resources_text.setString(std::to_string(get_resources()));
}

void Graphical_Statistics::display(sf::RenderWindow& window) const
{
    window.draw(m_stats_bar);
    window.draw(m_resources_sprite);
    window.draw(m_resources_text);
}
