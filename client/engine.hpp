#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include "../common/network_player.hpp"
#include "building_shop.hpp"
#include "deposit.hpp"
#include "graphical_unit.hpp"
#include "graphical_statistics.hpp"
#include "graphical_factory.hpp"
#include "house.hpp"
#include "infantry_factory.hpp"
#include "tank_factory.hpp"
#include <deque>
#include <memory>

class Client_Engine
{
    //sort from largest to smallest!
    std::deque <std::unique_ptr <Tank_Factory> > tankFactories;
    std::deque <std::unique_ptr <Infantry_Factory> > infantryFactories;
    std::deque <std::unique_ptr <cHouse> > houses;
    std::deque <std::unique_ptr <Graphical_Unit> > units;
    std::deque <cDeposit> deposits;
    std::deque <Network_Player> players;//80
    sf::Packet packet_to_send;//56
    sf::Packet received_packet;//56
    sf::UdpSocket socket;//48
    sf::Clock clock;//8
    sf::Time time;//8
    std::unique_ptr<Graphical_Statistics> m_game_stats;
    std::unique_ptr<cBuildingShop> buildingShop;
    sf::Sprite keepingObjectSprite;
    bool menu_loop = true;//1
    bool lobby_loop = false;//1
    bool game_loop = false;//1
    bool marked_building = false;
    bool keep_building = false;

public:
    void init();
    void init_game();

    void setup_window(bool fullscreen);
    void return_to_menu();
    void connect_to_lobby();
    void quit_engine();

    void menu_receive_inputs();
    void lobby_receive_inputs();
    void game_receive_inputs();

    void menu_logic();
    void lobby_logic();
    void game_logic();

    void menu_draw_frame();
    void lobby_draw_frame();
    void game_draw_frame();

    void receive_packets();
    void send_packets();

    bool get_menu_loop() const;
    bool get_lobby_loop() const;
    bool get_game_loop() const;

    void debug_show_size() const;

private:
    void set_all_players_ready_status(bool status);

    void mark_covered_objects(const sf::RectangleShape& rect);
    void unmark_objects();
    void point_destination(const sf::Vector2u& target);
    void move_units();

    void start_creating(Tank_Factory& factory);
    void start_creating(Infantry_Factory& factory);
    void start_creating(cBuildingShop& shop);

    void adjust_keeping_object();
};

#endif // ENGINE_HPP_INCLUDED
