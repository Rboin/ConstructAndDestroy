//
// Created by robin on 3/19/17.
//

#ifndef C_AND_D_PROJECT_UI_COMPONENT_H
#define C_AND_D_PROJECT_UI_COMPONENT_H

#include <map>

struct SDL_Rect;
struct SDL_Texture;
class SDL_Renderer;

class UIComponent {
protected:
    SDL_Rect *size;

    std::map<const char *, UIComponent *> components;

    SDL_Texture *texture;

    virtual void draw_components(SDL_Renderer *);

public:
    UIComponent(SDL_Rect *s);

    virtual ~UIComponent();

    virtual SDL_Rect *get_size();

    virtual bool add_component(const char *, UIComponent *);

    virtual bool remove_component(const char *);

    virtual void update(float);

    virtual SDL_Texture *draw(SDL_Renderer *);

};

#endif //C_AND_D_PROJECT_UI_COMPONENT_H
