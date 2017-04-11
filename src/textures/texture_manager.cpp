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
    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        std::string s = ("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        printf(s.data());
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
        if (newTexture == NULL) {
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

SDL_Texture *TextureManager::GetTexture(TextureTypes tt) {
    std::string texture;

    if (tt == IRONMINETEXTURE) { texture = "ironmine.png"; }
    else if (tt == MINERTEXTURE) { texture = "miner.png"; }
    else if (tt == TREETEXTURE) { texture = "tree.png"; }
    else if (tt == LUMBERJACKTEXTURE) { texture = "lumberjack.png"; }
    else if (tt == WAREHOUSETEXTURE) { texture = "warehouse.png"; }
    else if (tt == WORLDTEXTURE) { texture = "world.png"; }
    else if (tt == RESTAURANTTEXTURE) { texture = "restaurant.png"; }
    else if (tt == CAMPFIRETEXTURE) { texture = "campfire.png"; }
    else if (tt == BOWTEXTURE ) {texture = "bow.png";}
    else if (tt == AXETEXTURE ) {texture = "axe.png";}

    return loadTexture("res/textures/"+texture);
}