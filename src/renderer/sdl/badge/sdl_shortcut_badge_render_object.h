//
// Created by Stephan Schrijver on 1-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_SHORTCUT_BADGE_RENDER_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_SHORTCUT_BADGE_RENDER_OBJECT_H

#include <SDL_ttf.h>
#include "sdl_rectangle_badge_render_object.h"

class SDL_ShortcutBadgeRenderObject : public SDL_RectangleBadgeRenderObject {
private:
    std::string _shortcut;
public:
    SDL_ShortcutBadgeRenderObject(const vec2 &position, const vec2 &size, TTF_Font *font, std::string text,
                                  sdl_data *color, int radius);

    virtual void render(SDLRenderer *, const mat2 &) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_SHORTCUT_BADGE_RENDER_OBJECT_H
