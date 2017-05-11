//
// Created by Sander on 3-4-2017.
//

#ifndef C_AND_D_PROJECT_TEXTURE_MANAGER_H
#define C_AND_D_PROJECT_TEXTURE_MANAGER_H


#include <SDL_render.h>
#include <string>
#include "texture_types.h"

class TextureManager {
private:
    TextureManager();
    SDL_Renderer *_renderer;
    static TextureManager *_instance;
public:
    static TextureManager *get_instance();

    void setup(SDL_Renderer *);

    SDL_Texture* get_texture(TextureTypes);

    SDL_Texture* load_texture(std::string);
};


#endif //C_AND_D_PROJECT_TEXTURE_MANAGER_H
