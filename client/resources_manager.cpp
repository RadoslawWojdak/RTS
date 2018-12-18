#include "resources_manager.hpp"
#include <iostream>

void Resources_Manager::load_resources()
{
    m_font.loadFromFile("Fonts/font.ttf");
    m_textures.resize(12);//number of textures
    m_textures[0].loadFromFile("Textures/cb.bmp");
    m_textures[1].loadFromFile("Textures/Czolg.png");
    m_textures[2].loadFromFile("Textures/Drzewko.png");
    m_textures[3].loadFromFile("Textures/Drzewko2.png");
    m_textures[4].loadFromFile("Textures/Grunt.png");
    m_textures[5].loadFromFile("Textures/Grunt2.png");
    m_textures[6].loadFromFile("Textures/Test.png");
    m_textures[7].loadFromFile("Textures/Trawa1.png");
    m_textures[8].loadFromFile("Textures/Trawa2.png");
    m_textures[9].loadFromFile("Textures/Trawa3.png");
    m_textures[10].loadFromFile("Textures/MenuBackground1.png");
    m_textures[11].loadFromFile("Textures/Zasoby.png");
    m_textures[12].loadFromFile("Textures/FabrykaCzolgow.png");
}

const sf::Font& Resources_Manager::get_font() const
{
    return m_font;
}

const sf::Texture& Resources_Manager::get_texture(sf::Uint8 id) const
{
    return m_textures[id];
}

void Resources_Manager::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_font)<< L'\n'
               << sizeof(m_textures) << L'\n';
}
