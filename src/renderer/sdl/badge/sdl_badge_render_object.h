//
// Created by Jeroen on 5/24/2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_BADGE_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_BADGE_RENDER_OBJECT_H

#include <string>
#include "sdl/sdl_render_object.h"
#include "types.h"

class sdl_text;

class SDL_UI_RenderTextObject;

class SDL_Renderer;

class SDL_BadgeRenderObject : public SDL_RenderObject {
protected:
    int _count;
    int _radius;
    vec2 _center;
    sdl_text *_textdata;
    SDL_UI_RenderTextObject *_text;
public:
    SDL_BadgeRenderObject(const vec2 &position, const vec2 &size, sdl_data *color, int radius);

    ~SDL_BadgeRenderObject();

    //void update_color(sdl_data *color);
};

#endif //CONSTRUCT_AND_DESTROY_SDL_BADGE_RENDER_OBJECT_H
