//
// Created by robin on 3/20/17.
//

#include "information_panel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <entity/goal/goal.h>
#include <entity/goal/moving_entity_goal/level_type.h>
#include <entity/goal/composite_goal.h>
#include "observer/observable.h"
#include "entity/moving/moving_entity.h"

InformationPanel::InformationPanel(SDL_Rect *s, information *default_information) :

UIComponent(s) {
        _default_information = default_information;
        _information = nullptr;
}

void InformationPanel::update(float d) {
    if (subject->get_data() && _information)
        _information->text = format_character_information();
}

SDL_Texture *InformationPanel::draw(SDL_Renderer *renderer) {
    information *current_information = _default_information;
    if (_information) {
        current_information = _information;
    }

    SDL_Surface *f_surface = TTF_RenderText_Blended_Wrapped(current_information->font,
                                                            current_information->text.c_str(),
                                                            *current_information->color,
                                                            (Uint32) this->size->w);
    SDL_Texture *f_texture = SDL_CreateTextureFromSurface(renderer, f_surface);

    SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, this->texture);
    // Clear our previous texture
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, NULL);
    // Set transparency

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, NULL);
    SDL_RenderCopy(renderer, f_texture, NULL, &f_surface->clip_rect);

    SDL_DestroyTexture(f_texture);
    SDL_FreeSurface(f_surface);

    return this->texture;
}

void InformationPanel::set_information(information *i) {
    _information = i;
}

void InformationPanel::update_data() {
    if (subject->get_data()) {
        if (!_information)
            _information = new information;
        _information->color = _default_information->color;
        _information->font = _default_information->font;
    } else {
        delete _information;
        _information = nullptr;
    }

}

void InformationPanel::set_subject(Observable<MovingEntity *> *s) {
    s->attach(this);
    subject = s;
}

std::string InformationPanel::format_character_information() {
    std::ostringstream stringStream;
    stringStream << "Position: (" << subject->get_data()->get_position().x << ", "
                 << subject->get_data()->get_position().y << ")\n";
    stringStream << "Velocity: (" << std::trunc(100 * subject->get_data()->get_velocity().x)/100 << ","
                 << std::trunc(100 * subject->get_data()->get_velocity().y)/100 << ")\n";
    stringStream << "Current goals: \n"
                 << format_character_goals((Goal<MovingEntity> *) subject->get_data()->get_brain()) << "\n";

    std::string tmp = stringStream.str();
    return tmp;
}

std::string InformationPanel::format_character_goals(Goal<MovingEntity> *g) {
    std::string tmp = "";

    if (g && g->get_level_type() == LevelType::ATOMIC) {
        tmp += g->get_name();
        return "----" + tmp;
    } else if (g && g->get_level_type() == LevelType::STRATEGY) {

        GoalComposite<MovingEntity> *comp = (GoalComposite<MovingEntity> *) g;
        std::deque<Goal<MovingEntity> *> sub_goals = comp->get_sub_goals();

        tmp += g->get_name();

        for (std::deque<Goal<MovingEntity> *>::reverse_iterator it = sub_goals.rbegin();
             it != sub_goals.rend(); it++) {

            Goal<MovingEntity> *current_goal = (*it);
            if (current_goal) {
                tmp += "\n----" + format_character_goals(current_goal);
            }
        }
    }
    return tmp;
}


