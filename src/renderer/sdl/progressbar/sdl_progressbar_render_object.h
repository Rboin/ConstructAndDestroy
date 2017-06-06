//
// Created by Sander on 18-5-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_PROGRESSBAR_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_PROGRESSBAR_RENDER_OBJECT_H


#include <sdl/image/sdl_image_render_object.h>
#include "sdl/sdl_render_object.h"

class SDL_ProgressbarRenderObject : public SDL_RenderObject {
private:
    float _progress;
    SDL_Color _color;
    void draw(SDLRenderer *);

public:
    SDL_ProgressbarRenderObject(const vec2 &position, const vec2 &size, SDL_Color color, sdl_data *data);

    ~SDL_ProgressbarRenderObject();

    void render(SDLRenderer *, const mat2 &) override;

    void set_progress(float progress);
};


#endif //CONSTRUCT_AND_DESTROY_SDL_PROGRESSBAR_RENDER_OBJECT_H
