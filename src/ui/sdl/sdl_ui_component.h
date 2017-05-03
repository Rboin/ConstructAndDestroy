//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H
#define CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H

#include "component/ui_component.h"
#include "sdl/sdl_render_object.h"
#include "sdl/event/sdl_event_types.h"
class SDL_UIComponent : public UIComponent<SDL_Renderer, sdl_data, SDL_Texture, sdl_mouse_event_data> {
public:
    explicit SDL_UIComponent(SDL_RenderObject *);

    bool dragging;
    vec2 start_drag;
    vec2 end_drag;

    SDL_Texture *render(Renderer<SDL_Renderer> *, float) override;
    void draw_selection_rect(int start_x, int start_y, int end_x, int end_y, SDL_Renderer* _renderer);
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H
