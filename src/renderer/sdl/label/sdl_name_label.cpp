
#include <string>
#include <SDL_ttf.h>
#include "types.h"
#include "sdl_name_label.h"
#include "sdl/text/sdl_render_text_object.h"

SDLNameLabel::SDLNameLabel(const vec2 &position, const vec2 &size, sdl_data *data, TTF_Font* font,
                           std::string text): SDL_RenderObject(position, size, data)  {

    double size_y = _size.y;
    vec2 text_pos = {_position.x, _position.y}, text_size = {_size.x, (float)size_y};

    _text = text;

    sdl_text *text_data = new sdl_text{_data->red, _data->green, _data->blue, text.c_str(), font};
    _text_object = new SDL_UI_RenderTextObject(text_pos,text_size,text_data);

}

void SDLNameLabel::render(SDLRenderer *renderer) {
    if (_text == "") {
        return;
    }

    sdl_text *temp = (sdl_text*)_text_object->get_data();
    temp->text = _text.c_str();

    _text_object->render(renderer);
}

void SDLNameLabel::set_text(std::string text) {
    this->_text = text;
}

SDLNameLabel::~SDLNameLabel(){
    delete this->_text_object;
}
