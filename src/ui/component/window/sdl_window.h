//
// Created by robin on 4/23/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_WINDOW_H
#define CONSTRUCT_AND_DESTROY_SDL_WINDOW_H

#include "event/event_dispatcher.h"
#include "component/sdl/sdl_ui_component.h"
#include "sdl/sdl_ui_render_object.h"

struct SDL_Window;

class SDLWindow : public SDL_UIComponent {
private:
    Renderer<SDL_Renderer> *_renderer;
    EventDispatcher<mouse_event_data> *_mouse_event_dispatcher;
    EventDispatcher<key_event_data> *_key_event_dispatcher;
    SDL_Window *_sdl_window;
public:
    explicit SDLWindow(SDL_UI_RenderObject *);

    explicit SDLWindow(SDL_UI_RenderObject *, SDL_Window *);

    explicit SDLWindow(SDL_UI_RenderObject *, SDL_Window *, EventDispatcher<mouse_event_data> *);

    explicit SDLWindow(SDL_UI_RenderObject *, SDL_Window *, EventDispatcher<mouse_event_data> *,
                       EventDispatcher<key_event_data> *);

    explicit SDLWindow(SDL_UI_RenderObject *, SDL_Window *, EventDispatcher<mouse_event_data> *,
                       EventDispatcher<key_event_data> *, Renderer<SDL_Renderer> *);

    int show();

    SDL_Texture *render(Renderer<SDL_Renderer> *renderer, float delta) override;
};


#endif //CONSTRUCT_AND_DESTROY_SDL_WINDOW_H
