//
// Created by robin on 5/16/17.
//

#include <iostream>
#include "wave_start.h"

void WaveStart::enter(Wave *t) {
    std::cout << "WaveStart::enter()..." << std::endl;
}

void WaveStart::execute(Wave *t) {
    std::cout << "WaveStart::execute()..." << std::endl;
}

void WaveStart::exit(Wave *t) {
    std::cout << "WaveStart::exit()..." << std::endl;
}
