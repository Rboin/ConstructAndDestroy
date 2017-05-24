//
// Created by robin on 4/26/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_BUTTON_H
#define CONSTRUCT_AND_DESTROY_SDL_BUTTON_H

#include "sdl/sdl_ui_component.h"
#include "sdl/text/sdl_render_text_object.h"

class SDLButton : public SDL_UIComponent {
public:
    SDLButton(SDL_RenderObject *);

};

#endif //CONSTRUCT_AND_DESTROY_SDL_BUTTON_H
