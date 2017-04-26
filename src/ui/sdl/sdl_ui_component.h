//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H
#define CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H

#include "component/ui_component.h"
#include "event/event_types.h"
#include "sdl/sdl_render_object.h"

class SDL_UIComponent : public UIComponent<SDL_Renderer, sdl_data, SDL_Texture, mouse_event_data> {
public:
    explicit SDL_UIComponent(SDL_RenderObject *);

    SDL_Texture *render(Renderer<SDL_Renderer> *, float) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H
