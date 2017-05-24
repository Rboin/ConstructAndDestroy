//
// Created by robin on 5/24/17.
//

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

}
