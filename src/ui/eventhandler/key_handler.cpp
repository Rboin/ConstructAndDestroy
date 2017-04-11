//
// Created by robin on 3/21/17.
//

#include <SDL2/SDL_keycode.h>
#include <iostream>
#include <graph/graph_manager.h>
#include "key_handler.h"
#include "graph/graph.h"


bool KeyHandler::handle(key_event_data data) {
    std::cout << data.data << std::endl;

    //115 = 'S'
    if(data.data == 115){
        data.graph->set_show_graph();
    }
    return false;
}
