//
// Created by Sander on 12-3-2017.
//

#include "graph_manager.h"
#include "graph.h"

GraphManager *GraphManager::_instance = nullptr;

GraphManager::GraphManager() {
    graph = nullptr;
}

GraphManager::~GraphManager() {
    if(graph){
        delete graph;
    }
    _instance = nullptr;
}

void GraphManager::setup(vec2 world_size) {
    if(!graph){
        graph = new Graph(world_size);
    }
}

GraphManager *GraphManager::get_instance() {
    if (!_instance)
        _instance = new GraphManager();
    return _instance;
}