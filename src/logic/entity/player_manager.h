//
// Created by Sander on 20-4-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_PLAYER_MANAGER_H
#define CONSTRUCT_AND_DESTROY_PLAYER_MANAGER_H

#include <map>

class Player;

class PlayerManager {
private:
    PlayerManager();
    static PlayerManager *_instance;
    std::map<int, Player*> _players;
public:
    static PlayerManager *get_instance();
    /*!
     * Creates the amount of players for the game
     * @param players - Amount of players to create
     */
    void setup(int players);
    /*!
     * @param player player to return
     * @return a certain player
     */
    Player* get_player(int player);
};


#endif //CONSTRUCT_AND_DESTROY_PLAYER_MANAGER_H
