#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include "../common/network_player.hpp"
#include "graphical_unit.hpp"
#include <deque>
#include <memory>

class Client_Engine
{
    //sort from largest to smallest!
    std::deque <std::unique_ptr <Graphical_Unit> > units;//80
    std::deque <Network_Player> players;//80
    sf::Packet packet_to_send;//56
    sf::Packet received_packet;//56
    sf::UdpSocket socket;//48
    sf::Clock clock;//8
    sf::Time time;//8
    bool menu_loop = true;//1
    bool lobby_loop = false;//1
    bool game_loop = false;//1

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
};

#endif // ENGINE_HPP_INCLUDED
