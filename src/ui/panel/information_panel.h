//
// Created by robin on 3/20/17.
//

#ifndef C_AND_D_PROJECT_INFORMATION_PANEL_H
#define C_AND_D_PROJECT_INFORMATION_PANEL_H

#include "observer/observer.h"
#include "ui_component.h"

typedef struct _TTF_Font TTF_Font;
struct SDL_Color;

class MovingEntity;

template<typename T>
class Goal;

struct information {
    std::string text;
    const SDL_Color *color;
    TTF_Font *font;
};

class InformationPanel : public UIComponent, public Observer<MovingEntity *> {
private:
    information *_default_information;
    information *_information;

    std::string format_character_information();
    std::string format_character_goals(Goal<MovingEntity> *);
public:
    InformationPanel(SDL_Rect *, information *);

    void set_information(information *);

    void update(float d) override;

    void update_data() override;

    void set_subject(Observable<MovingEntity *> *) override;

    SDL_Texture *draw(SDL_Renderer *renderer) override;
};


#endif //C_AND_D_PROJECT_INFORMATION_PANEL_H
