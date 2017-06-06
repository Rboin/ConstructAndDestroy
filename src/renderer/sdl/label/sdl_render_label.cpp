//
// Created by bouwm on 8-5-2017.
//

#include "sdl_render_label.h"
#include "sdl/image/sdl_image_render_object.h"
#include "sdl/text/sdl_render_text_object.h"
#include "sdl/sdl_renderer.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "settings.h"


SDLRenderLabel::SDLRenderLabel(const vec2 &position, const vec2 &size, sdl_data *data, std::string image_path,
                               ResourceType rt) : SDL_RenderObject(position,
                                                                                   size, data), _rt(rt) {
    TTF_Font *font = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
    vec2 image_pos = {_position.x, _position.y}, image_size = {_size.x / 2, _size.y};
    vec2 text_pos = {_position.x + _size.x / 2, _position.y}, text_size = {_size.x / 2, _size.y};
    sdl_image_data *image_data = new sdl_image_data{image_path};

    PlayerManager *pm = PlayerManager::get_instance();

    Player *p = pm->get_player(player_id);
    _resource = p->resources;

    sdl_text *text_data = new sdl_text{_data->red, _data->green, _data->blue,
                                       std::to_string((int) _resource->get_resources(_rt)).c_str(), font};
    _text = new SDL_UI_RenderTextObject(text_pos, text_size, text_data);

    _image = new SDL_ImageRenderObject(image_pos, image_size, image_data);
}

void SDLRenderLabel::render(SDLRenderer *renderer, const mat2 &transformations) {
    sdl_text *temp = (sdl_text*)_text->get_data();
    int a = (int)_resource->get_resources(_rt);
    temp->text = std::to_string((int)_resource->get_resources(_rt)).c_str();

    _image->render(renderer, transformations);
    _text->render(renderer, transformations);
}

SDLRenderLabel::~SDLRenderLabel() {
    delete _text;
    delete _image;
    _resource = nullptr;
}

void SDLRenderLabel::set_position(float x, float y) {
    RenderObject::set_position(x, y);
    vec2 image_pos = {_position.x, _position.y}, image_size = {_size.x / 2, _size.y};
    vec2 text_pos = {_position.x + _size.x / 2, _position.y}, text_size = {_size.x / 2, _size.y};
    _image->set_position(image_pos.x, image_pos.y);
    _text->set_position(text_pos.x, text_pos.y);
}

