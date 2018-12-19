#ifndef GRAPHICAL_STATISTICS
#define GRAPHICAL_STATISTICS

#include <SFML/Graphics.hpp>
#include "statistics_manager.hpp"

class Graphical_Statistics : public Statistics_Manager
{
    sf::RectangleShape m_stats_bar;

    sf::Sprite m_resources_sprite;
    sf::Text m_resources_text;

    sf::Sprite m_units_capacity_sprite;
    sf::Text m_units_capacity_text;

public:
    Graphical_Statistics(const sf::RenderWindow& window, unsigned int resources, unsigned int max_units_capacity);

    virtual unsigned int get_resources() override;
    virtual void add_resources(unsigned int amount) override;
    virtual void subtract_resources(unsigned int amount) override;

    virtual unsigned int get_max_units_capacity() override;
    virtual void increase_max_units_capacity(unsigned int amount) override;
    virtual void decrease_max_units_capacity(unsigned int amount) override;

    virtual unsigned int get_current_units_number() override;
    virtual void increase_current_units_number(unsigned int amount) override;
    virtual void decrease_current_units_number(unsigned int amount) override;

    void display(sf::RenderWindow& window) const;

private:
    void refresh();
};

#endif // GRAPHICAL_STATISTICS