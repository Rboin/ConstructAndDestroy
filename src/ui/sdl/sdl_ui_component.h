//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H
#define CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H

#include "sdl/sdl_ui_render_object.h"
#include "component/ui_component.h"

class SDL_UIComponent : public UIComponent<SDL_Renderer, sdl_ui_data, SDL_Texture, mouse_event_data> {
public:
    explicit SDL_UIComponent(SDL_UI_RenderObject *);

    SDL_Texture *render(Renderer<SDL_Renderer> *, float) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H
