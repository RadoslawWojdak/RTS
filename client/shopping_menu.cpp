#include "shopping_menu.hpp"

cShoppingMenu::cShoppingMenu(const sf::RenderWindow& window,
                             const sf::Texture& frameTexture,
                             const std::vector<const sf::Texture*>& itemsTextures) {

    const auto LEFT_FRAME_POS_X = frameTexture.getSize().x / 2.0f;
    const auto FRAME_POS_Y = window.getSize().y - frameTexture.getSize().y / 2.0f;
    for (auto i = 0; i < itemsTextures.size(); i++) {
        m_frames.emplace_back(frameTexture);
        m_frames[i].setOrigin(frameTexture.getSize().x / 2.0f, frameTexture.getSize().y / 2.0f);
        m_frames[i].setPosition(LEFT_FRAME_POS_X + i * frameTexture.getSize().x, FRAME_POS_Y);

        m_items.emplace_back(*itemsTextures[i]);
        m_items[i].setOrigin(itemsTextures[i]->getSize().x / 2.0f, itemsTextures[i]->getSize().y / 2.0f);
        m_items[i].setPosition(LEFT_FRAME_POS_X + i * frameTexture.getSize().x, FRAME_POS_Y);
    }

    m_creating_item = NO_ITEM_ID;
}

void cShoppingMenu::startCreatingItem(unsigned int id, unsigned int time) {
    if (m_creating_item == NO_ITEM_ID) {
        m_start_time = sf::Clock().getElapsedTime().asMilliseconds();
        m_creating_item = time;
        m_creating_item = id;
    }
}

int cShoppingMenu::pickUpItemId() {
    if (sf::Clock().getElapsedTime().asMilliseconds() - m_start_time >= m_creating_time) {
        auto item = m_creating_item;
        m_creating_item = NO_ITEM_ID;
        return item;
    }
    return NO_ITEM_ID;
}

void cShoppingMenu::display(sf::RenderWindow& window) const {
    for (auto& frame : m_frames) {
        window.draw(frame);
    }
    for (auto& item : m_items) {
        window.draw(item);
    }
}

int cShoppingMenu::getClickedItemId(const sf::RenderWindow& window) const {
    for (auto i = 0; i < m_frames.size(); i++) {
        if (m_frames[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            return i;
        }
    }
    return NO_ITEM_ID;
}
