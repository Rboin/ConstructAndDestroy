//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_WINDOW_H
#define CONSTRUCT_AND_DESTROY_SDL_WINDOW_H

#include "event/event_dispatcher.h"
#include "sdl/sdl_ui_component.h"
#include "sdl/sdl_render_object.h"

struct SDL_Window;

class SDLWindow : public SDL_UIComponent {
private:
    SDLRenderer *_renderer;
    EventDispatcher<SDL_UIComponent, sdl_mouse_event_data> *_mouse_event_dispatcher;
    EventDispatcher<SDL_UIComponent, sdl_key_event_data> *_key_event_dispatcher;
    SDL_Window *_sdl_window;
public:
    explicit SDLWindow(SDL_RenderObject *);

    explicit SDLWindow(SDL_RenderObject *, SDL_Window *);

    explicit SDLWindow(SDL_RenderObject *, SDL_Window *, SDLRenderer *);

    explicit SDLWindow(SDL_RenderObject *, SDL_Window *, SDLRenderer *,
                       EventDispatcher<SDL_UIComponent, sdl_mouse_event_data> *);

    explicit SDLWindow(SDL_RenderObject *, SDL_Window *, SDLRenderer *,
                       EventDispatcher<SDL_UIComponent, sdl_mouse_event_data> *,
                       EventDispatcher<SDL_UIComponent, sdl_key_event_data> *);

    virtual ~SDLWindow() override;

    int show();

    void render(SDLRenderer *t, float d) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_WINDOW_H
