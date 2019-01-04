#ifndef SHOPPING_MENU_HPP_INCLUDED
#define SHOPPING_MENU_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include <vector>

class cShoppingMenu {

public:
    static constexpr auto NO_ITEM_ID = -1;

    cShoppingMenu(const sf::RenderWindow& window,
                  const sf::Texture& frameTexture,
                  const std::vector<const sf::Texture*>& itemsTextures);

    void startCreatingItem(unsigned int id, unsigned int time);
    int pickUpItemId();

    void display(sf::RenderWindow& window) const;

    int getClickedItemId(const sf::RenderWindow& window) const;

private:
    std::vector<sf::Sprite> m_frames;
    std::vector<sf::Sprite> m_items;

    int m_creating_item;

    unsigned int m_start_time;
    unsigned int m_creating_time;
};

#endif // SHOPPING_MENU_HPP_INCLUDED
