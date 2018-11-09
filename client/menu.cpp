#include "menu.hpp"
#include "engine.hpp"
#include "resources_manager.hpp"
#include "network_data.hpp"
#include <iostream>

extern Client_Engine engine;
extern Resources_Manager resources_manager;
extern Network_Data server;

void Menu::init(const sf::RenderWindow& window)
{
    main_menu(window);
}

void Menu::clear()
{
    m_state = 0;
    m_buttons.clear();
    m_textboxes.clear();
    m_rectangles.clear();
    m_texts.clear();
}

void Menu::main_menu(const sf::RenderWindow& window)
{
    clear();
    m_state = 1;
    
    const int BUTTONS_POSITION_X = window.getSize().x / 2 - STANDARD_BUTTON_SIZE.x / 2;

    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 64.0f),  L"CONNECT");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 128.0f), L"OPTIONS");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 192.0f), L"AUTHORS");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 256.0f), L"QUIT");
}

void Menu::connect_menu(const sf::RenderWindow& window)
{
    clear();
    m_state = 2;
    
    const int BUTTONS_POSITION_X = window.getSize().x / 2 - STANDARD_BUTTON_SIZE.x / 2;

    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 64.0f),  server.get_ip().toString());
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 128.0f), L"OPTIONS");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 192.0f), L"BACK");
}

void Menu::options_menu(const sf::RenderWindow& window)
{
    clear();
    m_state = 3;
    
    const int BUTTONS_POSITION_X = window.getSize().x / 2 - STANDARD_BUTTON_SIZE.x / 2;

    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 64.0f),  L"FULLSCREEN");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 128.0f), L"WINDOWED");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 192.0f), L"BACK");
}

void Menu::authors_menu(const sf::RenderWindow& window)
{
    clear();
    m_state = 4;

    m_texts.emplace_back(L"Kacper Piwiński", resources_manager.get_font());
    m_texts.emplace_back(L"Radosław Wojdak", resources_manager.get_font());
    m_texts[1].move(0, 30);
    
    const int BUTTONS_POSITION_X = window.getSize().x / 2 - STANDARD_BUTTON_SIZE.x / 2;

    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 192.0f), L"BACK");
}

void Menu::lobby_menu(const sf::RenderWindow& window)
{
    clear();
    m_state = 5;

    const int CHAT_WINDOW_MARGIN = 32;
    const int BUTTONS_WINDOW_MARGIN = 32;
    const int SPACE_BETWEEN_CHAT_AND_TEXTBOX = 16;
    const int SPACE_BETWEEN_CHAT_AND_BUTTONS = 32;

    //CHAT
    const sf::Vector2i CHAT_SIZE(
        window.getSize().x - SPACE_BETWEEN_CHAT_AND_BUTTONS - STANDARD_BUTTON_SIZE.x - CHAT_WINDOW_MARGIN - BUTTONS_WINDOW_MARGIN,
        window.getSize().y - CHAT_WINDOW_MARGIN * 2 - SPACE_BETWEEN_CHAT_AND_TEXTBOX - STANDARD_TEXTBOX_SIZE.y
    );
    const sf::Vector2f CHAT_POSITION(window.getSize().x - CHAT_SIZE.x - CHAT_WINDOW_MARGIN, CHAT_WINDOW_MARGIN);

    m_rectangles.emplace_back(sf::Vector2f(CHAT_SIZE));
    m_rectangles[0].setPosition(CHAT_POSITION);

    m_textboxes.emplace_back(
        sf::Vector2f(CHAT_POSITION.x, CHAT_POSITION.y + CHAT_SIZE.y + SPACE_BETWEEN_CHAT_AND_TEXTBOX), 
        sf::Vector2f(CHAT_SIZE.x, STANDARD_TEXTBOX_SIZE.y)
    );

    //BUTTONS
    const sf::Vector2f BACK_BUTTON_POSITION(
        BUTTONS_WINDOW_MARGIN,
        window.getSize().y - STANDARD_BUTTON_SIZE.y - BUTTONS_WINDOW_MARGIN
    );
    
    m_buttons.emplace_back(BACK_BUTTON_POSITION, L"BACK");
}

void Menu::mouse_click(const sf::RenderWindow& window)
{
    //TEXTBOXES
    for(TextBox& tb: m_textboxes)
    {
        if(tb.is_pressed(window))
            tb.mark();
        else
            tb.unmark();
    }

    //BUTTONS
    sf::Uint8 button_id = get_button_id_from_press(window);
    switch(m_state)
    {
    case 1://main menu
    {
        switch(button_id)
        {
        case 0://connect
        {
            connect_menu(window);
            break;
        }
        case 1://options
        {
            options_menu(window);
            break;
        }
        case 2://authors
        {
            authors_menu(window);
            break;
        }
        case 3://quit
        {
            engine.quit_engine();
            break;
        }
        }//end switch
        break;
    }
    case 2://connect menu
    {
        switch(button_id)
        {
        case 0://IpAddress
        {
            m_buttons[0].set_string(std::wstring());
            break;
        }
        case 1://connect
        {
            //server.set_ip(sf::IpAddress(m_buttons[0].get_string()));
            //engine.connect_to_lobby();
            lobby_menu(window);
            break;
        }
        case 2://back
        {
            main_menu(window);
            break;
        }
        }//end switch
        break;
    }
    case 3://options
    {
        switch(button_id)
        {
        case 0://fullscreen
        {
            engine.setup_window(true);
            break;
        }
        case 1://windowed
        {
            engine.setup_window(false);
            break;
        }
        case 2://back
        {
            main_menu(window);
            break;
        }
        }//end switch
        break;
    }
    case 4://authors menu
    {
        switch(button_id)
        {
        case 0://back
        {
            main_menu(window);
            break;
        }
        }//end switch
        break;
    }
    case 5://lobby menu
    {
        switch(button_id)
        {
        case 0://back
        {
            connect_menu(window);
            break;
        }
        }
        break;
    }
    }//end switch
}

void Menu::mouse_move(const sf::RenderWindow& window)
{
    for(Button& button : m_buttons)
    {
        if (button.is_mouse_on(window))
            button.mark();
        else
            button.unmark();
    }
}

void Menu::text_entered(const sf::Event& event)
{
    if(m_state == 2)
    {
        std::wstring str(m_texts[0].getString());
        str.push_back(event.text.unicode);
        m_texts[0].setString(str);
    }

    if(m_state == 5)
    {
        const int RETURN_CODE = 13;
        const int TEXT_CHAT_MARGIN = 4;
        const int SPACE_FOR_MESSAGE = 16;

        if(m_textboxes[0].is_marked() && event.text.unicode == RETURN_CODE)
        {
            m_texts.emplace_back(m_textboxes[0].get_string(), resources_manager.get_font());
            sf::Text* text_ptr = &m_texts[m_texts.size() - 1];

            text_ptr->setFillColor(sf::Color::Black);
            text_ptr->setCharacterSize(14U);

            text_ptr->setPosition(m_rectangles[0].getPosition());
            text_ptr->move(
                TEXT_CHAT_MARGIN,
                TEXT_CHAT_MARGIN + (m_texts.size() - 1) * SPACE_FOR_MESSAGE
            );
            
            m_textboxes[0].set_string("");
        }
    }

    //TEXTBOXES
    for(TextBox& tb: m_textboxes)
    {
        if(tb.is_marked())
            tb.enter_text(event.text.unicode);
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    for(sf::RectangleShape& rect: m_rectangles)
        window.draw(rect);

    for(sf::Text& text: m_texts)
        window.draw(text);

    for (TextBox& tb: m_textboxes)
        tb.display(window);

    for(Button& button: m_buttons)
        button.display(window);
}

sf::Uint8 Menu::get_button_id_from_press(const sf::RenderWindow& window) const
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
        if(m_buttons[i].is_pressed(window))
            return i;

    return m_buttons.size();
}

void Menu::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_buttons) << L'\n'
               << sizeof(m_texts)   << L'\n'
               << sizeof(m_state)   << L'\n';
}
