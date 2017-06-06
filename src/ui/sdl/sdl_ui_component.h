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
protected:
    vec2 old_window_size;
public:
    explicit SDL_UIComponent(SDL_RenderObject *);

    virtual ~SDL_UIComponent() override;

    /*!
     * The base rendering function. Do not modify this, instead create a derived class with custom rendering.
     * @return SDL_Texture *
     */
    virtual void render(SDLRenderer *t, mat2 &, float d) override;

    virtual void resize(const vec2 &) override;

    void resize_children(const vec2 &);
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UI_COMPONENT_H
