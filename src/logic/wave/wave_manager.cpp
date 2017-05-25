//
// Created by robin on 5/24/17.
//

#include "settings.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "wave_manager.h"
#include "wave.h"

WaveManager *WaveManager::_instance = nullptr;

WaveManager::WaveManager() {
    _wave = nullptr;
}

WaveManager *WaveManager::get_instance() {
    if(!_instance) {
        _instance = new WaveManager();
    }
    return _instance;
}

void WaveManager::set_wave(Wave *w) {
    if(_wave) {
        delete _wave;
    }
    _wave = w;
}

void WaveManager::reset() {
    reset_computer();
    reset_player();

    _wave->reset();
}

void WaveManager::reset_player() {
    Player *player = PlayerManager::get_instance()->get_player(player_id);
    player->clear_units();
}

void WaveManager::reset_computer() {
    Player *computer = PlayerManager::get_instance()->get_player(computer_id);
    computer->clear_units();
}
