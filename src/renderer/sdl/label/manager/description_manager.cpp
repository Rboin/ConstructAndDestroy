

#include "description_manager.h"
#include "../sdl_name_label.h"


SDLNameLabel* DescriptionManager::description = nullptr;

DescriptionManager::DescriptionManager() {}

DescriptionManager::~DescriptionManager() {
    delete this->description;
}

SDLNameLabel* DescriptionManager::get_description() {
    if(!description){
        TTF_Font *f_font = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
        vec2 description_panel_pos = {0,0}, description_panel_size = {400, 20};
        sdl_data sdl_description_data = {255, 255, 255, 255};
        SDLNameLabel* description_text = new SDLNameLabel(description_panel_pos, description_panel_size, &sdl_description_data, f_font, "");
        description = description_text;
    }
    return description;
}