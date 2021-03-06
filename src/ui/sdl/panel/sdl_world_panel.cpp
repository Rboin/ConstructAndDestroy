//
// Created by robin on 4/26/17.
//

#include <cmath>
#include "sdl_world_panel.h"
#include "settings.h"
#include "camera/camera_manager.h"
#include "world/world.h"

SDLWorldPanel::SDLWorldPanel(SDL_RenderObject *r) : SDLPanel(r) {
    _current_world = nullptr;
    dragging = false;
}

void SDLWorldPanel::set_world(World *world) {
    _current_world = world;
}

void SDLWorldPanel::render(SDLRenderer *renderer, mat2 &transformations, float d) {
    _current_world->update(d);
    CameraManager::get_instance()->update(d);
    renderer->set_render_target(renderer->get_world_buffer());
    CameraManager::get_instance()->render<World, SDLRenderer, mat2>(renderer, _current_world, &World::render);

    // Draw rectangle if dragging
    if (dragging) {
        this->draw_selection_rect((int) start_drag.x, (int) start_drag.y,
                                  (int) end_drag.x, (int) end_drag.y,
                                  renderer);
    }
    for(unsigned int i = 0; i < children.size(); i++) {
        children[i]->render(renderer, transformations, d);
    }
}

void SDLWorldPanel::draw_selection_rect(int start_x, int start_y, int end_x, int end_y, SDLRenderer *_renderer) {

    SDL_SetRenderDrawColor(_renderer->get_engine(), 255, 0, 0, 255);
    SDL_Rect *rect = new SDL_Rect;

    //starting coordinates from the rectangle
    rect->x = start_x;
    rect->y = start_y;

    //coordinates the lines of the rectangle end.
    rect->h = std::abs(start_y - end_y);

    //if rect's origin coordinates are greater then end coordinates use * -1 so the height/weight is negative.
    if (start_y > end_y) { rect->h = rect->h * -1; }

    rect->w = std::abs(end_x - start_x);
    if (start_x > end_x) { rect->w = rect->w * -1; }

    SDL_RenderDrawRect(_renderer->get_engine(), rect);
}

SDLWorldPanel::~SDLWorldPanel() {
    clear_components();
    _current_world = nullptr;
}

void SDLWorldPanel::resize(const vec2 &v) {
    representation->set_size(v);
    resize_children(v);
}
