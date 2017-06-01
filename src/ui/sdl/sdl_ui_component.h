//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H
#define CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H

#include "sdl/sdl_renderer.h"
#include "component/ui_component.h"

class SDL_RenderObject;

struct sdl_data;
struct sdl_mouse_event_data;
struct sdl_key_event_data;

class SDL_UIComponent : public UIComponent<SDLRenderer, sdl_data, SDL_Texture, sdl_mouse_event_data, sdl_key_event_data> {

public:
    explicit SDL_UIComponent(SDL_RenderObject *);

    virtual ~SDL_UIComponent() override;

    /*!
     * The base rendering function. Do not modify this, instead create a derived class with custom rendering.
     * @return SDL_Texture *
     */
    void render(SDLRenderer *t, float d) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H
