//
// Created by robin on 5/10/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_RENDERER_H
#define CONSTRUCT_AND_DESTROY_SDL_RENDERER_H

#include <SDL2/SDL.h>
#include "types.h"
#include "vector.h"
#include "renderer.h"

class SDLRenderer : public Renderer<SDL_Renderer> {
private:
    vec2 _window_size;
    SDL_Texture *_back_buffer_ui, *_back_buffer_world, *_back_buffer_final;

    void init_textures();
public:
    explicit SDLRenderer(SDL_Renderer *engine, vec2);

    ~SDLRenderer();

    void draw_to_buffer(SDL_Texture *, SDL_Rect *);

    void draw_to_buffer(SDL_Texture *, SDL_Texture *, SDL_Rect *);

    SDL_Texture *get_ui_buffer();

    SDL_Texture *get_world_buffer();

    void set_render_target(SDL_Texture *);

    SDL_Texture *create_texture(int, int, SDL_TextureAccess access = SDL_TEXTUREACCESS_TARGET);

    void resize(const vec2 &);

    void clear() override;

    void show() override;

};


#endif //CONSTRUCT_AND_DESTROY_SDL_RENDERER_H
