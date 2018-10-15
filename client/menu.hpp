#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "SFML/Graphics.hpp"

class Menu
{
    std::vector <sf::Text> m_texts;//24
    sf::Uint8 m_state;//1

public:
    void main_menu();

    void draw(sf::RenderWindow& window);

    void debug_show_size() const;

private:
    sf::Uint8 get_text_id_from_mousepress(const sf::Event& event) const;
};

#endif // MENU_HPP_INCLUDED