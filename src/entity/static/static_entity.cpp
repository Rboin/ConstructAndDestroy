//
// Created by Sander on 1-3-2017.
//

#include <graph/graph_manager.h>
#include "static_entity.h"
#include "graph/graph.h"
#include "matrix.h"
#include "entity/entity_types.h"

StaticEntity::StaticEntity(const mesh *base, vec2 position, float mass, TextureTypes texturetype) : BaseEntity(STATIC, base, position, mass, texturetype) {
    update_render_mesh(mat2::translate(_position));

    //remove edges from graph
    GraphManager *gm = GraphManager::get_instance();
    gm->setup({800, 600});
    gm->graph->remove_edge(position);

};