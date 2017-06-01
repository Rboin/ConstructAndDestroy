//
// Created by Mark on 23-5-2017.
//

#include "render_object.h"
#include "sdl_render_label.h"
#include "sdl/image/sdl_image_render_object.h"
#include "sdl/text/sdl_render_text_object.h"
#include "sdl/sdl_renderer.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "sdl_cost_label.h"
#include "settings.h"

SDLCostLabel::SDLCostLabel(const vec2 &position, const vec2 &size, sdl_data *data, std::string image_path, ResourceType rt, TTF_Font *font, Resources* resources) : SDL_RenderObject(position,
                                                                                                                                                                                  size, data) , _rt(rt){

    double size_y = _size.y / 1.5;
    vec2 image_pos = {_position.x, _position.y}, image_size = {_size.x / 3, (float)size_y};
    vec2 text_pos = {_position.x + _size.x / 2 - 10, _position.y}, text_size = {_size.x / 3, (float)size_y};
    sdl_image_data *image_data = new sdl_image_data{image_path};

    this->_resources = resources;
    _rt = rt;
    this->data = data;

    sdl_text *text_data = new sdl_text{_data->red, _data->green, _data->blue, std::to_string((int)resources->get_resources(rt)).c_str(), font};
    _text = new SDL_UI_RenderTextObject(text_pos,text_size,text_data);

    _image = new SDL_ImageRenderObject(image_pos,image_size,image_data);
}



void SDLCostLabel::render(SDLRenderer *renderer) {
    sdl_text *temp = (sdl_text*)_text->get_data();
    temp->text = std::to_string((int)_resources->get_resources(_rt)).c_str();

    int available_resources = (int)PlayerManager::get_instance()->get_player(player_id)->resources->get_resources(_rt);

    if((int)_resources->get_resources(_rt) > available_resources){
        temp->blue = 0;
        temp->green = 0;
        temp->red = 255;
    } else {
        temp->blue = data->blue;
        temp->green = data->green;
        temp->red = data->red;
    }

    _image->render(renderer);
    _text->render(renderer);
}

SDLCostLabel::~SDLCostLabel() {
    delete this->_text;
    this->_resources = nullptr;
    delete this->_image;
    clear_data();
}
