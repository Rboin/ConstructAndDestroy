//
// Created by robin on 3/19/17.
//

#ifndef C_AND_D_PROJECT_SIMULATION_SCREEN_H
#define C_AND_D_PROJECT_SIMULATION_SCREEN_H

#include "ui/ui_component.h"
//#include "ui/ui_part.h"

class World;

class WorldPanel : public UIComponent {
private:
    World *_world;
public:
    WorldPanel(World *, SDL_Rect *);

    SDL_Texture *draw(SDL_Renderer *) override;

    void update(float) override;
};


#endif //C_AND_D_PROJECT_SIMULATION_SCREEN_H
