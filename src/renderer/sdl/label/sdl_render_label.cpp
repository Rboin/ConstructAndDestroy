//
// Created by bouwm on 8-5-2017.
//

#include "sdl_render_label.h"
#include "renderer.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "../globals.cpp"


SDLRenderLabel::SDLRenderLabel(const vec2 &position, const vec2 &size, sdl_data *data, std::string image_path, ResourceType rt, TTF_Font *font) : SDL_RenderObject(position,
                                                                                                          size, data) , _rt(rt){
    vec2 image_pos = {_position.x, _position.y}, image_size = {_size.x / 2, _size.y};
    vec2 text_pos = {_position.x + _size.x / 2, _position.y}, text_size = {_size.x / 2, _size.y};
    sdl_image_data *image_data = new sdl_image_data{image_path};

    PlayerManager *pm = PlayerManager::get_instance();
    Player *p = pm->get_player(player_id);
    _resource = &p->resources;

    sdl_ui_text_data *text_data = new sdl_ui_text_data{_data->red, _data->green, _data->blue, std::to_string((int)_resource->get_resources(_rt)).c_str(), font};
    _text = new SDL_UI_RenderTextObject(text_pos,text_size,text_data);

    _image = new SDL_ImageRenderObject(image_pos,image_size,image_data);
}

SDL_Texture *SDLRenderLabel::render(Renderer<SDL_Renderer> *renderer) {
    sdl_ui_text_data *temp = (sdl_ui_text_data*)_text->get_data();
    temp->text = std::to_string((int)_resource->get_resources(_rt)).c_str();

    SDL_Texture *image_texture = _image->render(renderer);
    SDL_Texture *text_texture = _text->render(renderer);
    init_texture(renderer);
    SDL_Rect image_rect = {(int)_image->get_position()->x, (int)_image->get_position()->y, (int)_image->get_size()->x,
                           (int)_image->get_size()->y};
    SDL_Rect text_rect = {(int)_text->get_position()->x, (int)_text->get_position()->y, (int)_text->get_size()->x,
                          (int)_text->get_size()->y};
    SDL_SetRenderTarget(renderer->get_engine(), _result);
    SDL_RenderCopy(renderer->get_engine(), image_texture, NULL, &image_rect);
    SDL_RenderCopy(renderer->get_engine(), text_texture, NULL, &text_rect);
    SDL_SetRenderTarget(renderer->get_engine(), NULL);

    return _result;
}

