//
// Created by bouwm on 8-5-2017.
//

#include "sdl_render_label.h"
#include "sdl/image/sdl_image_render_object.h"
#include "sdl/text/sdl_render_text_object.h"
#include "sdl/sdl_renderer.h"

SDLRenderLabel::SDLRenderLabel(const vec2 &position, const vec2 &size, sdl_data *data, std::string image_path,std::string text, TTF_Font *font) : SDL_RenderObject(position,
                                                                                                          size, data) {

    vec2 image_pos = {_position.x, _position.y}, image_size = {_size.x / 2, _size.y};
    vec2 text_pos = {_position.x + _size.x / 2, _position.y}, text_size = {_size.x / 2, _size.y};

    sdl_image_data *image_data = new sdl_image_data{image_path};
    sdl_text *text_data = new sdl_text{_data->red, _data->green, _data->blue, text.c_str(), font};

    _text = new SDL_UI_RenderTextObject(text_pos, text_size, text_data);
    _image = new SDL_ImageRenderObject(image_pos, image_size, image_data);
}

void SDLRenderLabel::render(SDLRenderer *renderer, const mat2 &transformations) {
    _image->render(renderer, transformations);
    _text->render(renderer, transformations);
}

SDLRenderLabel::~SDLRenderLabel() {
    delete _text;
    delete _image;
}

void SDLRenderLabel::set_position(float x, float y) {
    RenderObject::set_position(x, y);
    vec2 image_pos = {_position.x, _position.y}, image_size = {_size.x / 2, _size.y};
    vec2 text_pos = {_position.x + _size.x / 2, _position.y}, text_size = {_size.x / 2, _size.y};
    _image->set_position(image_pos.x, image_pos.y);
    _text->set_position(text_pos.x, text_pos.y);
}

void SDLRenderLabel::set_text(const char* text) {
    sdl_text *temp = (sdl_text*)_text->get_data();
    temp->text = text;
}

