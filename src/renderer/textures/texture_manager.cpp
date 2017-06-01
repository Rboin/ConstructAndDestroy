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

TextureManager::~TextureManager() {
    SDL_DestroyRenderer(_renderer);
    _instance = nullptr;
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

    // Load the image into a texture
    SDL_Texture *image_texture = IMG_LoadTexture(_renderer, path.c_str());
    return image_texture;
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
    else if (tt == SEL_LUMBERJACKTEXTURE) { texture = "sel_lumberjack.png"; }
    else if (tt == SEL_MINERTEXTURE) { texture = "sel_miner.png"; }

    return load_texture(texture);
}
