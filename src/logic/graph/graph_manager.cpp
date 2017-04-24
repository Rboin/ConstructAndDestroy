//
// Created by Sander on 12-3-2017.
//

#include "graph_manager.h"
#include "graph.h"

GraphManager *GraphManager::instance = nullptr;

GraphManager::GraphManager() {
    graph = nullptr;
}

GraphManager::~GraphManager() {
    if(graph){
        delete graph;
    }
}

void GraphManager::setup(vec2 world_size) {
    if(!graph){
        graph = new Graph(world_size);
    }
}

GraphManager *GraphManager::get_instance() {
    if (!instance)
        instance = new GraphManager();
    return instance;
}