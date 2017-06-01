//
// Created by robin on 5/10/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RENDERER_H
#define CONSTRUCT_AND_DESTROY_SDL_RENDERER_H

#include <SDL2/SDL.h>
#include "renderer.h"

class SDLRenderer : public Renderer<SDL_Renderer> {
private:
    SDL_Texture *_back_buffer;
public:
    explicit SDLRenderer(SDL_Renderer *engine);

    ~SDLRenderer();

    void draw_to_back_buffer(SDL_Texture *, SDL_Rect *);

    SDL_Texture *get_back_buffer();

    SDL_Texture *create_texture(int, int, SDL_TextureAccess access = SDL_TEXTUREACCESS_TARGET);

    void clear() override;

    void show() override;

};


#endif //CONSTRUCT_AND_DESTROY_SDL_RENDERER_H
