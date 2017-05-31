//
// Created by Sander on 20-4-2017.
//

#include "player_manager.h"
#include "player.h"

PlayerManager *PlayerManager::_instance = nullptr;

PlayerManager::~PlayerManager() {
    for (std::map<int, Player *>::iterator it = _players.begin(); it != _players.end(); it++) {
        delete (it->second);
    }
    _players.clear();
    _instance = nullptr;
}

PlayerManager::PlayerManager() {
    _players = std::map<int, Player *>();
}

void PlayerManager::setup(int p) {
    if (_players.size() == 0) {
        for (int i = 0; i < p; i++) {
            _players.insert(std::make_pair(i, new Player(i)));
        }
    }
}

PlayerManager *PlayerManager::get_instance() {
    if (!_instance)
        _instance = new PlayerManager();
    return _instance;
}

Player *PlayerManager::get_player(int player) {
    return _players[player];
}

std::vector<int> PlayerManager::get_player_ids() {
    std::vector<int> v;
    for (std::map<int, Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
        v.push_back(it->first);
    }
    return v;
}
