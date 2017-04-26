//
// Created by robin on 4/26/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_BUTTON_H
#define CONSTRUCT_AND_DESTROY_SDL_BUTTON_H

#include <sdl/ui/sdl_ui_render_text_object.h>
#include <sdl/sdl_ui_component.h>

class SDLButton : public SDL_UIComponent {
public:
    SDLButton(SDL_UI_RenderTextObject *);

};

#endif //CONSTRUCT_AND_DESTROY_SDL_BUTTON_H
