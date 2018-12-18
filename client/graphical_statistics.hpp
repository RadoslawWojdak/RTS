#ifndef GRAPHICAL_STATISTICS
#define GRAPHICAL_STATISTICS

#include <SFML/Graphics.hpp>
#include "statistics_manager.hpp"

class Graphical_Statistics : public Statistics_Manager
{
    sf::RectangleShape m_stats_bar;

    sf::Sprite m_resources_sprite;
    sf::Text m_resources_text;

public:
    Graphical_Statistics(const sf::RenderWindow& window, unsigned int resources);

    virtual unsigned int get_resources() override;
    virtual void add_resources(unsigned int amount) override;
    virtual void subtract_resources(unsigned int amount) override;

    void display(sf::RenderWindow& window) const;

private:
    void refresh();
};

#endif // GRAPHICAL_STATISTICS