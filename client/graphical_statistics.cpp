#include "graphical_statistics.hpp"
#include "resources_manager.hpp"

extern Resources_Manager resources_manager;

Graphical_Statistics::Graphical_Statistics(const sf::RenderWindow& window, unsigned int resources, unsigned int max_units_capacity)
    : Statistics_Manager(resources, max_units_capacity)
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

    m_units_capacity_sprite.setTexture(resources_manager.get_texture(13));
    m_units_capacity_sprite.setPosition(64.0f, 4.0f);

    m_units_capacity_text.setFont(resources_manager.get_font());
    m_units_capacity_text.setPosition(80.0f, 2.0f);
    m_units_capacity_text.setCharacterSize(14u);
    m_units_capacity_text.setFillColor(sf::Color::White);

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

unsigned int Graphical_Statistics::get_max_units_capacity()
{
    return Statistics_Manager::get_max_units_capacity();
}

void Graphical_Statistics::increase_max_units_capacity(unsigned int amount)
{
    Statistics_Manager::increase_max_units_capacity(amount);
    refresh();
}

void Graphical_Statistics::decrease_max_units_capacity(unsigned int amount)
{
    Statistics_Manager::decrease_max_units_capacity(amount);
    refresh();
}

unsigned int Graphical_Statistics::get_current_units_number()
{
    return Statistics_Manager::get_current_units_number();
}

void Graphical_Statistics::increase_current_units_number(unsigned int amount)
{
    Statistics_Manager::increase_current_units_number(amount);
    refresh();
}

void Graphical_Statistics::decrease_current_units_number(unsigned int amount)
{
    Statistics_Manager::decrease_current_units_number(amount);
    refresh();
}


void Graphical_Statistics::refresh()
{
    m_resources_text.setString(std::to_string(Statistics_Manager::get_resources()));
    m_units_capacity_text.setString(std::to_string(Statistics_Manager::get_current_units_number()) + " / " +
                                    std::to_string(Statistics_Manager::get_max_units_capacity()));
}

void Graphical_Statistics::display(sf::RenderWindow& window) const
{
    window.draw(m_stats_bar);
    window.draw(m_resources_sprite);
    window.draw(m_resources_text);
    window.draw(m_units_capacity_sprite);
    window.draw(m_units_capacity_text);
}
