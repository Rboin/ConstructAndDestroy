//
// Created by Sander on 3-4-2017.
//

#include <SDL_image.h>
#include <cstdio>
#include "texture_manager.h"
#include "texture_types.h"


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


SDL_Texture *TextureManager::loadTexture(std::string path) {
    path = "res/textures/" + path;
    return IMG_LoadTexture(_renderer, path.c_str());
}


//TODO: remove this and replace by above method
SDL_Texture *TextureManager::GetTexture(TextureTypes tt) {
    std::string texture;

    if (tt == IRONMINETEXTURE) { texture = "ironmine.png"; } //to make selected
    else if (tt == MINERTEXTURE) { texture = "miner.png"; } //to make selected
    else if (tt == TREETEXTURE) { texture = "tree.png"; }
    else if (tt == LUMBERJACKTEXTURE) { texture = "lumberjack.png"; } //to make selected
    else if (tt == WAREHOUSETEXTURE) { texture = "warehouse.png"; }
    else if (tt == WORLDTEXTURE) { texture = "world.png"; }
    else if (tt == RESTAURANTTEXTURE) { texture = "restaurant.png"; }
    else if (tt == CAMPFIRETEXTURE) { texture = "campfire.png"; }
    else if (tt == BOWTEXTURE ) {texture = "bow.png";}
    else if (tt == AXETEXTURE ) {texture = "axe.png";}
    else if (tt == SEL_AXETEXTURE){texture = "sel_axe.png";}
    else if (tt == SEL_BOWTEXTURE){texture = "sel_bow.png";}
    else if (tt == SEL_LUMBERJACKTEXTURE){texture = "sel_lumberjack.png";}
    else if (tt == SEL_MINERTEXTURE){texture = "sel_miner.png";}

    return loadTexture(texture);
}

