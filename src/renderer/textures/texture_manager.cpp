//
// Created by Sander on 3-4-2017.
//

#include <SDL_image.h>
#include <cstdio>
#include "texture_manager.h"

TextureManager *TextureManager::_instance = nullptr;

TextureManager::TextureManager() {
    _renderer = nullptr;
}

void TextureManager::setup(SDL_Renderer *renderer) {
    if (!_renderer) {
        _renderer = renderer;
    }
}

TextureManager *TextureManager::get_instance() {
    if (!_instance)
        _instance = new TextureManager();
    return _instance;
}


SDL_Texture *TextureManager::load_texture(std::string path) {
    path = "res/textures/" + path;
    int width, height;

    // Load the image into a texture
    SDL_Texture *image_texture = IMG_LoadTexture(_renderer, path.c_str());
    // Don't blend the image together, if you do so,
    // it will try to combine with what is already on the texture's position.
    SDL_SetTextureBlendMode(image_texture, SDL_BLENDMODE_NONE);

    // Get width and height
    SDL_QueryTexture(image_texture, NULL, NULL, &width, &height);

    // Create new texture with correct access and format.
    // We need this to draw textures on top of one another.
    SDL_Texture *result_texture = SDL_CreateTexture(_renderer,
                                                    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                                    width, height);
    SDL_SetTextureBlendMode(result_texture, SDL_BLENDMODE_BLEND);

    // Copy image onto resulting texture
    SDL_SetRenderTarget(_renderer, result_texture);
    SDL_RenderCopy(_renderer, image_texture, NULL, NULL);
    SDL_SetRenderTarget(_renderer, NULL);

    // Destroy loaded image texture
    SDL_DestroyTexture(image_texture);
    return result_texture;
}


//TODO: remove this and replace by above method
SDL_Texture *TextureManager::get_texture(TextureTypes tt) {
    std::string texture;

    if (tt == IRONMINETEXTURE) { texture = "ironmine.png"; } //to make selected
    else if (tt == MINERTEXTURE) { texture = "miner.png"; } //to make selected
    else if (tt == TREETEXTURE) { texture = "tree.png"; }
    else if (tt == LUMBERJACKTEXTURE) { texture = "lumberjack.png"; } //to make selected
    else if (tt == WAREHOUSETEXTURE) { texture = "warehouse.png"; }
    else if (tt == CASTLETEXTURE) { texture = "castle.png"; }
    else if (tt == WORLDTEXTURE) { texture = "world.png"; }
    else if (tt == BOWTEXTURE) { texture = "bow.png"; }
    else if (tt == AXETEXTURE) { texture = "axe.png"; }
    else if (tt == SEL_AXETEXTURE) { texture = "sel_axe.png"; }
    else if (tt == SEL_BOWTEXTURE) { texture = "sel_bow.png"; }
    else if (tt == SEL_LUMBERJACKTEXTURE) { texture = "sel_lumberjack.png"; }
    else if (tt == SEL_MINERTEXTURE) { texture = "sel_miner.png"; }

    return load_texture(texture);
}

