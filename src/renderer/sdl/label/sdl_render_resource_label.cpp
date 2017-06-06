//
// Created by Jeroen on 6/1/2017.
//

#include <cstring>
#include "entity/player_manager.h"
#include "entity/player.h"
#include "settings.h"
#include "sdl_render_resource_label.h"

SDLRenderResourceLabel::SDLRenderResourceLabel(const vec2 &position, const vec2 &size, sdl_data *data, std::string texture, ResourceType rt, TTF_Font * font) : _rt(rt),
        SDLRenderLabel(position, size, data, texture, "", font) {
    _rt = rt;

    PlayerManager *pm = PlayerManager::get_instance();

    Player *p = pm->get_player(player_id);
    _resource = p->resources;

    set_text(get_resource_text());
}

void SDLRenderResourceLabel::render(SDLRenderer *renderer, const mat2 &mat) {
    set_text(get_resource_text());

    SDLRenderLabel::render(renderer, mat);
}

const char *SDLRenderResourceLabel::get_resource_text() {
    std::string temp_str = std::to_string((int)_resource->get_resources(_rt));
    char* char_type = new char[temp_str.length()];
    strcpy(char_type, temp_str.c_str());

    return char_type;
}